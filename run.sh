#!/bin/sh

CodeDir="code"
OutputDir="build_android"
ApkDir="${OutputDir}/apk"

AndroidDir=/home/user/Android/Sdk
AndroidCmdDir=${AndroidDir}/build-tools/29.0.3
JAVA_HOME=/home/user/.local/jdk-11.0.6
NDK=/home/user/Android/Sdk/ndk/21.0.6113669
CLANG_NDK=${NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin/x86_64-linux-android29-clang++
LLD=${NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin/x86_64-linux-android-ld
COMPILERS=${NDK}/toolchains/llvm/prebuilt/linux-x86_64/bin

mkdir -p "${OutputDir}"
mkdir -p "${ApkDir}/lib/x86"

CompilerFlags="-I ${NDK}/sources/android/support/include" 
CompilerFlags="-I ${NDK}/sources/cxx-stl/llvm-libc++/include ${CompilerFlags}"
CompilerFlags="-I ${NDK}/sources/cxx-stl/llvm-libc++abi/include ${CompilerFlags}"
CompilerFlags="-I ${NDK}/toolchains/llvm/prebuilt/linux-x86_64/lib64/clang/9.0.8/include ${CompilerFlags}"
CompilerFlags="-I ${NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include ${CompilerFlags}"
CompilerFlags="-I ${NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/x86_64-linux-android ${CompilerFlags}"
CompilerFlags="-D__ANDROID_API__=29 -g2 -gdwarf-2 -Wall -O0 -x c++ ${CompilerFlags}"

#LinkerFlags="-landroid_support -lc++_static -lc++abi -llog -landroid -lGLESv1_CM -lEGL"
LinkerFlass="-stdlib=libc++ ${LinkerFlags}"
LinkerFlags="-shared ${OutputDir}/android_native_app_glue.o ${OutputDir}/main.o ${LinkerFlags}"

gcctoolchain="-gcc-toolchain ${NDK}/toolchains/x86-4.9/prebuilt/linux-x86_64"
x86CommonFlags="-fdiagnostics-format=msvc"
x86CommonFlags="--sysroot=\"${NDK}/platforms/android-29/arch-x86_64\" ${x86CommonFlags}" 

x86CompilerFlags="-I \"${NDK}/platforms/android-29/arch-x86_64/usr/include\"" # ??

x86LinkerFlags="-rpath-link=${NDK}/platforms/android-29/arch-x86_64/usr/lib64" 
#x86LinkerFlags="-Wl,-L${NDK}/platforms/android-29/arch-x86_64/usr/lib64 ${x86LinkerFlags}"
x86LinkerFlags="-L${NDK}/toolchains/x86_64-4.9/prebuilt/linux-x86_64/lib/gcc/x86_64-linux-android/4.9.x ${x86LinkerFlags}"
x86LinkerFlags="-L${NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/x86_64-linux-android/29 ${x86LinkerFlags}"
x86LinkerFlags="-L${NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/x86_64-linux-android ${x86LinkerFlags}"
x86LinkerFlags="-L${NDK}/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/lib/i686-linux-android ${x86LinkerFlags}"
x86LinkerFlags="-L${NDK}/sources/cxx-stl/llvm-libc++/libs/x86_64 ${x86LinkerFlags}"

${CLANG_NDK} -B${COMPILERS} -v -c -o "${OutputDir}/android_native_app_glue.o" ${CodeDir}/android_native_app_glue.c ${x86CommonFlags} ${x86CompilerFlags} ${CompilerFlags} ${gcctoolchain}
${CLANG_NDK} -B${COMPILERS} -v -c -o "${OutputDir}/main.o" ${CodeDir}/main.cpp ${x86CommonFlags} ${x86CompilerFlags} ${CompilerFlags} ${gcctoolchain}
#${CLANG_NDK} -B${COMPILERS} -v -o "${ApkDir}/lib/x86/libnative-activity.so" ${x86LinkerFlags} ${x86CommonFlags} ${LinkerFlags}
${LLD} -v -o "${ApkDir}/lib/x86/libnative-activity.so" ${x86LinkerFlags} ${x86CommonFlags} ${LinkerFlags}

"${JAVA_HOME}/bin/keytool" -genkey -keystore ${OutputDir}/debug.keystore -storepass android -alias androiddebugkey -dname "CN=company name, OU=0, O=Dream, L=CityName, S=StateProvince, C=Country" -keyalg RSA -keysize 2048 -validity 20000

"${AndroidCmdDir}/aapt" package --debug-mode -f -M ${CodeDir}/AndroidManifest.xml -I "${AndroidDir}/platforms/android-29/android.jar" -F AndroidTest.unaligned.apk ${ApkDir}
"${JAVA_HOME}/bin/jarsigner" -sigalg SHA1withRSA -digestalg SHA1 -storepass android -keypass android -keystore ${OutputDir}/debug.keystore -signedjar AndroidTest.signed.apk AndroidTest.unaligned.apk androiddebugkey
"${AndroidCmdDir}/zipalign" 4 AndroidTest.signed.apk AndroidTest.apk
