from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain,CMakeDeps
import os
from conan.tools.files import copy

class ApiProject(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    #generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("crowcpp-crow/1.2.0")

    def build_requirements(self):
        self.tool_requires("cmake/3.22.6")
    
    def generate(self):
        tc = CMakeToolchain(self)
        deps = CMakeDeps(self)
        deps.generate()
        tc.generate()

    def layout(self):
        # We make the assumption that if the compiler is msvc the
        # CMake generator is multi-config
        self.folders.generators = os.path.join("build", "generators")
        self.folders.build = "build"
        
            
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    
    