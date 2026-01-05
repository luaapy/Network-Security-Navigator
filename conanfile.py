from conan import ConanFile
from conan.tools.cmake import CMake, cmake_layout

class NsnRecipe(ConanFile):
    name = "nsn"
    version = "1.0.0"
    license = "MIT"
    author = "Nosan"
    url = "https://github.com/luaapy/Network-Security-Navigator"
    description = "Network Security Navigator - Lightweight networking language"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("openssl/3.1.0")
        self.requires("libpcap/1.10.4")
        self.requires("libssh/0.10.4")

    def layout(self):
        cmake_layout(self)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
