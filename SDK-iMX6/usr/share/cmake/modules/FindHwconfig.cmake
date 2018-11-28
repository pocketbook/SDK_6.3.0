# -*- cmake -*-

# - Find Hwconfig library
# Find the Hwconfig includes and library
# This module defines
# HWCONFIG_INCLUDE_DIR, where to find json.h, etc.
# HWCONFIG_LIBRARIES, the libraries needed to use jsoncpp.
# HWCONFIG_FOUND, If false, do not try to use jsoncpp.

FIND_PATH(HWCONFIG_INCLUDE_DIR hwconfig.h
/include
/usr/include
/usr/local/include
)

FIND_LIBRARY(HWCONFIG_LIBRARIES
  NAMES libhwconfig.so
  PATHS /lib /usr/lib /usr/local/lib
)

IF (HWCONFIG_LIBRARIES AND HWCONFIG_INCLUDE_DIR)
  SET(HWCONFIG_FOUND "YES")
ELSE (HWCONFIG_LIBRARIES AND HWCONFIG_INCLUDE_DIR)
  SET(HWCONFIG_FOUND "NO")
ENDIF (HWCONFIG_LIBRARIES AND HWCONFIG_INCLUDE_DIR)


IF (HWCONFIG_FOUND)
  IF (NOT HWCONFIG_FIND_QUIETLY)
    MESSAGE(STATUS "Found Hwconfig: ${HWCONFIG_LIBRARIES}")
  ENDIF (NOT HWCONFIG_FIND_QUIETLY)
ELSE (HWCONFIG_FOUND)
  IF (HWCONFIG_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find Hwconfig library")
  ENDIF (HWCONFIG_FIND_REQUIRED)
ENDIF (HWCONFIG_FOUND)
