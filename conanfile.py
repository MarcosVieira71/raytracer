from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain

class Pkg(ConanFile):
    name = "raytracer"
    version = "0.1"
    requires = "glm/1.0.1"
    generators = (CMakeDeps, CMakeToolchain)
    settings = "build_type"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
