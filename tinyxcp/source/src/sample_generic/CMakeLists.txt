#-----------------------------------------------------------------------------
#
# sample-generic
#
#-----------------------------------------------------------------------------

SET(SRC
        MyDevice.h
        MyDevice.c
        sample.c
        )

ADD_EXECUTABLE(sample_generic ${SRC})
TARGET_LINK_LIBRARIES(sample_generic
        xcp_static
        xcp_common_static
        xcp_message_codec_static
        xcp_message_static
        ${DEPENDENCE_LIB})
