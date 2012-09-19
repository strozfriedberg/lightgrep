#include "lightgrep_c_api.h"
#include "jlightgrep.h"

#include <functional>
#include <memory>
#include <sstream>
#include <tuple>

static const char* ALL_IS_LOST = "Fuck it, Dude. Let's go bowling.";

static const char* programHandleClassName = "com/lightboxtechnologies/lightgrep/ProgramHandle";
static const char* contextHandleClassName = "com/lightboxtechnologies/lightgrep/ContextHandle";

static const char* hitCallbackClassName = "com/lightboxtechnologies/lightgrep/HitCallback";
static const char* searchHitClassName = "com/lightboxtechnologies/lightgrep/SearchHit";

static const char* nullPointerExceptionClassName = "java/lang/NullPointerException";
static const char* indexOutOfBoundsExceptionClassName = "java/lang/IndexOutOfBoundsException";
static const char* outOfMemoryErrorClassName = "java/lang/OutOfMemoryError";
static const char* keywordExceptionClassName = "com/lightboxtechnologies/lightgrep/KeywordException";
static const char* programExceptionClassName = "com/lightboxtechnologies/lightgrep/ProgramException";

//
// We cache field and method IDs in static init() methods for each class,
// in order to ensure that they get reset if a class is reloaded.
//

static jfieldID parserHandlePointerField;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ParserHandle_init(JNIEnv* env, jclass cl) {
  parserHandlePointerField = env->GetFieldID(cl, "Pointer", "J");
}

static jfieldID programHandlePointerField;
static jmethodID programHandleCtor;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_init(JNIEnv* env, jclass cl) {
  programHandleCtor = env->GetMethodID(cl, "<init>", "(J)V");
  if (env->ExceptionCheck()) return;

  programHandlePointerField = env->GetFieldID(cl, "Pointer", "J");
}

static jfieldID contextHandlePointerField;
static jmethodID contextHandleCtor;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_init(JNIEnv* env, jclass cl) {
  contextHandleCtor = env->GetMethodID(cl, "<init>", "(J)V");
  if (env->ExceptionCheck()) return;

  contextHandlePointerField = env->GetFieldID(cl, "Pointer", "J");
}

static jfieldID keyOptionsFixedStringField;
static jfieldID keyOptionsCaseInsensitiveField;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_KeyOptions_init(JNIEnv* env, jclass cl) {
  keyOptionsFixedStringField = env->GetFieldID(cl, "FixedString", "Z");
  if (env->ExceptionCheck()) return;

  keyOptionsCaseInsensitiveField = env->GetFieldID(cl, "FixedString", "Z");
}

static jfieldID programOptionsDeterminizeField;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramOptions_init(JNIEnv* env, jclass cl) {
  programOptionsDeterminizeField = env->GetFieldID(cl, "Determinize", "Z");
}

static jfieldID contextOptionsTraceBeginField;
static jfieldID contextOptionsTraceEndField;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextOptions_init(JNIEnv* env, jclass cl) {
  contextOptionsTraceBeginField = env->GetFieldID(cl, "TraceBegin", "J");
  if (env->ExceptionCheck()) return;

  contextOptionsTraceBeginField = env->GetFieldID(cl, "TraceEnd", "J");
}

static jclass hitCallbackClass;
static jmethodID hitCallbackCallback;

static jclass searchHitClass;
static jmethodID searchHitCtor;
static jfieldID searchHitStartField;
static jfieldID searchHitEndField;
static jfieldID searchHitKeywordIndexField;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jvm, void*) {
  JNIEnv* env;
  if (jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }

  // We make a global reference for HitCallback because it's not possible
  // to put a static block or any method implementations into an interface,
  // which prevents us from reseting the callback() method ID in the event
  // that HitCallback is unloaded and reloaded. The global reference blocks
  // this by preventing HitCallback from being unloaded.
  jclass cl = env->FindClass(hitCallbackClassName);
  if (env->ExceptionCheck()) return JNI_ERR;

  hitCallbackClass = reinterpret_cast<jclass>(env->NewGlobalRef(cl));
  if (!hitCallbackClass) return JNI_ERR;

  hitCallbackCallback = env->GetMethodID(hitCallbackClass, "callback", "(Lcom/lightboxtechnologies/lightgrep/SearchHit;)V");
  if (env->ExceptionCheck()) return JNI_ERR;

  // We make a global reference for SearchHit to avoid calling FindClass
  // for it on every hit in the callbackShim.
  cl = env->FindClass(searchHitClassName);
  if (env->ExceptionCheck()) return JNI_ERR;

  searchHitClass = reinterpret_cast<jclass>(env->NewGlobalRef(cl));
  if (!searchHitClass) return JNI_ERR;

  searchHitCtor = env->GetMethodID(searchHitClass, "<init>", "(JJI)V");
  if (env->ExceptionCheck()) return JNI_ERR;

  searchHitStartField = env->GetFieldID(searchHitClass, "Start", "J");
  if (env->ExceptionCheck()) return JNI_ERR;

  searchHitEndField = env->GetFieldID(searchHitClass, "End", "J");
  if (env->ExceptionCheck()) return JNI_ERR;

  searchHitKeywordIndexField = env->GetFieldID(searchHitClass, "KeywordIndex", "I");
  if (env->ExceptionCheck()) return JNI_ERR;

  return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM* jvm, void*) {
  JNIEnv* env;
  if (jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    // FIXME: Everything is hosed if this happens. We can't even throw an
    // exception back into Java, since to do that we'd need a valid JNIEnv.
    return;
  }

  env->DeleteGlobalRef(hitCallbackClass);
  env->DeleteGlobalRef(searchHitClass);
}

