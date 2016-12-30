@echo off
set DIR=%~dp0
set BUILD_DIR="%DIR%\build\VS2015"
set SOURCE_DIR="%DIR%"

md "%BUILD_DIR%"
pushd "%BUILD_DIR%"
   cmake ^
   -DCMAKE_BUILD_TYPE=Debug^
   -G"Visual Studio 14 2015"^
    "%SOURCE_DIR%"
popd

cmake --build "%BUILD_DIR%" --config Debug
