from conans import ConanFile, CMake, tools


class CtootConan(ConanFile):
    requires = "moduru/0.1@izmar/testing"
    name = "ctoot"
    version = "0.1"
    license = "WTFPL"
    author = "Izmar Verhage maybesomeday@iwilltell.com"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "A messy collection of utilities"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = ["CMakeLists.txt", "src/*"]

    _source_subfolder = "src"
    _build_subfolder = "build"
	
    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure(build_folder=self._build_subfolder)
        return cmake
		
    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
		
    def package(self):
        self.copy(pattern="*.h", dst="include", src=self._source_subfolder)
        self.copy(pattern="*.hpp", dst="include", src=self._source_subfolder)
        self.copy(pattern="*.dll", dst="bin", keep_path=False)
        self.copy(pattern="*.lib", dst="lib", keep_path=False)
        self.copy(pattern="*.a", dst="lib", keep_path=False)
        self.copy(pattern="*.so*", dst="lib", keep_path=False)
        self.copy(pattern="*.dylib", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
