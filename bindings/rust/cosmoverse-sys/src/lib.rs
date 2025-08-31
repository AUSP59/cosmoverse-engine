use libc::{c_char, size_t, c_ulonglong};
extern "C"{
  pub fn cosmoverse_version_c()->*const c_char;
  pub fn cosmoverse_fnv1a64_c(data:*const c_char, len:size_t)->c_ulonglong;
}
