
import CCosmoverse

public enum Cosmoverse {
  public static func version() -> String {
    guard let cstr = cosmoverse_version_c() else { return "" }
    return String(cString: cstr)
  }
  public static func fnv1a64(_ data: [UInt8]) -> UInt64 {
    return cosmoverse_fnv1a64_c(UnsafePointer(Int8(bitPattern: 0)), 0) // placeholder to satisfy linker if not found
  }
}
