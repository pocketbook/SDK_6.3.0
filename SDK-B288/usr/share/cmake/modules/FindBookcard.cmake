# -*- cmake -*-

# - Find Bookcard library
# Find the Bookcard includes and library
# This module defines
# BOOKCARD_INCLUDE_DIR, where to find g2log.hpp, etc.
# BOOKCARD_LIBRARIES, the libraries needed to use libbookcard.so
# BOOKCARD_FOUND, If false, do not try to use Bookcard.

FIND_PATH(BOOKCARD_INCLUDE_DIR bookcard/card.h
    bookcard/infocontainer.h
    bookcard/readrate.h
    /include
    /usr/include
    /usr/local/include
)

FIND_LIBRARY(BOOKCARD_LIBRARIES
  NAMES libbookcard.so
  PATHS /lib /usr/lib /usr/local/lib
)

IF (BOOKCARD_LIBRARIES AND BOOKCARD_INCLUDE_DIR)
  SET(BOOKCARD_FOUND "YES")
ELSE (BOOKCARD_LIBRARIES AND BOOKCARD_INCLUDE_DIR)
  SET(BOOKCARD_FOUND "NO")
ENDIF (BOOKCARD_LIBRARIES AND BOOKCARD_INCLUDE_DIR)

IF (BOOKCARD_FOUND)
  IF (NOT BOOKCARD_FIND_QUIETLY)
    MESSAGE(STATUS "Found BOOKCARD: ${BOOKCARD_LIBRARIES}")
  ENDIF (NOT BOOKCARD_FIND_QUIETLY)
ELSE (BOOKCARD_FOUND)
  IF (BOOKCARD_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find BOOKCARD library")
  ENDIF (BOOKCARD_FIND_REQUIRED)
ENDIF (BOOKCARD_FOUND)
