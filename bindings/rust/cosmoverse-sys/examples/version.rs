
use std::ffi::CStr;
extern "C" { fn cosmoverse_version_c() -> *const i8; }
fn main(){
    unsafe { 
        let s = cosmoverse_version_c();
        let v = CStr::from_ptr(s).to_string_lossy();
        println!("cosmoverse version: {}", v);
    }
}
