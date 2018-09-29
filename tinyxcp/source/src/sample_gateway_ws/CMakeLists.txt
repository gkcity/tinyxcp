#-----------------------------------------------------------------------------
#
# sample-gateway-ws
#
#-----------------------------------------------------------------------------

SET(SRC
        Gateway.h
        Gateway.c
        main.c
        )

ADD_EXECUTABLE(sample_gateway_ws ${SRC})
TARGET_LINK_LIBRARIES(sample_gateway_ws
        xcpws_static
        xcp_message_codec_static
        xcp_message_static
        xcp_common_static
        ${DEPENDENCE_LIB})
