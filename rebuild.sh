rm -rf ~/.conan/data/ctoot

mkdir -p ~/git/ctoot/build/Release
mkdir -p ~/git/ctoot/build/Debug

rm -rf ~/git/ctoot/build/Release/*
rm -rf ~/git/ctoot/build/Debug/*

cd ~/git/ctoot/build/Debug
conan install -s build_type=Debug ../../ ctoot/0.1@izmar/dev --build missing
conan build ../../

cd ~/git/ctoot/build/Release
conan install -s build_type=Release ../../ ctoot/0.1@izmar/dev --build missing
conan build ../../

conan create ../../ ctoot/0.1@izmar/dev
