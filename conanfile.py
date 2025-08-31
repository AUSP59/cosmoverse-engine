
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
class CosmoverseConan(ConanFile):
    name = "cosmoverse"
    version = "1.0.0"
    license = "Apache-2.0"
    url = "https://github.com/your-org/cosmoverse-engine"
    description = "COSMOVERSE ENGINE core C++ library and CLI"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "*"
    def layout(self):
        cmake_layout(self)
    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_BUILD_TYPE"] = self.settings.build_type or "Release"
        tc.generate()
    def build(self):
        cm = CMake(self)
        cm.configure()
        cm.build()
    def package(self):
        cm = CMake(self)
        cm.install()
    def package_info(self):
        self.cpp_info.libs = ["cosmoverse"]
