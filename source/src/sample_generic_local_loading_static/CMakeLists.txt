#-----------------------------------------------------------------------------
#
# sample_generic_local_loading_static
#
#-----------------------------------------------------------------------------

SET(SRC main.c
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
        ModbusDB.h
        ModbusDB.c
        DeviceCreator.h
        DeviceCreator.c
        )

ADD_EXECUTABLE(sample_generic_local_loading_static ${SRC})
TARGET_LINK_LIBRARIES(sample_generic_local_loading_static
        xcpws_static
        xcp_common_static
        xcp_message_codec_static
        xcp_message_static
        ${DEPENDENCE_LIB})
