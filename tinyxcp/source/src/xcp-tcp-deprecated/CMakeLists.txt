#-----------------------------------------------------------------------------
#
# Xcp Protocol
#
#-----------------------------------------------------------------------------

SET(Xcp_Header
        XcpClientRuntime.h
        XcpServerRuntime.h
        codec-message/CustomDataType.h
        codec-message/MessageCodec.h
        codec-message/MessageCodecContext.h
        codec-binary/XcpBinaryCodec.h
        codec-binary/XcpBinaryCodecContext.h
        codec-binary/frame/XcpFrameCodecType.h
        codec-binary/frame/XcpFrame.h
        codec-binary/frame/XcpFrameDecoder.h
        codec-binary/frame/XcpFrameEncoder.h
        client/XcpClient.h
        client/handler/XcpClientHandler.h
        client/handler/XcpClientHandlerContext.h
        server/XcpBonjour.h
        server/XcpServer.h
        server/handler/XcpServerHandler.h
        server/handler/XcpServerHandlerContext.h
        )

SET(Xcp_Source
        XcpClientRuntime.c
        XcpServerRuntime.c
        codec-message/MessageCodec.c
        codec-message/MessageCodecContext.c
        codec-binary/XcpBinaryCodec.c
        codec-binary/XcpBinaryCodecContext.c
        codec-binary/frame/XcpFrameDecoder.c
        codec-binary/frame/XcpFrameEncoder.c
        client/XcpClient.c
        client/handler/XcpClientHandler.c
        client/handler/XcpClientHandlerContext.c
        server/XcpBonjour.c
        server/XcpServer.c
        server/handler/XcpServerHandler.c
        server/handler/XcpServerHandlerContext.c
        )

SOURCE_GROUP(Xcp\\headers FILES ${Xcp_Header})
SOURCE_GROUP(Xcp\\sources FILES ${Xcp_Source})

SET(SRC
        ${Xcp_Header}
        ${Xcp_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(xcp_static STATIC ${SRC})
SET_TARGET_PROPERTIES(xcp_static PROPERTIES OUTPUT_NAME "xcp_static")
SET_TARGET_PROPERTIES(xcp_static PROPERTIES LINKER_LANGUAGE C)