INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DZLABS dzlabs)

FIND_PATH(
    DZLABS_INCLUDE_DIRS
    NAMES dzlabs/api.h
    HINTS $ENV{DZLABS_DIR}/include
        ${PC_DZLABS_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DZLABS_LIBRARIES
    NAMES gnuradio-dzlabs
    HINTS $ENV{DZLABS_DIR}/lib
        ${PC_DZLABS_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DZLABS DEFAULT_MSG DZLABS_LIBRARIES DZLABS_INCLUDE_DIRS)
MARK_AS_ADVANCED(DZLABS_LIBRARIES DZLABS_INCLUDE_DIRS)

