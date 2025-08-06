from conan import ConanFile
from conan.tools.cmake import cmake_layout

class StrongTypeConanFile(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"
    
    def requirements(self):
        pass

    def build_requirements(self):
        self.test_requires("catch2/3.8.1")
        self.test_requires("nanobench/4.3.11")
        
    def layout(self):
        cmake_layout(self)