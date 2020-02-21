cmake_minimum_required(VERSION 3.1)

project(android-cmake-demo LANGUAGES CXX)

set(Qt5_DIR "/opt/Qt/5.12.6/android_armv7/lib/cmake/Qt5")
set(CMAKE_BUILD_TYPE "release")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

include(cmake/qt-android-mk-apk.cmake)

SET(ANDROID_SDK_ROOT "/home/user/Android/Sdk/")
SET(CMAKE_ANDROID_ARCH_ABI "armeabi-v7a")
SET(CMAKE_ANDROID_STL_TYPE "gnustl_shared")
SET(CMAKE_SYSTEM_NAME "Android")
SET(CMAKE_SYSTEM_VERSION 16)
SET(CMAKE_ANDROID_NDK "/home/user/Android/Sdk/ndk/21.0.6113669")
SET(APK_NDK_TOOLCHAIN_PREFIX "llvm")
SET(CMAKE_CXX_ANDROID_TOOLCHAIN_MACHINE "llvm")
SET(CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION "4.9")
SET(CMAKE_ANDROID_NDK_TOOLCHAIN_HOST_TAG "linux-x86_64")
SET(STDCPP_PATH "/home/user/Android/Sdk/ndk/21.0.6113669/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a/libc++_shared.so")

#if(ANDROID)
#    add_library(${PROJECT_NAME} SHARED "main.cpp" "qml.qrc")
#else()
    add_executable(${PROJECT_NAME} "main.cpp" "qml.qrc")
#endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)

qt_android_build_apk(
    TARGET ${PROJECT_NAME}
    PACKAGE_NAME org.example.QmlCmakeDemo
    QML_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}
    ANDROID_EXTRA_FILES ${CMAKE_CURRENT_SOURCE_DIR}/android
)

