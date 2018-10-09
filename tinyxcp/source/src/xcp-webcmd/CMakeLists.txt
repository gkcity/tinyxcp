#-----------------------------------------------------------------------------
#
# xcp-webcmd
#
#-----------------------------------------------------------------------------

SET(Webcmd_Header
#        client/WebcmdClient.h
#        client/handler/WebcmdClientHandler.h
#        client/handler/WebcmdClientHandlerContext.h
        server/WebcmdServer.h
        server/handler/WebcmdServerHandler.h
        )

SET(Webcmd_Source
#        client/WebcmdClient.c
#        client/handler/WebcmdClientHandler.c
#        client/handler/WebcmdClientHandlerContext.c
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
