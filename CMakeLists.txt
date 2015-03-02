##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3
##---------------------------------------------------------------------------
 
# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(trimplot_pi)
SET(PACKAGE_NAME trimplot_pi)
SET(CPACK_PACKAGE_CONTACT "Sean D'Epagnier ")

MESSAGE (STATUS "*** Building ${PACKAGE_NAME} ***")

SET(VERSION_MAJOR "0")
SET(VERSION_MINOR "4")

INCLUDE("cmake/PluginConfigure.cmake")

SET(SRC_TRIMPLOT
            src/trimplot_pi.cpp
            src/TrimPlotDialog.cpp
            src/PreferencesDialog.cpp
            src/AboutDialog.cpp
            src/History.cpp
            src/Plot.cpp
            src/TrimPlotUI.cpp
            src/icons.cpp
	)

INCLUDE("cmake/PluginNMEA.cmake")
INCLUDE("cmake/PluginJSON.cmake")

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_TRIMPLOT} ${SRC_NMEA0183} ${SRC_JSON})

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
