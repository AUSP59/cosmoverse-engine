
// SPDX-License-Identifier: Apache-2.0
use std::ffi::{CString};
use std::os::raw::{c_char, c_int};

#[repr(C)]
pub struct CosmoPluginInfo {
    pub abi_version: i32,
    pub name: *const c_char,
}

#[no_mangle]
pub extern "C" fn cosmoverse_plugin_info() -> *const CosmoPluginInfo {
    // Keep a static so the pointer stays valid.
    static mut NAME: Option<CString> = None;
    static mut INFO: Option<CosmoPluginInfo> = None;
    unsafe {
        if NAME.is_none() { NAME = Some(CString::new("rust-sample").unwrap()); }
        if INFO.is_none() {
            INFO = Some(CosmoPluginInfo { abi_version: 1, name: NAME.as_ref().unwrap().as_ptr() });
        }
        INFO.as_ref().unwrap()
    }
}

#[no_mangle]
pub extern "C" fn cosmoverse_plugin_run(argc: c_int, _argv: *const *const c_char) -> c_int {
    // Return a deterministic code for demo
    (argc % 2) as c_int
}
