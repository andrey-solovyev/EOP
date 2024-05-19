@echo off

mkdir tmp
cd tmp

:: oatpp
git clone --depth=1 https://github.com/oatpp/oatpp
cd oatpp
git fetch --tags
git checkout 1.3.0-latest --
mkdir build
cd build
cmake -DOATPP_DISABLE_ENV_OBJECT_COUNTERS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOATPP_BUILD_TESTS=OFF ..
cmake --build .   --target install
cd ..
cd ..

:: oatpp-swagger
git clone --depth=1 https://github.com/oatpp/oatpp-swagger
cd oatpp-swagger
git fetch --tags
git checkout 1.3.0-latest --
mkdir build
cd build
cmake -DOATPP_DISABLE_ENV_OBJECT_COUNTERS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOATPP_BUILD_TESTS=OFF ..
cmake --build .   --target install
cd ..
cd ..

:: oatpp-postgresql
git clone --depth=1 https://github.com/oatpp/oatpp-postgresql
cd oatpp-postgresql
git fetch --tags
git checkout 1.3.0 --
mkdir build
cd build
cmake -DOATPP_DISABLE_ENV_OBJECT_COUNTERS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOATPP_BUILD_TESTS=OFF ..
cmake --build .   --target install
cd ..
cd ..



