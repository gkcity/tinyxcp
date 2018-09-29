#-----------------------------------------------------------------------------
#
# xcp-message-codec-websocket
#
#-----------------------------------------------------------------------------

SET(XcpMessageCodec_Header
        XcpMessageCodec.h
        iq/IQCodec.h
        iq/IQErrorCodec.h
        iq/IQQueryCodec.h
        iq/IQResultCodec.h
        iq/basic/ChildrenAddedCodec.h
        iq/basic/ChildrenRemovedCodec.h
        iq/basic/EventOccurredCodec.h
        iq/basic/InitializeCodec.h
        iq/basic/PropertiesChangedCodec.h
        iq/basic/SetAccessKeyCodec.h
        iq/basic/VerifyFinishCodec.h
        iq/basic/VerifyStartCodec.h
        iq/basic/GetPropertiesCodec.h
        iq/basic/SetPropertiesCodec.h
        iq/basic/InvokeActionCodec.h
        iq/basic/GetChildrenCodec.h
        xid/PIDCodec.h
        xid/AIDCodec.h
        )

SET(XcpMessageCodec_Source
        XcpMessageCodec.c
        iq/IQCodec.c
        iq/IQErrorCodec.c
        iq/IQQueryCodec.c
        iq/IQResultCodec.c
        iq/basic/ChildrenAddedCodec.c
        iq/basic/ChildrenRemovedCodec.c
        iq/basic/EventOccurredCodec.c
        iq/basic/InitializeCodec.c
        iq/basic/PropertiesChangedCodec.c
        iq/basic/SetAccessKeyCodec.c
        iq/basic/VerifyFinishCodec.c
        iq/basic/VerifyStartCodec.c
        iq/basic/GetPropertiesCodec.c
        iq/basic/SetPropertiesCodec.c
        iq/basic/InvokeActionCodec.c
        iq/basic/GetChildrenCodec.c
        xid/PIDCodec.c
        xid/AIDCodec.c
        )

SOURCE_GROUP(Xcp\\headers FILES ${XcpMessageCodec_Header})
SOURCE_GROUP(Xcp\\sources FILES ${XcpMessageCodec_Source})

SET(SRC
        ${XcpMessageCodec_Header}
        ${XcpMessageCodec_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(xcp_message_codec_static STATIC ${SRC})
SET_TARGET_PROPERTIES(xcp_message_codec_static PROPERTIES OUTPUT_NAME "xcp_message_codec_static")
SET_TARGET_PROPERTIES(xcp_message_codec_static PROPERTIES LINKER_LANGUAGE C)