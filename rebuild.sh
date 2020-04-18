rm -rf ~/.conan/data/ctoot
rm -rf ~/git/ctoot/build/Release/*

cd ~/git/ctoot/build/Release

conan install -s build_type=Release ../../ ctoot/0.1@izmar/dev --build missing
conan build ../../
conan create ../../ ctoot/0.1@izmar/dev