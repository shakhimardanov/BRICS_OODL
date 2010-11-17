# - Try to find rudeconfig
# Once done this will define
#
#  RUDECONFIG_FOUND - rudeconfig found
#  RUDECONFIG_INCLUDE_DIR - the rudeconfig include directory
#  RUDECONFIG_LIBRARY_DIR - rudeconfig lib directory
#

SET(RUDECONFIGLIB "rudeconfig")

FIND_PATH(RUDECONFIG_INCLUDE_DIR NAMES rude/config.h
  PATHS
  ${RUDECONFIG_PATH}/include
  ${CMAKE_HOME_DIRECTORY}/../openrobots/include
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}/include
  ENV CPATH
  /usr/include/
  /usr/local/include/
  /opt/local/include/
  NO_DEFAULT_PATH
)

#MESSAGE("RUDECONFIG_INCLUDE_DIR: "${RUDECONFIG_INCLUDE_DIR})

FIND_LIBRARY(RUDECONFIG_LIBRARY_TMP NAMES ${RUDECONFIGLIB} "rudeconfigLibraries"
  PATHS
  ${RUDECONFIG_PATH}/lib
  ${CMAKE_HOME_DIRECTORY}/../openrobots/lib
  ${PROJECT_BINARY_DIR}/lib
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/libraries
  ENV LD_LIBRARY_PATH
  ENV LIBRARY_PATH
  /usr/lib
  /usr/local/lib
  /opt/local/lib
  NO_DEFAULT_PATH
)

IF(RUDECONFIG_LIBRARY_TMP)
  GET_FILENAME_COMPONENT( RUDECONFIG_LIBRARY_DIR ${RUDECONFIG_LIBRARY_TMP} PATH )
ENDIF(RUDECONFIG_LIBRARY_TMP)

IF(RUDECONFIG_INCLUDE_DIR AND RUDECONFIG_LIBRARY_DIR)
  SET(RUDECONFIG_FOUND TRUE)
ENDIF(RUDECONFIG_INCLUDE_DIR AND RUDECONFIG_LIBRARY_DIR)

# show the RUDECONFIG_INCLUDE_DIR and RUDECONFIG_LIBRARY_DIR variables only in the advanced view
IF(RUDECONFIG_FOUND)
  MARK_AS_ADVANCED(RUDECONFIG_INCLUDE_DIR RUDECONFIG_LIBRARY_DIR )
ENDIF(RUDECONFIG_FOUND)