static void throwException(JNIEnv* env, const char* exClassName, const char* message) {
  jclass ex = env->FindClass(exClassName);
  if (!env->ExceptionCheck()) {
    if (env->ThrowNew(ex, message)) {
      env->FatalError(ALL_IS_LOST);
    }
  }
}

template <typename V>
static bool throwIfNull(JNIEnv* env, const char* varname, const V* var) {
  if (var == nullptr) {
    std::ostringstream ss;
    ss << varname << " == null";

    throwException(env, nullPointerExceptionClassName, ss.str().c_str());
    return true;
  }
  else {
    return false;
  }
}

template <typename V>
static bool throwIfNegative(JNIEnv* env, const char* varname, V var) {
  if (var < 0) {
    std::ostringstream ss;
    ss << varname << " == " << var << " < 0";

    throwException(env, indexOutOfBoundsExceptionClassName, ss.str().c_str());
    return true;
  }
  else {
    return false;
  }
}

template <typename O, typename S>
static bool throwIfBufferTooSmall(JNIEnv* env, const char* bufname, jbyteArray buffer, const char* offname, O offset, const char* sname, S size) {
  const jsize buflen = env->GetArrayLength(buffer);
  if (buflen - offset < size) {
    std::ostringstream ss;
    ss << bufname << ".length == " << buflen << ", "
       << offname << " == " << offset << ", "
       << bufname << ".length - " << offname << " < "
       << sname << " == " << size;

    throwException(env, indexOutOfBoundsExceptionClassName, ss.str().c_str());
    return true;
  }
  else {
    return false;
  }
}

