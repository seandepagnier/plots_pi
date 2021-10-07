##---------------------------------------------------------------------------
## Author:      Sean D'Epagnier
## Copyright:   2015
## License:     GPLv3+
##---------------------------------------------------------------------------
set(PluginJSON_SAVE_CMLOC ${CMLOC})
set(CMLOC "PluginJSON: ")
message(STATUS "${CMLOC}In PluginJSON")

SET(SRC_JSON
	    libs/wxJSON/src/jsonreader.cpp
	    libs/wxJSON/src/jsonval.cpp
	    libs/wxJSON/src/jsonwriter.cpp
        )

INCLUDE_DIRECTORIES(BEFORE libs/wxJSON/include)
set(CMLOC ${PluginJSON_SAVE_CMLOC})
