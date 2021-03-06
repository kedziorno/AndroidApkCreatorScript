#!/bin/sh

export ANDROID_SDK=$HOME/Android/Sdk
export ANDROID_NDK=$HOME/Android/Sdk/ndk/21.0.6113669
#export ANDROID_NDK=$ANDROID_NDK_ROOT
export QT_ROOT=/opt/Qt/5.12.6
export VC_PROJECT_NAME=votecastle-android

rm -rf build
mkdir build
cd build

cmake \
    -DCMAKE_CXX_COMPILER=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi22-clang++ \
    -DCMAKE_C_COMPILER=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi22-clang \
    -DCMAKE_SYSTEM_NAME=ANDROID \
    -DCMAKE_SYSTEM_VERSION=22 \
		-DCMAKE_PREFIX_PATH=/opt/Qt/5.12.6/android_armv7 \
		-DBUILD_ARM=1 \
		-DWRITE_TO_FILE=0 \
		..

VERBOSE=1 make

make $VC_PROJECT_NAME-apk

make $VC_PROJECT_NAME-apk-install

