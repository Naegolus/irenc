#!/bin/sh

mkdir -p build/build-native
cd build/build-native
../../configure
cd ../..

mkdir -p build/build-win64
cd build/build-win64
../../configure --host=i686-w64-mingw32 CFLAGS="-static-libgcc" CXXFLAGS="-static-libstdc++"
cd ../..

mkdir -p build/build-rpi
cd build/build-rpi
../../configure --host=arm-linux-gnueabihf
cd ../..

mkdir -p build/build-or_os
cd build/build-or_os
cd ../..

mkdir -p build/build-or_bm
cd build/build-or_bm
cd ../..
