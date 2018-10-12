#-----------------------------------------------------------------------------
#
# xcp-webcmd
#
#-----------------------------------------------------------------------------

SET(Webcmd_Header
        server/WebcmdServer.h
        server/handler/WebcmdServerHandler.h
        server/handler/HandleCommon.h
        server/handler/HandleGetAccessKey.h
        server/handler/HandleResetAccessKey.h
        server/handler/HandlePropertyChanged.h
        server/handler/HandleEventOccurred.h
        client/WebcmdClient.h
        )

SET(Webcmd_Source
        server/WebcmdServer.c
        server/handler/WebcmdServerHandler.c
        server/handler/HandleCommon.c
        server/handler/HandleGetAccessKey.c
        server/handler/HandleResetAccessKey.c
        server/handler/HandlePropertyChanged.c
        server/handler/HandleEventOccurred.c
        client/WebcmdClient.c
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
