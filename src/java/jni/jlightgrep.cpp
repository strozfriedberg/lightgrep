/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <lightgrep/api.h>
#include <lightgrep/util.h>

#include "jlightgrep.h"

#include <functional>
#include <limits>
#include <memory>
#include <sstream>
#include <tuple>

static const char ALL_IS_LOST[] = "Fuck it, Dude. Let's go bowling.";

static const char patternInfoClassName[] = "com/lightboxtechnologies/lightgrep/PatternInfo";
static const char programHandleClassName[] = "com/lightboxtechnologies/lightgrep/ProgramHandle";
static const char contextHandleClassName[] = "com/lightboxtechnologies/lightgrep/ContextHandle";

static const char hitCallbackClassName[] = "com/lightboxtechnologies/lightgrep/HitCallback";
static const char searchHitClassName[] = "com/lightboxtechnologies/lightgrep/SearchHit";

static const char hitContextClassName[] = "com/lightboxtechnologies/lightgrep/HitContext";

static const char keywordExceptionClassName[] = "com/lightboxtechnologies/lightgrep/KeywordException";
static const char programExceptionClassName[] = "com/lightboxtechnologies/lightgrep/ProgramException";
static const char indexOutOfBoundsExceptionClassName[] = "java/lang/IndexOutOfBoundsException";
static const char unsupportedEncodingExceptionClassName[] = "java/io/UnsupportedEncodingException";

class PendingJavaException {};

static void throwIfException(JNIEnv* env) {
  if (env->ExceptionCheck()) {
    throw PendingJavaException();
  }
}

static void throwException(JNIEnv* env, const char* exClassName, const char* message) {
  jclass ex = env->FindClass(exClassName);
  if (!env->ExceptionCheck()) {
    if (env->ThrowNew(ex, message)) {
      env->FatalError(ALL_IS_LOST);
    }
  }

  throw PendingJavaException();
}



//
// We cache field and method IDs in static init() methods for each class,
// in order to ensure that they get reset if a class is reloaded.
//

static jfieldID handlePointerField;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_Handle_init(JNIEnv* env, jclass cl) {
  try {
    handlePointerField = env->GetFieldID(cl, "Pointer", "J");
    throwIfException(env);
  }
  catch (const PendingJavaException&) {
  }
}

static jmethodID patternInfoCtor;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_PatternInfo_init(JNIEnv* env, jclass cl) {
  try {
    patternInfoCtor = env->GetMethodID(cl, "<init>", "(Ljava/lang/String;Ljava/lang/String;I)V");
    throwIfException(env);
  }
  catch (const PendingJavaException&) {
  }
}

static jmethodID programHandleCtor;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_init(JNIEnv* env, jclass cl) {
  try {
    programHandleCtor = env->GetMethodID(cl, "<init>", "(J)V");
    throwIfException(env);
  }
  catch (const PendingJavaException&) {
  }
}

static jmethodID contextHandleCtor;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_init(JNIEnv* env, jclass cl) {
  try {
    contextHandleCtor = env->GetMethodID(cl, "<init>", "(J)V");
    throwIfException(env);
  }
  catch (const PendingJavaException&) {
  }
}

static jfieldID keyOptionsFixedStringField;
static jfieldID keyOptionsCaseInsensitiveField;
static jfieldID keyOptionsUnicodeModeField;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_KeyOptions_init(JNIEnv* env, jclass cl) {
  try {
    keyOptionsFixedStringField = env->GetFieldID(cl, "FixedString", "Z");
    throwIfException(env);

    keyOptionsCaseInsensitiveField = env->GetFieldID(cl, "CaseInsensitive", "Z");
    throwIfException(env);

    keyOptionsUnicodeModeField = env->GetFieldID(cl, "UnicodeMode", "Z");
    throwIfException(env);
  }
  catch (const PendingJavaException&) {
  }
}

static jfieldID programOptionsDeterminizeField;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramOptions_init(JNIEnv* env, jclass cl) {
  try {
    programOptionsDeterminizeField = env->GetFieldID(cl, "Determinize", "Z");
    throwIfException(env);
  }
  catch (const PendingJavaException&) {
  }
}

