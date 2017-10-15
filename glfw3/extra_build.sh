#!/bin/bash

/mnt/big/work/mxe-linux/usr/bin/i686-w64-mingw32.static.posix-g++  -std=c++11 -O3 -DNDEBUG  -static-libgcc -static-libstdc++ -Wl,--whole-archive CMakeFiles/spring-launcher.dir/objects.a -Wl,--no-whole-archive  -o spring-launcher.exe -Wl,--out-implib,libspring-launcher.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/spring-launcher.dir/linklibs.rsp -lpthread -lssl -lnettle -lcrypto -lwldap32 -lws2_32 -lgdi32
