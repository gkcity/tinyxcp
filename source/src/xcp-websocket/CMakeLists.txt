#-----------------------------------------------------------------------------
#
# Xcp Over message
#
#-----------------------------------------------------------------------------

SET(Xcpws_Header
        XcpwsClientRuntime.h
        XcpwsServerRuntime.h
        client/XcpwsClient.h
        client/hook/XcpwsClientLoopHook.h
        client/handler/XcpwsClientHandler.h
        client/handler/XcpwsClientHandlerContext.h
        client/verifier/XcpClientVerifier.h
        server/XcpwsServer.h
        server/XcpwsServerContext.h
        server/XcpwsBonjour.h
        server/hook/XcpwsServerLoopHook.h
        server/handler/XcpwsServerHandler.h
        server/handler/XcpwsServerHandlerContext.h
        codec-message/CustomDataType.h
        codec-message/MessageCodec.h
        codec-message/MessageCodecContext.h
        codec-binary/WebSocketBinaryFrameCodec.h
        codec-binary/WebSocketBinaryFrameCodecContext.h
        codec-binary/WebSocketBinaryFrameCodecType.h
        codec-binary/WebSocketBinaryFrameDecoder.h
        codec-binary/WebSocketBinaryFrameEncoder.h
        )

SET(Xcpws_Source
        XcpwsClientRuntime.c
        XcpwsServerRuntime.c
        client/XcpwsClient.c
        client/hook/XcpwsClientLoopHook.c
        client/handler/XcpwsClientHandler.c
        client/handler/XcpwsClientHandlerContext.c
        client/verifier/XcpClientVerifier.c
        server/XcpwsServer.c
        server/XcpwsServerContext.c
        server/XcpwsBonjour.c
        server/hook/XcpwsServerLoopHook.c
        server/handler/XcpwsServerHandler.c
        server/handler/XcpwsServerHandlerContext.c
        codec-message/MessageCodec.c
        codec-message/MessageCodecContext.c
        codec-binary/WebSocketBinaryFrameCodec.c
        codec-binary/WebSocketBinaryFrameCodecContext.c
        codec-binary/WebSocketBinaryFrameDecoder.c
        codec-binary/WebSocketBinaryFrameEncoder.c
        )

SOURCE_GROUP(Xcpws\\headers FILES ${Xcpws_Header})
SOURCE_GROUP(Xcpws\\sources FILES ${Xcpws_Source})

SET(SRC
        ${Xcpws_Header}
        ${Xcpws_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(xcpws_static STATIC ${SRC})
SET_TARGET_PROPERTIES(xcpws_static PROPERTIES OUTPUT_NAME "xcpws_static")
SET_TARGET_PROPERTIES(xcpws_static PROPERTIES LINKER_LANGUAGE C)
