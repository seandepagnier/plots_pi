##---------------------------------------------------------------------------
## Author:      bdbcat aka. dsr (Dave Register)
## Copyright:
## License:     wxWidgets License
##---------------------------------------------------------------------------


# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)
# This should be 2.8.0 to have FindGTK2 module

PROJECT(plots_pi)
SET(PACKAGE_NAME plots_pi)
SET(VERBOSE_NAME Plots)
SET(TITLE_NAME Plots)
SET(CPACK_PACKAGE_CONTACT "Sean D'Epagnier")

INCLUDE("cmake/PluginConfigure.cmake")

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

ADD_LIBRARY(${PACKAGE_NAME} SHARED ${SRC_PLOTS})

INCLUDE("cmake/PluginNMEA.cmake")
INCLUDE("cmake/PluginJSON.cmake")
INCLUDE("cmake/PluginLocalization.cmake")
INCLUDE("cmake/PluginInstall.cmake")
INCLUDE("cmake/PluginPackage.cmake")