static jmethodID hitContextCtor;

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_HitContext_init(JNIEnv* env, jclass cl) {
  try {
    hitContextCtor = env->GetMethodID(
      cl, "<init>", "(JJIILjava/lang/String;I)V"
    );
    throwIfException(env);
  }
  catch (const PendingJavaException&) {
  }
}

static jclass hitCallbackClass;
static jmethodID hitCallbackCallback;

static jclass searchHitClass;
static jmethodID searchHitCtor;
static jfieldID searchHitStartField;
static jfieldID searchHitEndField;
static jfieldID searchHitKeywordIndexField;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* jvm, void*) {
  try {
    JNIEnv* env;
    if (jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
      throw PendingJavaException();
    }

    // We make a global reference for HitCallback because it's not possible
    // to put a static block or any method implementations into an interface,
    // which prevents us from reseting the callback() method ID in the event
    // that HitCallback is unloaded and reloaded. The global reference blocks
    // this by preventing HitCallback from being unloaded.
    jclass cl = env->FindClass(hitCallbackClassName);
    throwIfException(env);

    hitCallbackClass = reinterpret_cast<jclass>(env->NewGlobalRef(cl));
    if (!hitCallbackClass) throw PendingJavaException();

    hitCallbackCallback = env->GetMethodID(hitCallbackClass, "callback", "(Lcom/lightboxtechnologies/lightgrep/SearchHit;)V");
    throwIfException(env);

    // We make a global reference for SearchHit to avoid calling FindClass
    // for it on every hit in the callbackShim.
    cl = env->FindClass(searchHitClassName);
    throwIfException(env);

    searchHitClass = reinterpret_cast<jclass>(env->NewGlobalRef(cl));
    throwIfException(env);

    searchHitCtor = env->GetMethodID(searchHitClass, "<init>", "(JJI)V");
    throwIfException(env);

    searchHitStartField = env->GetFieldID(searchHitClass, "Start", "J");
    throwIfException(env);

    searchHitEndField = env->GetFieldID(searchHitClass, "End", "J");
    throwIfException(env);

    searchHitKeywordIndexField = env->GetFieldID(searchHitClass, "KeywordIndex", "I");
    throwIfException(env);

    return JNI_VERSION_1_6;
  }
  catch (const PendingJavaException&) {
    return JNI_ERR;
  }
}

JNIEXPORT void JNI_OnUnload(JavaVM* jvm, void*) {
  JNIEnv* env;
  if (jvm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
    // Everything is hosed if this happens. We can't even throw an
    // exception back into Java, since to do that we'd need a valid JNIEnv.
    return;
  }

  env->DeleteGlobalRef(hitCallbackClass);
  env->DeleteGlobalRef(searchHitClass);
}

/*
template <typename T> T unwrap(JNIEnv* env, jobject handle) {
  return reinterpret_cast<T>(env->GetLongField(handle, handlePointerField));
}
*/

static std::unique_ptr<const char,std::function<void(const char*)>> unwrap(JNIEnv* env, jstring str) {
  using namespace std::placeholders;

  std::unique_ptr<const char,std::function<void(const char*)>> ptr(
    env->GetStringUTFChars(str, nullptr),
    std::bind(&JNIEnv::ReleaseStringUTFChars, env, str, _1)
  );

  if (!ptr) {
    // OutOfMemoryError already thrown
    throw PendingJavaException();
  }

  return ptr;
}

static std::unique_ptr<void,std::function<void(void*)>> unwrapCrit(JNIEnv* env, jbyteArray buffer) {
  using namespace std::placeholders;

  std::unique_ptr<void,std::function<void(void*)>> ptr(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, 0)
  );

  if (!ptr) {
    // OutOfMemoryError already thrown
    throw PendingJavaException();
  }

  return ptr;
}

static std::unique_ptr<jbyte,std::function<void(jbyte*)>> unwrap(JNIEnv* env, jbyteArray buffer) {
  using namespace std::placeholders;

  std::unique_ptr<jbyte,std::function<void(jbyte*)>> ptr(
    env->GetByteArrayElements(buffer, nullptr),
    std::bind(&JNIEnv::ReleaseByteArrayElements, env, buffer, _1, JNI_ABORT)
  );

  if (!ptr) {
    // OutOfMemoryError already thrown
    throw PendingJavaException();
  }

  return ptr;
}

