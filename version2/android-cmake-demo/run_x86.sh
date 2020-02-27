#!/bin/sh

export ANDROID_SDK=$HOME/Android/Sdk
export ANDROID_NDK=$HOME/Android/ndk/21.0.6113669
export QT_ROOT=/opt/Qt/5.12.6

rm -rf build
mkdir build
cd build

cmake \
    -DCMAKE_SYSTEM_NAME=ANDROID \
    -DCMAKE_SYSTEM_VERSION=22 \
		-DCMAKE_PREFIX_PATH=/opt/Qt/5.12.6/gcc_64 \
		-DBUILD_X86=1 \
		-DWRITE_TO_FILE=0 \
		..

VERBOSE=1 make

