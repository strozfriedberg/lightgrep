#include "lightgrep_c_api.h"
#include "jlightgrep.h"

#include <cstring>
#include <functional>
#include <memory>
#include <tuple>

static jfieldID handleField;

static jmethodID parserHandleCtor;
static jmethodID programHandleCtor;
static jmethodID contextHandleCtor;

static const char* handleClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$Handle";
static const char* parserHandleClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$ParserHandle";
static const char* programHandleClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$ProgramHandle";
static const char* contextHandleClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$ContextHandle";

static jfieldID keyOptionsFixedStringField;
static jfieldID keyOptionsCaseInsensitiveField;
static jfieldID programOptionsDeterminizeField;
static jfieldID contextOptionsTraceBeginField;
static jfieldID contextOptionsTraceEndField;

static const char* keyOptionsClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$LG_KeyOptions";
static const char* programOptionsClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$LG_ProgramOptions";
static const char* contextOptionsClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$LG_ContextOptions";

static jmethodID searchHitCtor;
static jfieldID searchHitStartField;
static jfieldID searchHitEndField;
static jfieldID searchHitKeywordIndexField;

static const char* searchHitClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$LG_SearchHit";

static jmethodID callbackCallback;

static const char* callbackClassName = "com/lightboxtechnologies/lightgrep/Lightgrep$Callback";

