#include <stdlib.h>
#include <stdlib.h>  /* abs */
#include "nan.h"

using namespace node;

namespace {

NAN_METHOD(ArrayAbs) {
  int *arr = reinterpret_cast<int *>(Buffer::Data(info[0].As<v8::Object>()));
#if defined(V8_MAJOR_VERSION) && (V8_MAJOR_VERSION > 4 ||                      \
  (V8_MAJOR_VERSION == 4 && defined(V8_MINOR_VERSION) && V8_MINOR_VERSION > 3))
  v8::Isolate *isolate = info.GetIsolate();
  uint32_t length = info[1]->Uint32Value(
    isolate->GetCurrentContext()).FromJust();
#else
  uint32_t length = info[1]->Uint32Value();
#endif
  for (uint32_t i = 0; i < length; i++) {
    *(arr + i) = abs(arr[i]);
  }
}

void
Initialize(
  v8::Local<v8::Object> target,
  v8::Local<v8::Value> module,
  void* priv) {
  Nan::HandleScope scope;
  Nan::SetMethod(target, "arrayAbs", ArrayAbs);
}

} // anonymous namespace

NODE_MODULE(native_tests, Initialize);