JNIEXPORT jlong JNICALL Java_com_lightboxtechnologies_lightgrep_ParserHandle_create(JNIEnv*, jclass, jint numFsmStateSizeHint) {
  return reinterpret_cast<jlong>(lg_create_parser(numFsmStateSizeHint));
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ParserHandle_destroy(JNIEnv* env, jobject hParser) {
  jlong ptr = env->GetLongField(hParser, parserHandlePointerField);
  lg_destroy_parser(reinterpret_cast<LG_HPARSER>(ptr));
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ParserHandle_addKeyword(JNIEnv* env, jobject hParser, jstring keyword, jint keyIndex, jobject options, jstring encoding) {
  // validate all of the arguments so we don't crash the JVM
  if (throwIfNull(env, "keyword", keyword) || 
      throwIfNegative(env, "keyIndex", keyIndex) ||
      throwIfNull(env, "options", options) ||
      throwIfNull(env, "encoding", encoding))
  {
    return 0;
  }

  // convert all of the Java objects to C
  LG_HPARSER ptr = reinterpret_cast<LG_HPARSER>(
    env->GetLongField(hParser, parserHandlePointerField)
  );

  using namespace std::placeholders;

  std::unique_ptr<const char,std::function<void(const char*)>> kw(
    env->GetStringUTFChars(keyword, nullptr),
    std::bind(&JNIEnv::ReleaseStringUTFChars, env, keyword, _1)
  );

  if (!kw) {
    // FIXME: does this mean an OOME has been thrown already?
    return 0;
  }

  LG_KeyOptions opts{
    env->GetBooleanField(options, keyOptionsFixedStringField) != 0,
    env->GetBooleanField(options, keyOptionsCaseInsensitiveField) != 0
  };

  std::unique_ptr<const char,std::function<void(const char*)>> enc(
    env->GetStringUTFChars(encoding, nullptr),
    std::bind(&JNIEnv::ReleaseStringUTFChars, env, encoding, _1)
  );

  if (!enc) {
    // FIXME: does this mean an OOME has been thrown already?
    return 0;
  }

  // finally actually do something
  const int ret = lg_add_keyword(
    ptr,
    kw.get(),
    std::strlen(kw.get()),
    (uint32) keyIndex,
    &opts,
    enc.get()
  );

  if (!ret) {
    throwException(env, keywordExceptionClassName, lg_error(ptr));
  }

  return ret;
}

static jobject makeProgramHandle(JNIEnv* env, LG_HPROGRAM hProg) {
  jclass cl = env->FindClass(programHandleClassName);
  if (env->ExceptionCheck()) return nullptr;

  return env->NewObject(cl, programHandleCtor, reinterpret_cast<jlong>(hProg));
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_ParserHandle_createProgram(JNIEnv* env, jobject hParser, jobject options) {
  // validate all of the arguments so we don't crash the JVM
  if (throwIfNull(env, "options", options)) {
    return nullptr;
  }
  
  // convert all of the Java objects to C
  LG_HPARSER ptr = reinterpret_cast<LG_HPARSER>(
    env->GetLongField(hParser, parserHandlePointerField)
  );

  LG_ProgramOptions opts{
    env->GetBooleanField(options, programOptionsDeterminizeField) != 0
  };

  // finally actually do something
  LG_HPROGRAM hProg = lg_create_program(ptr, &opts);
// FIXME: don't use lg_ok
  if (lg_ok(hProg)) {
    return makeProgramHandle(env, hProg);
  }
  else {
    throwException(env, keywordExceptionClassName, lg_error(hProg));
    return nullptr;
  }
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_destroy(JNIEnv* env, jobject hProg) {
  jlong ptr = env->GetLongField(hProg, programHandlePointerField);
  lg_destroy_program(reinterpret_cast<LG_HPROGRAM>(ptr));
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_size(JNIEnv* env, jobject hProg) {
  jlong ptr = env->GetLongField(hProg, programHandlePointerField); 
  return lg_program_size(reinterpret_cast<LG_HPROGRAM>(ptr));
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_write(JNIEnv* env, jobject hProg, jbyteArray buffer, jint offset) {
  // validate all of the arguments so we don't crash the JVM
  if (throwIfNull(env, "buffer", buffer) ||
      throwIfNegative(env, "offset", offset))
  {
    return;
  }

  LG_HPROGRAM ptr = reinterpret_cast<LG_HPROGRAM>(
    env->GetLongField(hProg, programHandlePointerField)
  );

  if (
    throwIfBufferTooSmall(
      env,
      "buffer", buffer,
      "offset", offset,
      "program size", lg_program_size(ptr))
    )
  {
    return;
  }

  // convert all of the Java objects to C
  using namespace std::placeholders;

  std::unique_ptr<void,std::function<void(void*)>> data(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, 0)
  );

  if (!data) {
    // FIXME: does this mean an OOME has been thrown already?
    return;
  }

  // finally actually do something
  lg_write_program(ptr, reinterpret_cast<char*>(data.get()) + (uint32) offset);
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_read(JNIEnv* env, jclass, jbyteArray buffer, jint offset, jint size) {
  // validate all of the arguments so we don't crash the JVM
  if (throwIfNull(env, "buffer", buffer) ||
      throwIfNegative(env, "offset", offset) ||
      throwIfNegative(env, "size", size) ||
      throwIfBufferTooSmall(
        env,
        "buffer", buffer,
        "offset", offset,
        "size", size
      )
    )
  {
    return nullptr;
  }

  // convert all of the Java objects to C
  using namespace std::placeholders;

  std::unique_ptr<void,std::function<void(void*)>> data(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, 0)
  );

  if (!data) {
    // FIXME: does this mean an OOME has been thrown already?
    return nullptr;
  }

  char* buf = reinterpret_cast<char*>(data.get()) + (uint32) offset;

  // finally actually do something
  LG_HPROGRAM hProg = lg_read_program(buf, (uint32) size);
  if (lg_ok(hProg)) {
    return makeProgramHandle(env, hProg);
  }
  else {
    throwException(env, programExceptionClassName, lg_error(hProg));
    return nullptr;
  }
}

static jobject makeContextHandle(JNIEnv* env, LG_HCONTEXT hCtx) {
  jclass cl = env->FindClass(contextHandleClassName);
  if (env->ExceptionCheck()) return nullptr;

  return env->NewObject(cl, contextHandleCtor, reinterpret_cast<jlong>(hCtx));
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_createContext(JNIEnv* env, jobject hProg, jobject options) {
  // validate all of the arguments so we don't crash the JVM
  if (throwIfNull(env, "options", options)) {
    return nullptr;
  }
  
  // convert all of the Java objects to C
  LG_HPROGRAM ptr = reinterpret_cast<LG_HPROGRAM>(
    env->GetLongField(hProg, programHandlePointerField)
  );

  LG_ContextOptions opts{
    (uint64) env->GetLongField(options, contextOptionsTraceBeginField),
    (uint64) env->GetLongField(options, contextOptionsTraceEndField),
  };

  LG_HCONTEXT hCtx = lg_create_context(ptr, &opts);
  if (lg_ok(hCtx)) {
    return makeContextHandle(env, hCtx);
  }
  else {
    throwException(env, programExceptionClassName, lg_error(hCtx));
    return nullptr;
  }
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_destroy(JNIEnv* env, jobject hCtx) {
  jlong ptr = env->GetLongField(hCtx, contextHandlePointerField);
  lg_destroy_context(reinterpret_cast<LG_HCONTEXT>(ptr));
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_reset(JNIEnv* env, jobject hCtx) {
  jlong ptr = env->GetLongField(hCtx, contextHandlePointerField); 
  lg_reset_context(reinterpret_cast<LG_HCONTEXT>(ptr));
}

static void callbackShim(void* userData, const LG_SearchHit* const hit) {
  JNIEnv* env;
  jobject cb;
  std::tie(env, cb) = *reinterpret_cast<std::tuple<JNIEnv*,jobject>*>(userData);

  jobject hobj = env->NewObject(
    searchHitClass,
    searchHitCtor,
    (jlong) hit->Start,
    (jlong) hit->End,
    (jint) hit->KeywordIndex
  );

// FIXME: is this actually effective?
  if (env->ExceptionCheck()) return;
  if (hobj == nullptr) env->FatalError(ALL_IS_LOST);
  
  env->CallVoidMethod(cb, hitCallbackCallback, hobj);
// FIXME: do we need an exception check here? what about at the start
// of this function?
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_search(JNIEnv* env, jobject hCtx, jbyteArray buffer, jint offset, jint size, jlong startOffset, jobject callback) {
  // validate all of the arguments so we don't crash the JVM
  if (throwIfNull(env, "buffer", buffer) ||
      throwIfNegative(env, "offset", offset) ||
      throwIfNegative(env, "size", size) ||
      throwIfBufferTooSmall(
        env,
        "buffer", buffer,
        "offset", offset,
        "size", size
      ) ||
      throwIfNegative(env, "startOffset", startOffset) ||
      throwIfNull(env, "callback", callback)
    )
  {
    return 0;
  }

  // convert all of the Java objects to C
  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, contextHandlePointerField)
  );

  using namespace std::placeholders;

  std::unique_ptr<void,std::function<void(void*)>> data(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, JNI_ABORT)
  );

  if (!data) {
    // FIXME: does this mean an OOME has been thrown already?
    return 0;
  }
    
  const char* buf = reinterpret_cast<const char*>(data.get()) + offset;
 
  std::tuple<JNIEnv*,jobject> userData{env, callback};

  // finally actually do something
  return lg_search(
    ptr,
    buf,
    buf + size,
    (uint64) startOffset,
    &userData,
    callbackShim
  );
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_closeoutSearch(JNIEnv* env, jobject hCtx, jobject callback) {
  // validate all of the arguments so we don't crash the JVM
  if (throwIfNull(env, "callback", callback)) {
    return;
  }

  // convert all of the Java objects to C
  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, contextHandlePointerField)
  );

  std::tuple<JNIEnv*,jobject> userData{env, callback};

  // finally actually do something
  lg_closeout_search(ptr, &userData, callbackShim);
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_startsWith(JNIEnv* env, jobject hCtx, jbyteArray buffer, jint offset, jint size, jlong startOffset, jobject callback) {
  // validate all of the arguments so we don't crash the JVM
  if (throwIfNull(env, "buffer", buffer) ||
      throwIfNegative(env, "offset", offset) ||
      throwIfNegative(env, "size", size) ||
      throwIfBufferTooSmall(
        env,
        "buffer", buffer,
        "offset", offset,
        "size", size
      ) ||
      throwIfNegative(env, "startOffset", startOffset) ||
      throwIfNull(env, "callback", callback)
    )
  {
    return;
  }

  // convert all of the Java objects to C
  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, contextHandlePointerField)
  );

  using namespace std::placeholders;

  std::unique_ptr<void,std::function<void(void*)>> data(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, JNI_ABORT)
  );

  if (!data) {
    // FIXME: does this mean an OOME has been thrown already?
    return;
  }

  const char* buf = reinterpret_cast<const char*>(data.get()) + offset;

  std::tuple<JNIEnv*,jobject> userData{env, callback};

  // finally actually do something
  lg_starts_with(
    ptr,
    buf,
    buf + size,
    (uint64) startOffset,
    &userData,
    callbackShim
  );
}

/*
JNIEXPORT jstring JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1error(JNIEnv* env, jclass, jobject handle) {
  jlong ptr = env->GetLongField(handle, handleField); 
  return env->NewStringUTF(lg_error(reinterpret_cast<void*>(ptr)));
}
*/
