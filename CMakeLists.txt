##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   
## License:     GPLv3
##---------------------------------------------------------------------------
 
# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)

PROJECT(sweepplot_pi)

SET(PACKAGE_NAME sweepplot_pi)
SET(VERBOSE_NAME SweepPlot)
SET(TITLE_NAME SWEEPPLOT)
SET(CPACK_PACKAGE_CONTACT "Sean D'Epagnier ")

MESSAGE (STATUS "*** Building ${PACKAGE_NAME} ***")

INCLUDE( VERSION.cmake )
SET(PLUGIN_VERSION "${PLUGIN_VERSION_MAJOR}.${PLUGIN_VERSION_MINOR}.${PLUGIN_VERSION_PATCH}" )

OPTION(SWEEPPLOT_USE_SVG "Use SVG graphics" ON)

INCLUDE("cmake/PluginConfigure.cmake")

IF(SWEEPPLOT_USE_SVG)
  ADD_DEFINITIONS(-DSWEEPPLOT_USE_SVG)
ENDIF(SWEEPPLOT_USE_SVG)

SET(SRC_SWEEPPLOT
            src/sweepplot_pi.cpp
            src/SweepPlotDialog.cpp
            src/PreferencesDialog.cpp
            src/PlotConfigurationDialog.cpp
            src/AboutDialog.cpp
            src/History.cpp
            src/Plot.cpp
            src/SweepPlotUI.cpp
            src/icons.cpp
	)

INCLUDE("cmake/PluginNMEA.cmake")
INCLUDE("cmake/PluginJSON.cmake")

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_SWEEPPLOT} ${SRC_NMEA0183} ${SRC_JSON})

INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginPackage.cmake")
