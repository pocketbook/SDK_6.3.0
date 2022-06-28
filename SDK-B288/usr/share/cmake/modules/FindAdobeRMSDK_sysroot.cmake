# -*- cmake -*-

# - Find AdobeManager library
# Find the AdobeManager includes and library
# This module defines
# ADOBE_MANAGER_INCLUDE_DIR, where to find json.h, etc.
# ADOBE_MANAGER_LIBRARIES, the libraries needed to use jsoncpp.
# ADOBE_MANAGER_FOUND, If false, do not try to use jsoncpp.

FIND_PATH(ADOBE_RMSDK_INCLUDE_DIR dp_all.h
/include
/usr/include
/usr/local/include/adobe
)

FIND_LIBRARY(ADOBE_RMSDK_LIBRARIES_adobermsdk
  NAMES libadobermsdk.a
  PATHS /lib /usr/lib /usr/local/lib
)
FIND_LIBRARY(ADOBE_RMSDK_LIBRARIES_adept
  NAMES libadept.a
  PATHS /lib /usr/lib /usr/local/lib
)
FIND_LIBRARY(ADOBE_RMSDK_LIBRARIES_adobe_expat
  NAMES libadobe_expat.a 
  PATHS /lib /usr/lib /usr/local/lib
)
FIND_LIBRARY(ADOBE_RMSDK_LIBRARIES_cryptopenssl
  NAMES libcryptopenssl.a
  PATHS /lib /usr/lib /usr/local/lib
)
FIND_LIBRARY(ADOBE_RMSDK_LIBRARIES_MSCHEMA
  NAMES libmschema.a
  PATHS /lib /usr/lib /usr/local/lib
)
FIND_LIBRARY(ADOBE_RMSDK_LIBRARIES_libdatacollector
  NAMES libdatacollector.a
  PATHS /lib /usr/lib /usr/local/lib
)


IF (ADOBE_RMSDK_LIBRARIES_MSCHEMA 
		AND ADOBE_RMSDK_LIBRARIES_cryptopenssl 
		AND ADOBE_RMSDK_LIBRARIES_adobe_expat
		AND ADOBE_RMSDK_LIBRARIES_adept
		AND ADOBE_RMSDK_LIBRARIES_adobermsdk
		AND ADOBE_RMSDK_INCLUDE_DIR)
  SET(ADOBE_RMSDK_FOUND "YES")
set(ADOBE_RMSDK_LIBRARIES 
	${ADOBE_RMSDK_LIBRARIES_adobe_expat}
	${ADOBE_RMSDK_LIBRARIES_adobermsdk}
	${ADOBE_RMSDK_LIBRARIES_MSCHEMA} 
	${ADOBE_RMSDK_LIBRARIES_cryptopenssl} 
	${ADOBE_RMSDK_LIBRARIES_adobermsdk}
	${ADOBE_RMSDK_LIBRARIES_adept}
	${ADOBE_RMSDK_LIBRARIES_libdatacollector}
	)
ELSE ()
  SET(ADOBE_RMSDK_FOUND "NO")
ENDIF ()


IF (ADOBE_RMSDK_FOUND)
  IF (NOT ADOBE_RMSDK_FIND_QUIETLY)
	  MESSAGE(STATUS "Found ADOBE_RMSDK_LIBRARIES : ${ADOBE_RMSDK_LIBRARIES}")
  ENDIF (NOT ADOBE_RMSDK_FIND_QUIETLY)
ELSE (ADOBE_RMSDK_FOUND)
  IF (ADOBE_RMSDK_FIND_REQUIRED)
	  MESSAGE(FATAL_ERROR "Could not find ADOBE_RMSDK_LIBRARIES")
  ENDIF (ADOBE_RMSDK_FIND_REQUIRED)
ENDIF (ADOBE_RMSDK_FOUND)
