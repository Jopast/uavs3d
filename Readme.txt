# uavs3d
 uavs3d is an opensource avs3 decoder. 
 features:
 1) supports to compile on Android/IOS/Windows/Linux/MacOS systems.
 2) optimized for ARM32/ARM64/X86 architecture CPUs.
 3) supports decoding 8bit and 10bit streams on all supported platforms.

# compilation
8bit version compiled default. To support 10bit streams decoding, edit source/decore/com_def.h :
#define BIT_DEPTH 10

if enable arm64 or armv7 assembly codes for 10bit, edit source/decore/arm64/def_arm64.S or source/decore/armv7/def_armv7.S :
#define COMPILE_10BIT 1

## windows
Prerequisites:
  Visual Studio 2017

build:
  1. ./version.bat (to generate version.h)
  2. solution file: build/x86_windows/uavs3d.sln 

## linux/mac
Prerequisites:
  1. gawk (http://www.gnu.org/software/gawk/)
  2. CMake (https://cmake.org) version 2.8 or higher
  
Build:
  1. ./version.sh
  2. mkdir build/linux
  3. cd build/linux && cmake ../..
  4. make && make install

to build shared library, edit source/CMakeLists.txt:
  add_library(uavs3d SHARED ${DIR_UAVS3D_SRC} ${DIR_X86_256_SRC} ${DIR_X86_SRC})

## ios
Prerequisites:
  XCode

Build:
1. build test application
  a. ./version.sh (generate the version.h)
  b. xcode solution file: build/ios/uavs3d.xcodeproj

2. build static library
  a. create new xcode project, and select project type: IOS->Framework & Library->Cocoa Touch Static Library.
  b. add source files:
    source/decoder/*.c
    source/decoder/*.h
    source/decore/*.c
    source/decore/*.h
    source/decore/arm64/*
    source/decore/armv7/*
  c. configure architectures option, and build.

## android
Prerequisites:
  Android NDK (https://developer.android.google.cn/ndk/downloads/).

Build ndk library or executable file: 
  a. ./version.sh (generate the version.h)
  b. cd build/android/ndk/jni
  c. $NDK_PATH/ndk-build  

  The shared library generated default. 
  To build static library, edit Android.mk as below :
    #include $(BUILD_SHARED_LIBRARY)
    include $(BUILD_STATIC_LIBRARY)
    #include $(BUILD_EXECUTABLE)

  To build executable file, edit Android.mk as below:
  1) #include $(BUILD_SHARED_LIBRARY)
      #include $(BUILD_STATIC_LIBRARY)
      include $(BUILD_EXECUTABLE)
  2) #if build_executable
      LOCAL_CFLAGS    += -pie -fPIE
      LOCAL_LDFLAGS   += -pie -fPIE
      uavs3d_srcs_test+= $(SRC_PATH)/../test/utest.c  
      #endif

  The default build architecture is arm64-v8a. To switch to armv7a, do as below:
  1. edit Application.mk :
     APP_ABI := armeabi-v7a
     #APP_ABI := arm64-v8a
   
  2. edit Android.mk : 
    #if build armv7a
    LOCAL_CFLAGS 	+= -mfpu=neon 
    include $(LOCAL_PATH)/uavs2d.arm32.mk
    #elif build arm64
    #include $(LOCAL_PATH)/uavs2d.arm64.mk
    #endif

# Run test
## window/linux/mac/android
sample: ./uavs3d -i input.avs3 -o output.yuv -t 8 -l 2 -s 1

Arguments:
-h (--help)             Print this help
-v (--version)         Version information
-i (--input)             Input file
-o (--output)         Output file
-l (--loglevel)         Log level (0: no message; 1: seq level message; 2: frame level log (default)

-t (--threads)         Number of frame-level threads
-f (--frames)          Total frames to decode
-s (--check_md5)   Enable to check md5 or not

## ios
  Edit build/ios/uavs3d/main.m to configure decoding options.

# Header files for the uavs3d library
  source/decoder/uavs3d.h

