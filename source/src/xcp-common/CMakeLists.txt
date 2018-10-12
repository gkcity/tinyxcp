#-----------------------------------------------------------------------------
#
# xcp-commcon
#
#-----------------------------------------------------------------------------

SET(XcpCommon_Header
        XcpSessionInfo.h
        XcpKeyCreator.h
        XcpStage.h
        )

SET(XcpCommon_Source
        XcpSessionInfo.c
        XcpKeyCreator.c
        )

SOURCE_GROUP(XcpCommon\\headers FILES ${XcpCommon_Header})
SOURCE_GROUP(XcpCommon\\sources FILES ${XcpCommon_Source})

SET(SRC
        ${XcpCommon_Header}
        ${XcpCommon_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(xcp_common_static STATIC ${SRC})
SET_TARGET_PROPERTIES(xcp_common_static PROPERTIES OUTPUT_NAME "xcp_common_static")
SET_TARGET_PROPERTIES(xcp_common_static PROPERTIES LINKER_LANGUAGE C)