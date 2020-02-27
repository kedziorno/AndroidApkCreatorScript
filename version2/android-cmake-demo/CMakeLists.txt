cmake_minimum_required(VERSION 3.1)

project(android-cmake-demo LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "debug")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("/opt/Qt/5.12.6/android_armv7/include/QtWidgets")
find_package(Qt5 COMPONENTS Core Gui Quick Widgets REQUIRED)

include(cmake/qt-android-mk-apk.cmake)

SET(ANDROID_SDK_ROOT "$ENV{ANDROID_SDK}")
SET(CMAKE_ANDROID_ARCH_ABI "armeabi-v7a")
SET(CMAKE_ANDROID_STL_TYPE "gnustl_shared")
SET(CMAKE_SYSTEM_NAME "Android")
SET(CMAKE_ANDROID_NDK "/home/user/Android/Sdk/ndk/21.0.6113669")
SET(APK_NDK_TOOLCHAIN_PREFIX "llvm")
SET(CMAKE_CXX_ANDROID_TOOLCHAIN_MACHINE "llvm")
SET(CMAKE_ANDROID_NDK_TOOLCHAIN_VERSION "4.9")
SET(CMAKE_ANDROID_NDK_TOOLCHAIN_HOST_TAG "linux-x86_64")
SET(STDCPP_PATH "$ENV{ANDROID_NDK}/sources/cxx-stl/llvm-libc++/libs/armeabi-v7a/libc++_shared.so")

if(WRITE_TO_FILE)
add_definitions(-DWRITE_TO_FILE)
endif()
if(BUILD_ARM)
add_definitions(-DBUILD_ARM)
add_library(${PROJECT_NAME} SHARED "main.cpp" "widget.cpp" "monitor.cpp")
endif()
if(BUILD_X86)
add_definitions(-DBUILD_X86)
add_executable(${PROJECT_NAME} "main.cpp" "widget.cpp" "monitor.cpp")
endif()
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets Qt5::Quick)

if(BUILD_ARM)
qt_android_build_apk(
    TARGET ${PROJECT_NAME}
    PACKAGE_NAME org.example.QmlCmakeDemo
    QML_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}
    ANDROID_EXTRA_FILES ${CMAKE_CURRENT_SOURCE_DIR}/android
)
endif()

