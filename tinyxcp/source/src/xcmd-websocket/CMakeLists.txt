#-----------------------------------------------------------------------------
#
# xcmd-ws
#
#-----------------------------------------------------------------------------

SET(Xcmd_Header
        client/XcmdClient.h
        client/handler/XcmdClientHandler.h
        client/handler/XcmdClientHandlerContext.h
        server/XcmdServer.h
        server/handler/XcmdServerHandler.h
        server/handler/XcmdServerHandlerContext.h
        )

SET(Xcmd_Source
        client/XcmdClient.c
        client/handler/XcmdClientHandler.c
        client/handler/XcmdClientHandlerContext.c
        server/XcmdServer.c
        server/handler/XcmdServerHandler.c
        server/handler/XcmdServerHandlerContext.c
        )

SOURCE_GROUP(Xcmd\\headers FILES ${Xcmd_Header})
SOURCE_GROUP(Xcmd\\sources FILES ${Xcmd_Source})

SET(SRC
        ${Xcmd_Header}
        ${Xcmd_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(Xcmd_static STATIC ${SRC})
SET_TARGET_PROPERTIES(Xcmd_static PROPERTIES OUTPUT_NAME "Xcmd_static")
SET_TARGET_PROPERTIES(Xcmd_static PROPERTIES LINKER_LANGUAGE C)
