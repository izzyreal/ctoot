rmdir C:\Users\Izmar\git\ctoot\build\32bit /s /q

md C:\Users\Izmar\git\ctoot\build\32bit

cd C:\Users\Izmar\git\ctoot\build\32bit
conan install -s build_type=Debug -s arch=x86 -g cmake_multi ../../ ctoot/0.1@izmar/dev --build missing
conan install -s build_type=Release -s arch=x86 -g cmake_multi ../../ ctoot/0.1@izmar/dev --build missing
conan build ../../
conan create ../../ ctoot/0.1@izmar/dev
