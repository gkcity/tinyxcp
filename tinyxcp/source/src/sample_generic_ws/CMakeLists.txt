#-----------------------------------------------------------------------------
#
# sample-device-ws
#
#-----------------------------------------------------------------------------

SET(SRC
        Gateway.h
        MyDevice.c
        sample.c
        )

ADD_EXECUTABLE(sample_generic_ws ${SRC})
TARGET_LINK_LIBRARIES(sample_generic_ws
        xcpws_static
        xcp_message_codec_static
        xcp_message_static
        xcp_common_static
        ${DEPENDENCE_LIB})
