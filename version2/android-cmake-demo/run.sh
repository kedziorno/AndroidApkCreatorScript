#!/bin/sh

export ANDROID_SDK=$HOME/Android/Sdk
export ANDROID_NDK=$HOME/Android/ndk/21.0.6113669
export QT_ROOT=/opt/Qt/5.12.6

rm -rf build
mkdir build
cd build

cmake \
    -DANDROID_SDK_ROOT=$ANDROID_SDK \
    -DCMAKE_ANDROID_ARCH_ABI=armeabi-v7a \
    -DCMAKE_CXX_COMPILER=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi22-clang++ \
    -DCMAKE_C_COMPILER=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi22-clang \
    -DCMAKE_PREFIX_PATH=$QT_ROOT/android_armv7/lib/cmake/Qt5/ \
    -DCMAKE_SYSTEM_NAME=Android \
    -DCMAKE_SYSTEM_VERSION=22 \
    -DQT_QMAKE_EXECUTABLE=$QT_ROOT/bin/qmake \
		..

make

make android-cmake-demo-apk

make android-cmake-demo-apk-install

