#-----------------------------------------------------------------------------
#
# sample-plc-local
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
        ModbusDB.h
        ModbusDB.c
        DeviceCreator.h
        DeviceCreator.c
        )

ADD_EXECUTABLE(sample_plc_local ${SRC})
TARGET_LINK_LIBRARIES(sample_plc_local
        xcpws_static
        xcp_common_static
        xcp_message_codec_static
        xcp_message_static
        ${DEPENDENCE_LIB})
