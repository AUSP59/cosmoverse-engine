
// SPDX-License-Identifier: Apache-2.0
#include <napi.h>
extern "C" {
  const char* cosmoverse_version_c();
  unsigned long long cosmoverse_fnv1a64_c(const char* data, size_t len);
}
Napi::Value Version(const Napi::CallbackInfo& info){
  return Napi::String::New(info.Env(), cosmoverse_version_c());
}
Napi::Value Fnv1a64(const Napi::CallbackInfo& info){
  auto env = info.Env();
  if (info.Length()<1 || !info[0].IsBuffer()) return env.Null();
  auto buf = info[0].As<Napi::Buffer<uint8_t>>();
  auto h = cosmoverse_fnv1a64_c((const char*)buf.Data(), buf.Length());
  return Napi::BigInt::New(env, (uint64_t)h);
}
Napi::Object Init(Napi::Env env, Napi::Object exports){
  exports.Set("version", Napi::Function::New(env, Version));
  exports.Set("fnv1a64", Napi::Function::New(env, Fnv1a64));
  return exports;
}
NODE_API_MODULE(cosmoverse, Init)