template <class T>
T handle_cast(JNIEnv* env, jobject h) {
  return reinterpret_cast<T>(env->GetLongField(h, handlePointerField));
}

template <class T, class D>
static void destroyHandle(JNIEnv* env, jobject h, D d) {
  T ptr = handle_cast<T>(env, h);
  if (ptr) {
    d(ptr);
    env->SetLongField(h, handlePointerField, 0);
  }
}

JNIEXPORT jlong JNICALL Java_com_lightboxtechnologies_lightgrep_PatternHandle_create(JNIEnv*, jclass) {
  return reinterpret_cast<jlong>(lg_create_pattern());
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_PatternHandle_destroy(JNIEnv* env, jobject hPattern) {
  destroyHandle<LG_HPATTERN>(env, hPattern, lg_destroy_pattern);
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_PatternHandle_parsePatternImpl(JNIEnv* env, jobject hPattern, jstring pattern, jobject options) {
  LG_Error* err = nullptr;
  try {
    // convert all of the Java objects to C
    LG_HPATTERN ptr = reinterpret_cast<LG_HPATTERN>(
      env->GetLongField(hPattern, handlePointerField)
    );

// TODO: C++11 stuff.

    std::unique_ptr<const char,std::function<void(const char*)>> pat(unwrap(env, pattern));

    LG_KeyOptions opts{
      env->GetBooleanField(options, keyOptionsFixedStringField) != 0,
      env->GetBooleanField(options, keyOptionsCaseInsensitiveField) != 0,
      env->GetBooleanField(options, keyOptionsUnicodeModeField) != 0
    };

    // finally actually do something
    const int ret = lg_parse_pattern(
      ptr,
      pat.get(),
      &opts,
      &err
    );
    if (err) {
      throwException(env, keywordExceptionClassName, err->Message);
    }

    return ret;
  }
  catch (const PendingJavaException&) {
    lg_free_error(err);
    return 0;
  }
}

static jobject makeProgramHandle(JNIEnv* env, LG_HPROGRAM hProg) {
  jclass cl = env->FindClass(programHandleClassName);
  throwIfException(env);

  jobject obj = env->NewObject(
    cl,
    programHandleCtor,
    reinterpret_cast<jlong>(hProg)
  );
  throwIfException(env);

  return obj;
}

JNIEXPORT jlong JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_create(JNIEnv*, jclass, jint numTotalPatternsSizeHint) {
  return 0;
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_countImpl(JNIEnv* env, jobject hProg) {
  LG_HPROGRAM ptr = reinterpret_cast<LG_HPROGRAM>(
    env->GetLongField(hProg, handlePointerField)
  );
  return lg_prog_pattern_count(ptr);
}

static jobject makePatternInfo(JNIEnv* env, LG_PatternInfo* pinfo) {
  jclass cl = env->FindClass(patternInfoClassName);
  throwIfException(env);

  jstring pat = env->NewStringUTF(pinfo->Pattern);
  throwIfException(env);

  jstring enc = env->NewStringUTF(pinfo->EncodingChain);
  throwIfException(env);

  jint idx = pinfo->UserIndex;

  jobject obj = env->NewObject(cl, patternInfoCtor, pat, enc, idx);
  throwIfException(env);

  return obj;
}

template <class LgHandle>
unsigned int get_pattern_count(LgHandle h);

template <>
unsigned int get_pattern_count<LG_HFSM>(LG_HFSM h) {
  return lg_fsm_pattern_count(h);
}

template <>
unsigned int get_pattern_count<LG_HPROGRAM>(LG_HPROGRAM h) {
  return lg_prog_pattern_count(h);
}

template <class LgHandle>
static void throwIfPatternIndexOOB(JNIEnv* env, LgHandle h, int patternIndex) {
  const int size = get_pattern_count(h);
  if (patternIndex >= size) {
    std::stringstream ss;
    ss << "patternIndex == " << patternIndex << " >= " << size << " == size()";
    throwException(env, indexOutOfBoundsExceptionClassName, ss.str().c_str());
  }
}

template <class LgHandle>
LG_PatternInfo* get_pattern_info(LgHandle h, unsigned int i);

template <>
LG_PatternInfo* get_pattern_info<LG_HFSM>(LG_HFSM h, unsigned int i) {
  return lg_fsm_pattern_info(h, i);
}

template <>
LG_PatternInfo* get_pattern_info<LG_HPROGRAM>(LG_HPROGRAM h, unsigned int i) {
  return lg_prog_pattern_info(h, i);
}

template <class LgHandle>
jobject getPatternInfo(JNIEnv* env, jobject& h, jint patternIndex) {
  try {
    // convert all of the Java objects to C
    LgHandle ptr = reinterpret_cast<LgHandle>(
      env->GetLongField(h, handlePointerField)
    );

    throwIfPatternIndexOOB(env, ptr, patternIndex);

    // finally actually do something
    LG_PatternInfo* pinfo = get_pattern_info(ptr, patternIndex);
    return makePatternInfo(env, pinfo);
  }
  catch (const PendingJavaException&) {
    return nullptr;
  }
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_FSMHandle_getPatternInfoImpl(JNIEnv* env, jobject hFsm, jint patternIndex) {
  return getPatternInfo<LG_HFSM>(env, hFsm, patternIndex);
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_getPatternInfoImpl(JNIEnv* env, jobject hProg, jint patternIndex) {
  return getPatternInfo<LG_HPROGRAM>(env, hProg, patternIndex);
}

template <class LgHandle>
jint getUserIndex(JNIEnv* env, jobject& h, jint patternIndex) {
  try {
    // convert all of the Java objects to C
    LgHandle ptr = reinterpret_cast<LgHandle>(
      env->GetLongField(h, handlePointerField)
    );

    throwIfPatternIndexOOB(env, ptr, patternIndex);

    // finally actually do something
    LG_PatternInfo* pinfo = get_pattern_info(ptr, patternIndex);
    return pinfo->UserIndex;
  }
  catch (const PendingJavaException&) {
    return 0;
  }
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_FSMHandle_getUserIndexImpl(JNIEnv* env, jobject hFsm, jint patternIndex) {
  return getUserIndex<LG_HFSM>(env, hFsm, patternIndex);
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_getUserIndexImpl(JNIEnv* env, jobject hProg, jint patternIndex) {
  return getUserIndex<LG_HPROGRAM>(env, hProg, patternIndex);
}

template <class LgHandle>
void setUserIndex(JNIEnv* env, jobject& h, jint patternIndex, jint userIndex) {  try {
    // convert all of the Java objects to C
    LgHandle ptr = reinterpret_cast<LgHandle>(
      env->GetLongField(h, handlePointerField)
    );

    throwIfPatternIndexOOB(env, ptr, patternIndex);

    LG_PatternInfo* pinfo = get_pattern_info(ptr, patternIndex);
    pinfo->UserIndex = userIndex;
  }
  catch (const PendingJavaException&) {
  }
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_FSMHandle_setUserIndexImpl(JNIEnv* env, jobject hFsm, jint patternIndex, jint userIndex) {
  setUserIndex<LG_HFSM>(env, hFsm, patternIndex, userIndex);
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_setUserIndexImpl(JNIEnv* env, jobject hProg, jint patternIndex, jint userIndex) {
  setUserIndex<LG_HPROGRAM>(env, hProg, patternIndex, userIndex);
}

JNIEXPORT jlong JNICALL Java_com_lightboxtechnologies_lightgrep_FSMHandle_create(JNIEnv*, jclass, jint patternCountHint, jint numFsmStateSizeHint) {
  return reinterpret_cast<jlong>(lg_create_fsm(patternCountHint, numFsmStateSizeHint));
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_FSMHandle_destroy(JNIEnv* env, jobject hFsm) {
  destroyHandle<LG_HFSM>(env, hFsm, lg_destroy_fsm);
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_FSMHandle_addPatternImpl(JNIEnv* env, jobject hFsm, jobject hPattern, jstring encoding, jint idx) {
  LG_Error* err = nullptr;
  try {
    // convert all of the Java objects to C
    LG_HFSM fsmptr = reinterpret_cast<LG_HFSM>(
      env->GetLongField(hFsm, handlePointerField)
    );

    LG_HPATTERN patptr = reinterpret_cast<LG_HPATTERN>(
      env->GetLongField(hPattern, handlePointerField)
    );

    std::unique_ptr<const char,std::function<void(const char*)>> enc(unwrap(env, encoding));

    // finally actually do something
    const int ret = lg_add_pattern(
      fsmptr,
      patptr,
      enc.get(),
      idx,
      &err
    );
    if (err) {
      throwException(env, keywordExceptionClassName, err->Message);
    }

    return ret;
  }
  catch (const PendingJavaException&) {
    lg_free_error(err);
    return 0;
  }
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_FSMHandle_countImpl(JNIEnv* env, jobject hFsm) {
  LG_HFSM ptr = reinterpret_cast<LG_HFSM>(
    env->GetLongField(hFsm, handlePointerField)
  );
  return lg_fsm_pattern_count(ptr);
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_compileImpl(JNIEnv* env, jobject hProg, jobject hFsm, jobject options) {
  try {
    // convert all of the Java objects to C
    LG_HFSM fsm_ptr = reinterpret_cast<LG_HFSM>(
      env->GetLongField(hFsm, handlePointerField)
    );

    LG_ProgramOptions opts{
      env->GetBooleanField(options, programOptionsDeterminizeField) != 0
    };

    // finally actually do something
    LG_HPROGRAM prog_ptr = lg_create_program(fsm_ptr, &opts);

    if (prog_ptr) {
      env->SetLongField(hProg, handlePointerField, reinterpret_cast<jlong>(prog_ptr));
      return 1;
    }
    throwException(env, programExceptionClassName, "Failed to compile program");
  }
  catch (const PendingJavaException&) {
    return 0;
  }
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_destroy(JNIEnv* env, jobject hProg) {
  destroyHandle<LG_HPROGRAM>(env, hProg, lg_destroy_program);
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_sizeImpl(JNIEnv* env, jobject hProg) {
  LG_HPROGRAM ptr = reinterpret_cast<LG_HPROGRAM>(
    env->GetLongField(hProg, handlePointerField)
  );
  return lg_program_size(ptr);
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_writeImpl(JNIEnv* env, jobject hProg, jbyteArray buffer, jint offset) {
  // convert all of the Java objects to C
  LG_HPROGRAM ptr = reinterpret_cast<LG_HPROGRAM>(
    env->GetLongField(hProg, handlePointerField)
  );

  std::unique_ptr<void,std::function<void(void*)>> data(unwrapCrit(env, buffer));

  char* buf = static_cast<char*>(data.get()) + (uint32_t) offset;

  // finally actually do something
  lg_write_program(ptr, buf);
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_readImpl(JNIEnv* env, jclass, jbyteArray buffer, jint offset, jint size) {
  try {
    LG_HPROGRAM hProg = nullptr;

    {
      // convert all of the Java objects to C
      std::unique_ptr<void,std::function<void(void*)>> data(unwrapCrit(env, buffer));

      char* buf = static_cast<char*>(data.get()) + (uint32_t) offset;

      // finally actually do something
      hProg = lg_read_program(buf, (uint32_t) size);
      if (!hProg) {
        throwException(env, programExceptionClassName, "Bad program");
      }
    }

    return makeProgramHandle(env, hProg);
  }
  catch (const PendingJavaException&) {
    return nullptr;
  }
}

static jobject makeContextHandle(JNIEnv* env, LG_HCONTEXT hCtx) {
  jclass cl = env->FindClass(contextHandleClassName);
  throwIfException(env);

  jobject obj = env->NewObject(
    cl,
    contextHandleCtor,
    reinterpret_cast<jlong>(hCtx)
  );
  throwIfException(env);

  return obj;
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_ProgramHandle_createContextImpl(JNIEnv* env, jobject hProg, jobject) {
  try {
    // convert all of the Java objects to C
    LG_HPROGRAM ptr = reinterpret_cast<LG_HPROGRAM>(
      env->GetLongField(hProg, handlePointerField)
    );

    LG_ContextOptions opts{
      std::numeric_limits<uint64_t>::max(),
      std::numeric_limits<uint64_t>::max()
    };

    LG_HCONTEXT hCtx = lg_create_context(ptr, &opts);
/*
// FIXME: Is this possible?
    if (!hCtx) {
      throwException(env, programExceptionClassName, "No hit context");
    }
*/
    return makeContextHandle(env, hCtx);
  }
  catch (const PendingJavaException&) {
    return nullptr;
  }
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_destroy(JNIEnv* env, jobject hCtx) {
  destroyHandle<LG_HCONTEXT>(env, hCtx, lg_destroy_context);
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_resetImpl(JNIEnv* env, jobject hCtx) {
  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, handlePointerField)
  );
  lg_reset_context(ptr);
}

JNIEXPORT jlong JNICALL Java_com_lightboxtechnologies_lightgrep_DecoderHandle_create(JNIEnv*, jclass) {
  return reinterpret_cast<jlong>(lg_create_decoder());
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_DecoderHandle_destroy(JNIEnv* env, jobject hDec) {
  destroyHandle<LG_HDECODER>(env, hDec, lg_destroy_decoder);
}

static void callbackShim(void* userData, const LG_SearchHit* const hit) {
  // NB: Throwing C++ exceptions here is super wacky, as they pass into
  // and then back out of our C API, finally being caught in our wrappers
  // for lg_search or lg_starts_with. This works due to our having no
  // exception_trap in those two C API functions.

  JNIEnv* env;
  jobject cb;
  std::tie(env, cb) = *static_cast<std::tuple<JNIEnv*,jobject>*>(userData);

  jobject hobj = env->NewObject(
    searchHitClass,
    searchHitCtor,
    (jlong) hit->Start,
    (jlong) hit->End,
    (jint) hit->KeywordIndex
  );
  throwIfException(env);

  env->CallVoidMethod(cb, hitCallbackCallback, hobj);
  throwIfException(env);
}

static int search(JNIEnv* env, jobject hCtx, const char* buf, jint offset, jint size, jlong startOffset, jobject callback) {
  // convert all of the Java objects to C
  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, handlePointerField)
  );

  buf += offset;

  std::tuple<JNIEnv*,jobject> userData{env, callback};

  // finally actually do something
  return lg_search(
    ptr,
    buf,
    buf + size,
    (uint64_t) startOffset,
    &userData,
    callbackShim
  );
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_searchImpl___3BIIJLcom_lightboxtechnologies_lightgrep_HitCallback_2(JNIEnv* env, jobject hCtx, jbyteArray buffer, jint offset, jint size, jlong startOffset, jobject callback) {
  try {
    std::unique_ptr<jbyte,std::function<void(jbyte*)>> data(unwrap(env, buffer));
    const char* buf = reinterpret_cast<const char*>(data.get());
    return search(env, hCtx, buf, offset, size, startOffset, callback);
  }
  catch (const PendingJavaException&) {
    return 0;
  }
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_searchImpl__Ljava_nio_ByteBuffer_2IIJLcom_lightboxtechnologies_lightgrep_HitCallback_2(JNIEnv* env, jobject hCtx, jobject buffer, jint offset, jint size, jlong startOffset, jobject callback) {
  try {
    const char* buf = static_cast<const char*>(
      env->GetDirectBufferAddress(buffer)
    );

    if (!buf) {
// FIXME: what to do here?
    }

    return search(env, hCtx, buf, offset, size, startOffset, callback);
  }
  catch (const PendingJavaException&) {
    return 0;
  }
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_closeoutSearchImpl(JNIEnv* env, jobject hCtx, jobject callback) {
  try {
    // convert all of the Java objects to C
    LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
      env->GetLongField(hCtx, handlePointerField)
    );

    std::tuple<JNIEnv*,jobject> userData{env, callback};

    // finally actually do something
    lg_closeout_search(ptr, &userData, callbackShim);
  }
  catch (const PendingJavaException&) {
  }
}

static void startsWith(JNIEnv* env, jobject hCtx, const char* buf, jint offset, jint size, jlong startOffset, jobject callback) {
  // convert all of the Java objects to C
  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, handlePointerField)
  );

  buf += offset;

  std::tuple<JNIEnv*,jobject> userData{env, callback};

  // finally actually do something
  lg_starts_with(
    ptr,
    buf,
    buf + size,
    (uint64_t) startOffset,
    &userData,
    callbackShim
  );
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_startsWithImpl___3BIIJLcom_lightboxtechnologies_lightgrep_HitCallback_2(JNIEnv* env, jobject hCtx, jbyteArray buffer, jint offset, jint size, jlong startOffset, jobject callback) {
  try {
    std::unique_ptr<jbyte,std::function<void(jbyte*)>> data(unwrap(env, buffer));
    const char* buf = reinterpret_cast<const char*>(data.get());
    startsWith(env, hCtx, buf, offset, size, startOffset, callback);
  }
  catch (const PendingJavaException&) {
  }
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_ContextHandle_startsWithImpl__Ljava_nio_ByteBuffer_2IIJLcom_lightboxtechnologies_lightgrep_HitCallback_2(JNIEnv* env, jobject hCtx, jobject buffer, jint offset, jint size, jlong startOffset, jobject callback) {
  try {
    const char* buf = static_cast<const char*>(
      env->GetDirectBufferAddress(buffer)
    );

    if (!buf) {
// FIXME: what to do here?
    }

    startsWith(env, hCtx, buf, offset, size, startOffset, callback);
  }
  catch (const PendingJavaException&) {
  }
}

static jobject makeHitContext(JNIEnv* env, const LG_Window& outer, const LG_Window& decodedHit, const char* utf8, unsigned int bad) {
  jclass cl = env->FindClass(hitContextClassName);
  throwIfException(env);

  jstring decoded = env->NewStringUTF(utf8);
  throwIfException(env);

  jobject hc = env->NewObject(
    cl, hitContextCtor, outer.begin, outer.end,
    decodedHit.begin, decodedHit.end, decoded, bad
  );
  throwIfException(env);

  return hc;
}

static jobject getHitContext(JNIEnv* env, jobject hDec, const char* buf, jint offset, jint size, jlong startOffset, jlong ibegin, jlong iend, jstring encoding, jint windowSize, jint replacement) {
  // convert all of the Java objects to C
  LG_HDECODER ptr = reinterpret_cast<LG_HDECODER>(
    env->GetLongField(hDec, handlePointerField)
  );

  buf += offset;

  const LG_Window inner{ (uint64_t) ibegin, (uint64_t) iend };

  std::unique_ptr<const char,std::function<void(const char*)>> enc(unwrap(env, encoding));

  LG_Window outer, decodedHit;
  const char* utf8;

  LG_Error* err = nullptr;

  // finally actually do something
  unsigned int bad = lg_hit_context(
    ptr,
    buf,
    buf + size,
    (uint64_t) startOffset,
    &inner,
    enc.get(),
    windowSize,
    replacement,
    &utf8,
    &outer,
    &decodedHit,
    &err
  );

  if (err) {
    throwException(env, unsupportedEncodingExceptionClassName, err->Message);
  }

  std::unique_ptr<const char[],void(*)(const char*)> pchars(
    utf8, &lg_free_hit_context_string
  );

  return makeHitContext(env, outer, decodedHit, utf8, bad);
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_LGUtil_getHitContextImpl__Lcom_lightboxtechnologies_lightgrep_DecoderHandle_2_3BIIJJJLjava_lang_String_2II(JNIEnv* env, jclass, jobject hDec, jbyteArray buffer, jint offset, jint size, jlong startOffset, jlong ibegin, jlong iend, jstring encoding, jint windowSize, jint replacement) {
  try {
    std::unique_ptr<jbyte,std::function<void(jbyte*)>> data(unwrap(env, buffer));
    const char* buf = reinterpret_cast<const char*>(data.get());

    return getHitContext(env, hDec, buf, offset, size, startOffset, ibegin, iend, encoding, windowSize, replacement);
  }
  catch (const PendingJavaException&) {
    return nullptr;
  }
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_LGUtil_getHitContextImpl__Lcom_lightboxtechnologies_lightgrep_DecoderHandle_2Ljava_nio_ByteBuffer_2IIJJJLjava_lang_String_2II(JNIEnv* env, jclass, jobject hDec, jobject buffer, jint offset, jint size, jlong startOffset, jlong ibegin, jlong iend, jstring encoding, jint windowSize, jint replacement) {
  try {
    const char* buf = static_cast<const char*>(
      env->GetDirectBufferAddress(buffer)
    );

    if (!buf) {
// FIXME: what to do here?
    }

    return getHitContext(env, hDec, buf, offset, size, startOffset, ibegin, iend, encoding, windowSize, replacement);
  }
  catch (const PendingJavaException&) {
    return nullptr;
  }
}
