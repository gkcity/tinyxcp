#-----------------------------------------------------------------------------
#
# sample-plc
#
#-----------------------------------------------------------------------------

SET(SRC sample.c
        HexString.h
        HexString.c
        Modbus.h
        Modbus.c
        ModFrame.h
        ModFrame.c
        Runner.h
        Runner.c
        FanController.h
        FanController.c
        )

ADD_EXECUTABLE(sample_plc ${SRC})
TARGET_LINK_LIBRARIES(sample_plc
        xcp_static
        xcp_common_static
        xcp_message_codec_static
        xcp_message_static
        ${DEPENDENCE_LIB})
