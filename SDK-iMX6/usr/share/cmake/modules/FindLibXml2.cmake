# - Try to find the LibXml2 xml processing library
# Once done this will define
#
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIR - The LibXml2 include directory
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2
#  LIBXML2_XMLLINT_EXECUTABLE - The XML checking tool xmllint coming with LibXml2
#  LIBXML2_VERSION_STRING - the version of LibXml2 found (since CMake 2.8.8)

FIND_PATH(LIBXML2_INCLUDE_DIR  libxml/xpath.h
/include
/usr/include
/usr/include/libxml2
   )

FIND_LIBRARY(LIBXML2_LIBRARIES NAMES xml2 libxml2
PATHS /lib /usr/lib /usr/local/lib
   )

IF (LIBXML2_LIBRARIES AND LIBXML2_INCLUDE_DIR)
  SET(LIBXML2_FOUND "YES")
ELSE (LIBXML2_LIBRARIES AND LIBXML2_INCLUDE_DIR)
  SET(LIBXML2_FOUND "NO")
ENDIF (LIBXML2_LIBRARIES AND LIBXML2_INCLUDE_DIR)

IF (LIBXML2_FOUND)
  IF (NOT LIBXML2_FIND_QUIETLY)
    MESSAGE(STATUS "Found LIBXML2 : ${LIBXML2_LIBRARIES}")
  ENDIF (NOT LIBXML2_FIND_QUIETLY)
ELSE (LIBXML2_FOUND)
  IF (LIBXML2_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find LIBXML2 library")
  ENDIF (LIBXML2_FIND_REQUIRED)
ENDIF (LIBXML2_FOUND)
