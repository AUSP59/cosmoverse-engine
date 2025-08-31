
package org.cosmoverse;
public class Cosmoverse {
  static { System.loadLibrary("cosmoverse"); }
  private static native String cosmoverse_version_c(); // via JNI shim (not provided)
  public static String version() { return cosmoverse_version_c(); }
}
