
list(APPEND CMAKE_MODULE_PATH /tmp/sdk-6.5/SDK-B288/usr/share/cmake/modules)
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
set(QT_QMAKE_EXECUTABLE "/tmp/sdk-6.5/SDK-B288/usr/local/qt5/bin/qmake")

set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -pipe -fomit-frame-pointer -fPIC -march=native -mtune=native " CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O2 -pipe -fomit-frame-pointer -fPIC -march=native -mtune=native " CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE " -s" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "-s" CACHE STRING "" FORCE)

set(CMAKE_LINKER_FLAGS "-Wl,-z,defs" CACHE STRING "" FORCE)

SET(CMAKE_C_COMPILER gcc)
SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_ASM_COMPILER gcc)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -pipe -fno-omit-frame-pointer -fPIC" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "" CACHE STRING "" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "" CACHE STRING "" FORCE)

set(CMAKE_INSTALL_PREFIX "/tmp/sdk-6.5/SDK-B288/usr/local" CACHE PATH "Installation Prefix")
add_definitions(-DEMULATOR -DPLATFORM_NX)

set(PB_PLATFORM "PC" CACHE STRING  "ARM|PC Readonly!") 
set(PBRES "/tmp/sdk-6.5/SDK-B288/usr/bin/pbres")

