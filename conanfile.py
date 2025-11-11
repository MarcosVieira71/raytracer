from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain

class Pkg(ConanFile):
    name = "raytracer"
    version = "0.1"
    requires = (
        "glm/1.0.1",
        "stb/cci.20230920",
        "sdl/3.2.20",
        "llvm-openmp/20.1.6"
    )    
    generators = (CMakeDeps, CMakeToolchain)
    settings = "build_type"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
