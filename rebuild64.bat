rmdir C:\Users\Izmar\git\ctoot\build\64bit /s /q

md C:\Users\Izmar\git\ctoot\build\64bit

cd C:\Users\Izmar\git\ctoot\build\64bit
conan install -s build_type=Debug -g cmake_multi ../../ ctoot/0.1@izmar/dev --build missing
conan install -s build_type=Release -g cmake_multi ../../ ctoot/0.1@izmar/dev --build missing
conan build ../../
conan install -s build_type=Debug -g cmake_multi ../../ ctoot/0.1@izmar/dev
conan build ../../
conan create ../../ ctoot/0.1@izmar/dev