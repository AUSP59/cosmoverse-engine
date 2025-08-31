
using System;
using System.Runtime.InteropServices;

public static class CosmoverseNative {
#if WINDOWS
  const string LIB = "cosmoverse.dll";
#elif OSX
  const string LIB = "libcosmoverse.dylib";
#else
  const string LIB = "libcosmoverse.so";
#endif

  [DllImport(LIB, CallingConvention=CallingConvention.Cdecl)]
  private static extern IntPtr cosmoverse_version_c();

  [DllImport(LIB, CallingConvention=CallingConvention.Cdecl)]
  private static extern UInt64 cosmoverse_fnv1a64_c(byte[] data, UIntPtr len);

  public static string Version() => Marshal.PtrToStringUTF8(cosmoverse_version_c()) ?? "";

  public static UInt64 Fnv1a64(byte[] data) => cosmoverse_fnv1a64_c(data, (UIntPtr)data.Length);
}
