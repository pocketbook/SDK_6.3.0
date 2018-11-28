# -*- cmake -*-

# - Find Send2PB library
# Find the Send2PB includes and library
# This module defines
# SEND2PB_INCLUDE_DIR, where to find json.h, etc.
# SEND2PB_LIBRARIES, the libraries needed to use jsoncpp.
# SEND2PB_FOUND, If false, do not try to use jsoncpp.

FIND_PATH(SEND2PB_INCLUDE_DIR inkview.h
/include
/usr/include
/usr/local/include
)

FIND_LIBRARY(SEND2PB_LIBRARIES
  NAMES libsendtopb.so
  PATHS /lib /usr/lib /usr/local/lib
)

IF (SEND2PB_LIBRARIES AND SEND2PB_INCLUDE_DIR)
	SET(SEND2PB_FOUND "YES")
ELSE (SEND2PB_LIBRARIES AND SEND2PB_INCLUDE_DIR)
	SET(SEND2PB_FOUND "NO")
ENDIF (SEND2PB_LIBRARIES AND SEND2PB_INCLUDE_DIR)


IF (SEND2PB_FOUND)
	IF (NOT SEND2PB_FIND_QUIETLY)
		MESSAGE(STATUS "Found Inkview: ${SEND2PB_LIBRARIES}")
	ENDIF (NOT SEND2PB_FIND_QUIETLY)
ELSE (SEND2PB_FOUND)
	IF (SEND2PB_FIND_REQUIRED)
		MESSAGE(FATAL_ERROR "Could not find Send2PB library")
	ENDIF (SEND2PB_FIND_REQUIRED)
ENDIF (SEND2PB_FOUND)
