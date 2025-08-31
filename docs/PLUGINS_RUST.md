
# Rust plugin sample
Build the sample as a shared library (`cdylib`) and run it via the CLI:

```bash
cd plugins/rust_sample
cargo build --release
# On Linux:
cosmoverse plugin target/release/libcosmoverse_rust_sample.so --ping
# On macOS:
cosmoverse plugin target/release/libcosmoverse_rust_sample.dylib --ping
# On Windows (PowerShell):
cosmoverse.exe plugin target\release\cosmoverse_rust_sample.dll --ping
```
