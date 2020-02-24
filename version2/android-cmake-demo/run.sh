#!/bin/sh

export ANDROID_SDK=$HOME/Android/Sdk
export ANDROID_NDK=$HOME/Android/ndk/21.0.6113669
export QT_ROOT=/opt/Qt/5.12.6

rm -rf build
mkdir build
cd build

cmake \
    -DCMAKE_CXX_COMPILER=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi22-clang++ \
    -DCMAKE_C_COMPILER=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi22-clang \
    -DCMAKE_SYSTEM_NAME=ANDROID \
    -DCMAKE_SYSTEM_VERSION=22 \
		..

make

make android-cmake-demo-apk

make android-cmake-demo-apk-install

