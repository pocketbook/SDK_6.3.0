# -*- cmake -*-

# - Find PBCrypto library
# Find the Inkview includes and library
# This module defines
# PBCRYPTO_INCLUDE_DIR, where to find json.h, etc.
# PBCRYPTO_LIBRARIES, the libraries needed to use jsoncpp.
# PBCRYPTO_FOUND, If false, do not try to use jsoncpp.

FIND_PATH(PBCRYPTO_INCLUDE_DIR pbcrypto.h
/include
/usr/include
/usr/local/include
)

FIND_LIBRARY(PBCRYPTO_LIBRARIES
  NAMES libpbcrypto.a
  PATHS /lib /usr/lib /usr/local/lib
)

IF (PBCRYPTO_LIBRARIES AND PBCRYPTO_INCLUDE_DIR)
  SET(PBCRYPTO_FOUND "YES")
ELSE (PBCRYPTO_LIBRARIES AND PBCRYPTO_INCLUDE_DIR)
  SET(PBCRYPTO_FOUND "NO")
ENDIF (PBCRYPTO_LIBRARIES AND PBCRYPTO_INCLUDE_DIR)


IF (PBCRYPTO_FOUND)
  IF (NOT PBCRYPTO_FIND_QUIETLY)
    MESSAGE(STATUS "Found PBCrypto: ${PBCRYPTO_LIBRARIES}")
  ENDIF (NOT PBCRYPTO_FIND_QUIETLY)
ELSE (PBCRYPTO_FOUND)
  IF (PBCRYPTO_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find PBCrypto library")
  ENDIF (PBCRYPTO_FIND_REQUIRED)
ENDIF (PBCRYPTO_FOUND)
