#!/bin/sh

make -C build/build-native
make -C build/build-win64
make -C build/build-rpi
#make -C build/build-or_os
#make -C build/build-or_bm

#make -C build/build-native distcheck
