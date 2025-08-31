
class Cosmoverse < Formula
  desc "COSMOVERSE ENGINE core C++ library and CLI"
  homepage "https://github.com/your-org/cosmoverse-engine"
  url "https://github.com/your-org/cosmoverse-engine/archive/refs/tags/v1.0.0.tar.gz"
  sha256 "PUT_SHA256_HERE"
  license "Apache-2.0"
  depends_on "cmake" => :build
  def install
    system "cmake", "-S", ".", "-B", "build", "-DCMAKE_BUILD_TYPE=Release"
    system "cmake", "--build", "build", "-j"
    system "cmake", "--install", "build", "--prefix", prefix
  end
end
