@echo off
set DIR=%~dp0
set BUILD_DIR="%DIR%\build\VS2015\Win64\Debug"
set SOURCE_DIR="%DIR%"

md "%BUILD_DIR%"
pushd "%BUILD_DIR%"
   cmake ^
   -DCOMPILER_ID=VS2015^
   -DBIN_PATH_POSTFIX=VS2015/Win64^
   -DCMAKE_BUILD_TYPE=Debug^
   -G"Visual Studio 14 2015 Win64"^
    "%SOURCE_DIR%"
popd

cmake --build "%BUILD_DIR%" --config Debug
