#-----------------------------------------------------------------------------
#
# Xcp Messsage
#
#-----------------------------------------------------------------------------

SET(XcpMessage_Header
        XcpMessage.h
        XcpConstant.h
        iq/IQ.h
        iq/IQError.h
        iq/IQErrorFactory.h
        iq/IQQuery.h
        iq/IQResult.h
        iq/IQMethod.h
        iq/basic/ByebyeFactory.h
        iq/basic/ChildrenAdded.h
        iq/basic/ChildrenRemoved.h
        iq/basic/EventOccurred.h
        iq/basic/EventOccurredFactory.h
        iq/basic/GetAccessKey.h
        iq/basic/GetAccessKeyFactory.h
        iq/basic/GetChildren.h
        iq/basic/GetProperties.h
        iq/basic/GetPropertiesFactory.h
        iq/basic/Initialize.h
        iq/basic/InitializeFactory.h
        iq/basic/InvokeAction.h
        iq/basic/InvokeActionFactory.h
        iq/basic/PingFactory.h
        iq/basic/PongFactory.h
        iq/basic/PropertiesChanged.h
        iq/basic/PropertiesChangedFactory.h
        iq/basic/SetAccessKey.h
        iq/basic/SetAccessKeyFactory.h
        iq/basic/SetProperties.h
        iq/basic/SetPropertiesFactory.h
        iq/basic/VerifyFinish.h
        iq/basic/VerifyFinishFactory.h
        iq/basic/VerifyStart.h
        iq/basic/VerifyStartFactory.h
        handler/XcpMessageHandler.h
        )

SET(XcpMessage_Source
        XcpMessage.c
        iq/IQ.c
        iq/IQQuery.c
        iq/IQResult.c
        iq/IQError.c
        iq/IQErrorFactory.c
        iq/IQMethod.c
        iq/basic/ByebyeFactory.c
        iq/basic/ChildrenAdded.c
        iq/basic/ChildrenRemoved.c
        iq/basic/EventOccurred.c
        iq/basic/EventOccurredFactory.c
        iq/basic/GetAccessKey.c
        iq/basic/GetAccessKeyFactory.c
        iq/basic/GetProperties.c
        iq/basic/GetPropertiesFactory.c
        iq/basic/GetChildren.c
        iq/basic/Initialize.c
        iq/basic/InitializeFactory.c
        iq/basic/InvokeAction.c
        iq/basic/InvokeActionFactory.c
        iq/basic/PingFactory.c
        iq/basic/PongFactory.c
        iq/basic/PropertiesChanged.c
        iq/basic/PropertiesChangedFactory.c
        iq/basic/SetAccessKey.c
        iq/basic/SetAccessKeyFactory.c
        iq/basic/SetProperties.c
        iq/basic/SetPropertiesFactory.c
        iq/basic/VerifyFinish.c
        iq/basic/VerifyFinishFactory.c
        iq/basic/VerifyStart.c
        iq/basic/VerifyStartFactory.c
        handler/XcpMessageHandler.c
        )

SOURCE_GROUP(XcpMessage\\headers FILES ${XcpMessage_Header})
SOURCE_GROUP(XcpMessage\\sources FILES ${XcpMessage_Source})

SET(SRC
        ${XcpMessage_Header}
        ${XcpMessage_Source}
        )

#----------------------------------------------------------------------------
# static library
#----------------------------------------------------------------------------
ADD_LIBRARY(xcp_message_static STATIC ${SRC})
SET_TARGET_PROPERTIES(xcp_message_static PROPERTIES OUTPUT_NAME "xcp_message_static")
SET_TARGET_PROPERTIES(xcp_message_static PROPERTIES LINKER_LANGUAGE C)