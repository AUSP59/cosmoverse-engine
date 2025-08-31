
using System;
class Program {
  static void Main() {
    Console.WriteLine(CosmoverseNative.Version());
    Console.WriteLine(CosmoverseNative.Fnv1a64(System.Text.Encoding.UTF8.GetBytes("hello")).ToString("x"));
  }
}