static const char* nullPointerExceptionClassName = "java/lang/NullPointerException";

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_init(JNIEnv* env, jclass) {
  // cache the field and method IDs we use to prevent lookup every time
  jclass c;

  c = env->FindClass(handleClassName);
  handleField = env->GetFieldID(c, "Pointer", "J");

  c = env->FindClass(parserHandleClassName);
  parserHandleCtor = env->GetMethodID(c, "<init>", "(J)V"); 

  c = env->FindClass(programHandleClassName);
  programHandleCtor = env->GetMethodID(c, "<init>", "(J)V"); 

  c = env->FindClass(contextHandleClassName);
  contextHandleCtor = env->GetMethodID(c, "<init>", "(J)V");

  c = env->FindClass(keyOptionsClassName);
  keyOptionsFixedStringField = env->GetFieldID(c, "FixedString", "Z");
  keyOptionsCaseInsensitiveField = env->GetFieldID(c, "FixedString", "Z");

  c = env->FindClass(programOptionsClassName);
  programOptionsDeterminizeField = env->GetFieldID(c, "Determinize", "Z");

  c = env->FindClass(contextOptionsClassName);
  contextOptionsTraceBeginField = env->GetFieldID(c, "TraceBegin", "J");
  contextOptionsTraceBeginField = env->GetFieldID(c, "TraceEnd", "J");

  c = env->FindClass(searchHitClassName);
  searchHitCtor = env->GetMethodID(c, "<init>", "(JJI)V");
  searchHitStartField = env->GetFieldID(c, "Start", "J");
  searchHitEndField = env->GetFieldID(c, "End", "J");
  searchHitKeywordIndexField = env->GetFieldID(c, "KeywordIndex", "I");

  c = env->FindClass(callbackClassName);
  callbackCallback = env->GetMethodID(c, "callback", "(Lcom/lightboxtechnologies/lightgrep/Lightgrep$LG_SearchHit;)V");
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1ok(JNIEnv* env, jclass, jobject handle) {
  jlong ptr = env->GetLongField(handle, handleField); 
  return lg_ok(reinterpret_cast<void*>(ptr)); 
}

JNIEXPORT jstring JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1error(JNIEnv* env, jclass, jobject handle) {
  jlong ptr = env->GetLongField(handle, handleField); 
  return env->NewStringUTF(lg_error(reinterpret_cast<void*>(ptr)));
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1create_1parser(JNIEnv* env, jclass, jint numFsmStateSizeHint) {
  return env->NewObject(
    env->FindClass(parserHandleClassName),
    parserHandleCtor,
    reinterpret_cast<jlong>(lg_create_parser(numFsmStateSizeHint))
  );
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1destroy_1parser(JNIEnv* env, jclass, jobject hParser) {
  if (hParser) {
    jlong ptr = env->GetLongField(hParser, handleField);
    return lg_destroy_parser(reinterpret_cast<LG_HPARSER>(ptr));
  }
  else {
    return 1;
  }
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1add_1keyword(JNIEnv* env, jclass, jobject hParser, jstring keyword, jint keyIndex, jobject options, jstring encoding) {
  using namespace std::placeholders;

  jlong ptr = env->GetLongField(hParser, handleField);

  std::unique_ptr<const char,std::function<void(const char*)>> kw(
    env->GetStringUTFChars(keyword, nullptr),
    std::bind(&JNIEnv::ReleaseStringUTFChars, env, keyword, _1)
  );

  LG_KeyOptions opts{
    env->GetBooleanField(options, keyOptionsFixedStringField) != 0,
    env->GetBooleanField(options, keyOptionsCaseInsensitiveField) != 0
  };

  std::unique_ptr<const char,std::function<void(const char*)>> enc(
    env->GetStringUTFChars(encoding, nullptr),
    std::bind(&JNIEnv::ReleaseStringUTFChars, env, encoding, _1)
  );

  return lg_add_keyword(
    reinterpret_cast<LG_HPARSER>(ptr),
    kw.get(),
    std::strlen(kw.get()),
    (uint32) keyIndex,
    &opts,
    enc.get()
  );
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1create_1program(JNIEnv* env, jclass, jobject hParser, jobject options) {
  LG_HPARSER ptr = reinterpret_cast<LG_HPARSER>(
    env->GetLongField(hParser, handleField)
  );

  LG_ProgramOptions opts{
    env->GetBooleanField(options, programOptionsDeterminizeField) != 0
  };

  return env->NewObject(
    env->FindClass(programHandleClassName),
    programHandleCtor,
    reinterpret_cast<jlong>(lg_create_program(ptr, &opts))
  );
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1program_1size(JNIEnv* env, jclass, jobject hProg) {
  jlong ptr = env->GetLongField(hProg, handleField); 
  return lg_program_size(reinterpret_cast<LG_HPROGRAM>(ptr));
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1write_1program(JNIEnv* env, jclass, jobject hProg, jbyteArray buffer, jint offset) {
  using namespace std::placeholders;

  LG_HPROGRAM ptr = reinterpret_cast<LG_HPROGRAM>(
    env->GetLongField(hProg, handleField)
  );

  std::unique_ptr<void,std::function<void(void*)>> data(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, 0)
  );

  lg_write_program(ptr, reinterpret_cast<char*>(data.get()) + (uint32) offset);
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1read_1program(JNIEnv* env, jclass, jbyteArray buffer, jint offset, jint size) {
  using namespace std::placeholders;

  std::unique_ptr<void,std::function<void(void*)>> data(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, 0)
  );

  char* buf = reinterpret_cast<char*>(data.get()) + (uint32) offset;

  return env->NewObject(
    env->FindClass(programHandleClassName),
    programHandleCtor,
    reinterpret_cast<jlong>(lg_read_program(buf, (uint32) size))
  );
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1destroy_1program(JNIEnv* env, jclass, jobject hProg) {
  jlong ptr = env->GetLongField(hProg, handleField); 
  return lg_destroy_program(reinterpret_cast<LG_HPROGRAM>(ptr));
}

JNIEXPORT jobject JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1create_1context(JNIEnv* env, jclass, jobject hProg, jobject options) {
  LG_HPROGRAM ptr = reinterpret_cast<LG_HPROGRAM>(
    env->GetLongField(hProg, handleField)
  );

  LG_ContextOptions opts{
    (uint64) env->GetLongField(options, contextOptionsTraceBeginField),
    (uint64) env->GetLongField(options, contextOptionsTraceEndField),
  };

  return env->NewObject(
    env->FindClass(contextHandleClassName),
    contextHandleCtor,
    reinterpret_cast<jlong>(lg_create_context(ptr, &opts))
  );
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1destroy_1context(JNIEnv* env, jclass, jobject hCtx) {
  jlong ptr = env->GetLongField(hCtx, handleField); 
  return lg_destroy_context(reinterpret_cast<LG_HCONTEXT>(ptr));
}

void callbackShim(void* userData, const LG_SearchHit* const hit) {
  JNIEnv* env;
  jobject* cb;
  std::tie(env, cb) = *reinterpret_cast<std::tuple<JNIEnv*,jobject*>*>(userData);

  jobject hobj = env->NewObject(
    env->FindClass(searchHitClassName),
    searchHitCtor,
    (jlong) hit->Start,
    (jlong) hit->End,
    (jint) hit->KeywordIndex
  );

  env->CallVoidMethod(*cb, callbackCallback, hobj);  
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1starts_1with(JNIEnv* env, jclass, jobject hCtx, jbyteArray buffer, jint offset, jint size, jlong startOffset, jobject callback) {
  using namespace std::placeholders;

  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, handleField)
  );

  std::unique_ptr<void,std::function<void(void*)>> data(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, JNI_ABORT)
  );

// FIXME: check for OOM. Wtf do we do then?
// FIXME: check that offset + size doesn't go beyond array end   
    
  const char* buf = reinterpret_cast<const char*>(data.get()) + offset;
 
  std::tuple<JNIEnv*,jobject*> userData{env, &callback};

  lg_starts_with(
    ptr,
    buf,
    buf + size,
    (uint64) startOffset,
    &userData,
    callbackShim
  );
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1reset_1context(JNIEnv* env, jclass, jobject hCtx) {
  jlong ptr = env->GetLongField(hCtx, handleField); 
  lg_reset_context(reinterpret_cast<LG_HCONTEXT>(ptr));
}

JNIEXPORT jint JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1search(JNIEnv* env, jclass, jobject hCtx, jbyteArray buffer, jint offset, jint size, jlong startOffset, jobject callback) {
  using namespace std::placeholders;

  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, handleField)
  );

  std::unique_ptr<void,std::function<void(void*)>> data(
    env->GetPrimitiveArrayCritical(buffer, nullptr),
    std::bind(&JNIEnv::ReleasePrimitiveArrayCritical, env, buffer, _1, JNI_ABORT)
  );

// FIXME: check for OOM. Wtf do we do then?
// FIXME: check that offset + size doesn't go beyond array end   
    
  const char* buf = reinterpret_cast<const char*>(data.get()) + offset;
 
  std::tuple<JNIEnv*,jobject*> userData{env, &callback};

  return lg_search(
    ptr,
    buf,
    buf + size,
    (uint64) startOffset,
    &userData,
    callbackShim
  );
}

JNIEXPORT void JNICALL Java_com_lightboxtechnologies_lightgrep_Lightgrep_lg_1closeout_1search(JNIEnv* env, jclass, jobject hCtx, jobject callback) {
  LG_HCONTEXT ptr = reinterpret_cast<LG_HCONTEXT>(
    env->GetLongField(hCtx, handleField)
  );

  std::tuple<JNIEnv*,jobject*> userData{env, &callback};

  lg_closeout_search(ptr, &userData, callbackShim);
}
