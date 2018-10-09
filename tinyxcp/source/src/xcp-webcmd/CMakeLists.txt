#-----------------------------------------------------------------------------
#
# xcp-webcmd
#
#-----------------------------------------------------------------------------

SET(Webcmd_Header
        server/WebcmdServer.h
        server/handler/WebcmdServerHandler.h
        )

SET(Webcmd_Source
        server/WebcmdServer.c
        server/handler/WebcmdServerHandler.c
        )

SOURCE_GROUP(Xcmd\\headers FILES ${Xcmd_Header})
SOURCE_GROUP(Xcmd\\sources FILES ${Xcmd_Source})

SET(SRC
        ${Webcmd_Header}
        ${Webcmd_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(xcp_webcmd_static STATIC ${SRC})
SET_TARGET_PROPERTIES(xcp_webcmd_static PROPERTIES OUTPUT_NAME "xcp_webcmd_static")
SET_TARGET_PROPERTIES(xcp_webcmd_static PROPERTIES LINKER_LANGUAGE C)
