from conans import ConanFile, CMake

class Pkg(ConanFile):
    name = "ctoot"
    version = "0.2"
    license = "GPL-3.0"
    settings = "os", "compiler", "arch", "build_type"
    generators = "cmake"
    exports_sources = "src/*"
    requires = ("moduru/0.2@izmar/dev", "catch2/2.13.8")
    url = "https://github.com/izzyreal/ctoot.git"
	
    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="src")
        cmake.build()

    def package(self):
        self.copy("*.h", src="src/main", dst="include")
        self.copy("*.hpp", src="src/main", dst="include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs=["ctoot"]
