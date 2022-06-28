set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1.0)
set(CMAKE_SYSTEM_PROCESSOR armv7a)
set(BUILD_SHARED_LIBS ON)
set(CMAKE_FIND_ROOT_PATH "/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/")
set(CMAKE_INCLUDE_PATH "/usr/include")
message("CMAKE_FIND_ROOT_PATH=${CMAKE_FIND_ROOT_PATH}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(FREETYPE_INCLUDE_DIRS "/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/usr/include/freetype2")
list(APPEND CMAKE_MODULE_PATH "/tmp/sdk-6.5/SDK-B288/usr/share/cmake/modules")
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
#set(PKG_CONFIG_EXECUTABLE -pkg-config)
set(QT_QMAKE_EXECUTABLE "/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/usr/qt5/bin/qmake")
set(CMAKE_PREFIX_PATH "/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/ebrmain/lib/cmake")

set(CMAKE_C_COMPILER "/tmp/sdk-6.5/SDK-B288/usr/bin/arm-obreey-linux-gnueabi-clang")
set(CMAKE_CXX_COMPILER "/tmp/sdk-6.5/SDK-B288/usr/bin/arm-obreey-linux-gnueabi-clang++")
set(CMAKE_C_FLAGS "-fsigned-char -Werror-return-type" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "-fsigned-char -Werror-return-type" CACHE STRING "" FORCE)
#set(CMAKE_C_COMPILER "/tmp/sdk-6.5/SDK-B288/usr/bin/arm-obreey-linux-gnueabi-gcc")
#set(CMAKE_CXX_COMPILER "/tmp/sdk-6.5/SDK-B288/usr/bin/arm-obreey-linux-gnueabi-g++")
#set(CMAKE_C_FLAGS "-fsigned-char " CACHE STRING "" FORCE)
#set(CMAKE_CXX_FLAGS "-fsigned-char " CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp " CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O2 -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp " CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG "-DDEBUG -O0 -g -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp " CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -O0 -g -pipe -fomit-frame-pointer -march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=softfp " CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "-s" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-s" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-z,defs" CACHE STRING "" FORCE)

add_definitions(-DPLATFORM_FC)
set(PB_PLATFORM "ARM" CACHE STRING "ARM|PC Readonly!")

set(CMAKE_INSTALL_PREFIX "/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/usr/local" CACHE PATH "Installation Prefix")
set(CMAKE_BUILD_TYPE Release CACHE STRING "Debug|Release|RelWithDebInfo|MinSizeRel")
set(ENV{PKG_CONFIG_DIR} "")
set(ENV{PKG_CONFIG_LIBDIR} ${CMAKE_FIND_ROOT_PATH}/usr/lib/pkgconfig)
set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_FIND_ROOT_PATH})
set(ENV{LD_LIBRARY_PATH} /tmp/sdk-6.5/SDK-B288/usr/lib)
list(APPEND PB_LINK_DIRECTORIES "/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/usr/lib")
list(APPEND PB_LINK_DIRECTORIES "/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/usr/local/lib")
list(APPEND PB_INCLUDE_DIRECTORIES "/tmp/sdk-6.5/SDK-B288/usr/arm-obreey-linux-gnueabi/sysroot/usr/include")
set(PBRES "/tmp/sdk-6.5/SDK-B288/usr/bin/pbres")

