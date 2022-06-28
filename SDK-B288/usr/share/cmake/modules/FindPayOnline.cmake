# -*- cmake -*-

# - Find PayOnline library
# Find the Inkview includes and library
# This module defines
# PAY_ONLINE_INCLUDE_DIR, where to find json.h, etc.
# PAY_ONLINE_LIBRARIES, the libraries needed to use jsoncpp.
# PAY_ONLINE_FOUND, If false, do not try to use jsoncpp.

FIND_PATH(PAY_ONLINE_INCLUDE_DIR pay_online.h
/include
/usr/include
/usr/local/include
)

FIND_LIBRARY(PAY_ONLINE_LIBRARIES
  NAMES libpay_online.so
  PATHS /lib /usr/lib /usr/local/lib
)

IF (PAY_ONLINE_LIBRARIES AND PAY_ONLINE_INCLUDE_DIR)
  SET(PAY_ONLINE_FOUND "YES")
ELSE (PAY_ONLINE_LIBRARIES AND PAY_ONLINE_INCLUDE_DIR)
  SET(PAY_ONLINE_FOUND "NO")
ENDIF (PAY_ONLINE_LIBRARIES AND PAY_ONLINE_INCLUDE_DIR)


IF (PAY_ONLINE_FOUND)
  IF (NOT PAY_ONLINE_FIND_QUIETLY)
    MESSAGE(STATUS "Found PayOnline: ${PAY_ONLINE_LIBRARIES}")
  ENDIF (NOT PAY_ONLINE_FIND_QUIETLY)
ELSE (PAY_ONLINE_FOUND)
  IF (PAY_ONLINE_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find PayOnline library")
  ENDIF (PAY_ONLINE_FIND_REQUIRED)
ENDIF (PAY_ONLINE_FOUND)
