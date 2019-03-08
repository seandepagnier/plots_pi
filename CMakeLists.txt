##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3
##---------------------------------------------------------------------------
 
# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(plots_pi)

SET(PACKAGE_NAME plots_pi)
SET(VERBOSE_NAME Plots)
SET(TITLE_NAME PLOTS)
SET(CPACK_PACKAGE_CONTACT "Sean D'Epagnier ")

MESSAGE (STATUS "*** Building ${PACKAGE_NAME} ***")

INCLUDE( VERSION.cmake )
SET(PLUGIN_VERSION "${PLUGIN_VERSION_MAJOR}.${PLUGIN_VERSION_MINOR}.${PLUGIN_VERSION_PATCH}" )

OPTION(PLOTS_USE_SVG "Use SVG graphics" ON)

INCLUDE("cmake/PluginConfigure.cmake")

IF(PLOTS_USE_SVG)
  ADD_DEFINITIONS(-DPLOTS_USE_SVG)
ENDIF(PLOTS_USE_SVG)

SET(SRC_PLOTS
            src/plots_pi.cpp
            src/PlotsDialog.cpp
            src/PreferencesDialog.cpp
            src/PlotConfigurationDialog.cpp
            src/AboutDialog.cpp
            src/History.cpp
            src/Plot.cpp
            src/PlotsUI.cpp
            src/icons.cpp
	)

INCLUDE("cmake/PluginNMEA.cmake")
INCLUDE("cmake/PluginJSON.cmake")

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_PLOTS} ${SRC_NMEA0183} ${SRC_JSON})

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
