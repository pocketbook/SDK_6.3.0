#!/bin/sh

script_path=$(cd $(dirname $0) && pwd)

SDK_ROOT=`realpath ${script_path}/../usr/`
mkdir -p ${SDK_ROOT}/../share/cmake

CMAKE_TOOLCHAIN_FILE_ARM=${SDK_ROOT}/../share/cmake/arm_conf.cmake
TARGET_ARM='arm-obreey-linux-gnueabi'

CMAKE_TOOLCHAIN_FILE_PC=${SDK_ROOT}/../share/cmake/pc_conf.cmake

#Update ARM config
echo "\
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1.0)
set(CMAKE_SYSTEM_PROCESSOR armv7a)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_FIND_ROOT_PATH \"${SDK_ROOT}/${TARGET_ARM}/sysroot/\")
set(CMAKE_INCLUDE_PATH \"${CMAKE_FIND_ROOT_PATH}/usr/include\")
message(\"CMAKE_FIND_ROOT_PATH=\${CMAKE_FIND_ROOT_PATH}\")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(FREETYPE_INCLUDE_DIRS \"${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/include/freetype2\")
list(APPEND CMAKE_MODULE_PATH \"${SDK_ROOT}/share/cmake/modules\")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
#set(PKG_CONFIG_EXECUTABLE -pkg-config)
set(QT_QMAKE_EXECUTABLE \"${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/qt5/bin/qmake\")
set(CMAKE_PREFIX_PATH \"${SDK_ROOT}/${TARGET_ARM}/sysroot/ebrmain/lib/cmake\")

set(CMAKE_C_COMPILER \"${SDK_ROOT}/bin/${TARGET_ARM}-clang\")
set(CMAKE_CXX_COMPILER \"${SDK_ROOT}/bin/${TARGET_ARM}-clang++\")
set(CMAKE_C_FLAGS \"-fsigned-char -Werror-return-type\" CACHE STRING \"\" FORCE)
set(CMAKE_CXX_FLAGS \"-fsigned-char -Werror-return-type\" CACHE STRING \"\" FORCE)
#set(CMAKE_C_COMPILER \"${SDK_ROOT}/bin/${TARGET_ARM}-gcc\")
#set(CMAKE_CXX_COMPILER \"${SDK_ROOT}/bin/${TARGET_ARM}-g++\")
#set(CMAKE_C_FLAGS \"-fsigned-char \" CACHE STRING \"\" FORCE)
#set(CMAKE_CXX_FLAGS \"-fsigned-char \" CACHE STRING \"\" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE \"-DNDEBUG -O2 -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp \" CACHE STRING \"\" FORCE)
set(CMAKE_C_FLAGS_RELEASE \"-DNDEBUG -O2 -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp \" CACHE STRING \"\" FORCE)
set(CMAKE_C_FLAGS_DEBUG \"-DDEBUG -O0 -g -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp \" CACHE STRING \"\" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG \"-DDEBUG -O0 -g -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp \" CACHE STRING \"\" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE \"-s\" CACHE STRING \"\" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE \"-s\" CACHE STRING \"\" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS \"-Wl,-z,defs\" CACHE STRING \"\" FORCE)

add_definitions(-DPLATFORM_FC)
set(PB_PLATFORM \"ARM\" CACHE STRING \"ARM|PC Readonly!\")

set(CMAKE_INSTALL_PREFIX \"${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/local\" CACHE PATH \"Installation Prefix\")
set(CMAKE_BUILD_TYPE Release CACHE STRING \"Debug|Release|RelWithDebInfo|MinSizeRel\")
set(ENV{PKG_CONFIG_DIR} \"\")
set(ENV{PKG_CONFIG_LIBDIR} \${CMAKE_FIND_ROOT_PATH}/usr/lib/pkgconfig)
set(ENV{PKG_CONFIG_SYSROOT_DIR} \${CMAKE_FIND_ROOT_PATH})
set(ENV{LD_LIBRARY_PATH} ${SDK_ROOT}/lib)
list(APPEND PB_LINK_DIRECTORIES \"${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/lib\")
list(APPEND PB_LINK_DIRECTORIES \"${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/local/lib\")
list(APPEND PB_INCLUDE_DIRECTORIES \"${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/include\")
set(PBRES \"${SDK_ROOT}/bin/pbres\")
" > ${CMAKE_TOOLCHAIN_FILE_ARM}

#Update PC config
echo "\

list(APPEND CMAKE_MODULE_PATH "${SDK_ROOT}/share/cmake/modules")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
set(QT_QMAKE_EXECUTABLE \"${SDK_ROOT}/local/qt5/bin/qmake\")

set(CMAKE_CXX_FLAGS_RELEASE \"-DNDEBUG -O2 -pipe -fomit-frame-pointer -fPIC -march=native -mtune=native \" CACHE STRING \"\" FORCE)
set(CMAKE_C_FLAGS_RELEASE \"-DNDEBUG -O2 -pipe -fomit-frame-pointer -fPIC -march=native -mtune=native \" CACHE STRING \"\" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE \" -s\" CACHE STRING \"\" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE \"-s\" CACHE STRING \"\" FORCE)

set(CMAKE_LINKER_FLAGS \"-Wl,-z,defs\" CACHE STRING \"\" FORCE)

SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_ASM_COMPILER gcc)

set(CMAKE_CXX_FLAGS_DEBUG \"-ggdb -O0 -pipe -fno-omit-frame-pointer -fPIC\" CACHE STRING \"\" FORCE)
set(CMAKE_C_FLAGS_DEBUG \"\${CMAKE_CXX_FLAGS_DEBUG}\" CACHE STRING \"\" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG \"\" CACHE STRING \"\" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG \"\" CACHE STRING \"\" FORCE)

set(CMAKE_INSTALL_PREFIX \"${SDK_ROOT}/local\" CACHE PATH \"Installation Prefix\")
add_definitions(-DEMULATOR -DPLATFORM_NX)

set(PB_PLATFORM \"PC\" CACHE STRING  \"ARM|PC Readonly!\") 
set(PBRES \"${SDK_ROOT}/bin/pbres\")
" > ${CMAKE_TOOLCHAIN_FILE_PC}

libcurl=libcurl-openssl
if [ -n "$PB_LIBCURL" ]; then
	libcurl=$PB_LIBCURL
fi
if [ -d ${SDK_ROOT}/${TARGET_ARM}/sysroot/${libcurl} ]; then
	echo "Apply ${libcurl} to build"
	if [ "`cat ${SDK_ROOT}/${TARGET_ARM}/sysroot/${libcurl}/usr/lib/libcurl.so.4|md5sum -`" = "`cat ${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/lib/libcurl.so.4|md5sum -`" ]
	then
		echo "Already applied"
	else
	cp -rvf ${SDK_ROOT}/${TARGET_ARM}/sysroot/${libcurl}/usr/bin ${SDK_ROOT}/${TARGET_ARM}/sysroot/${libcurl}/usr/lib ${SDK_ROOT}/${TARGET_ARM}/sysroot/${libcurl}/usr/include  ${SDK_ROOT}/${TARGET_ARM}/sysroot/usr/
	fi
else
	echo "Warning: PB_LIBCURL=$PB_LIBCURL, but ${SDK_ROOT}/${TARGET_ARM}/sysroot/${libcurl} not exist"
fi
