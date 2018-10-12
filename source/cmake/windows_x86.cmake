MESSAGE(STATUS "make for windows")
SET(CMAKE_SYSTEM_NAME Windows)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR x86)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

#----------------------------------------------------------------------------
#
# for VisualStudio 2017
#
#----------------------------------------------------------------------------
ADD_DEFINITIONS(-D_WINSOCK_DEPRECATED_NO_WARNINGS)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)
ADD_DEFINITIONS(-D__WIN32__)

#----------------------------------------------------------------------------
#
# Dependence Libraries
#
#----------------------------------------------------------------------------
SET(DEPENDENCE_LIB ws2_32.lib tinycrypto.lib tinyfx.lib tiny.lib)

#----------------------------------------------------------------------------
#
# DEBUG INFORMATION
#
#----------------------------------------------------------------------------
ADD_DEFINITIONS(-DTINY_DEBUG)

#----------------------------------------------------------------------------
#
# static library
#
#----------------------------------------------------------------------------
ADD_DEFINITIONS(-DHAP_STATIC)
