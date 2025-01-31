# Library MDF version 2.0

## Summary

The MDF library repository implements an interface against the ASAM Measurement Data File (MDF). 
It supports reading and writing of MDF files version 3 and 4. 
The release 2.0 of the project support reading and writing of MDF files up to version 4.2. 

- **MDF lib** is a C++ static library.
- **MDF lib test** is a C++ unit tests application for mdflib.
- **MDF library** is a C++ shared library, and it contains .NET (C++/CLI) Assembly(need to be built with msvc>=19.36).
- **MDF library example** is a C++ application that use MDF library as dll/so.
- **MDF library test net** is a C# unit tests application that use the .NET Assembly of MDF library.
- **MDF Viewer**. Simple GUI application that list the contents of an MDF file.
- **MDF gRPC Server**. Microservice for reading and writing of MDF files. On request.
- **MDF Python Library**. Basic reading and writing for Python friends. On request or use the ASAMMDF library.

The library and its applications, compiles/runs on Windows, Linux and Mac operating system.

## Installation

[Windows Install (exe)](https://github.com/ihedvall/mdflib/releases/download/v2.0.%2C0/mdflib.exe)

## Building

### With Devcontainer
1. Open the folder in VSCode
2. Reopen in Devcontainer
3. Use one of the steps below depending on what you're building. If you change what you want to build, delete the build folder with
`rm -rf build` before you run any command or just use different `build` folders for each of them.

#### GCC -> mdflib only.
1. `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake -D MDF_BUILD_SHARED_LIB=OFF -D CMAKE_MAKE_PROGRAM=make -D CMAKE_CXX_COMPILER=g++`
2. `cmake --build build`

#### GCC -> mdflib + mdflibrary.
1. `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake -D CMAKE_MAKE_PROGRAM=make -D CMAKE_CXX_COMPILER=g++`
2. `cmake --build build`

#### Clang -> mdflib only.
1. `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake -D MDF_BUILD_SHARED_LIB=OFF CMAKE_MAKE_PROGRAM=make -D CMAKE_CXX_COMPILER=clang++`
2. `cmake --build build`

#### Clang -> mdflib + mdflibrary.
1. `cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake -D CMAKE_MAKE_PROGRAM=make -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_CXX_FLAGS="-fPIC"`
2. `cmake --build build`

### Without Devcontainer

The project uses CMAKE for building. But mdflibrary_test_net is a Visual Studio build.

The following third-party libraries are used and needs to be downloaded and pre-built.

- ZLIB Library. Set the 'ZLIB_ROOT' variable to the ZLIB root path.
- EXPAT Library. Set the 'EXPAT_ROOT' variable to the ZLIB root path.
- Boost Library. Required if the GUI applications should be built.
- WxWidgets Library. Required if the GUI applications should be built.
- Google Test Library. Is required for running and build the unit tests.
- Doxygen's application. Is required if the documentation should be built.

Also, you can use [vcpkg](https://github.com/microsoft/vcpkg) to import the dependencies.

## Testing

1. Make sure you set `-D MDF_BUILD_TEST=ON`
2. cd build && ctest -C && cd ..

## License

The project uses the MIT license. See external LICENSE file in project root.

