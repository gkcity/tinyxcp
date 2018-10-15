#-----------------------------------------------------------------------------
#
# sample_generic_loading_dynamic
#
#-----------------------------------------------------------------------------



SET(HANDLER_SRC
        handler/OnActionInvoke.h
        handler/OnActionInvoke.c
        handler/OnPropertyGet.h
        handler/OnPropertyGet.c
        handler/OnPropertySet.h
        handler/OnPropertySet.c
        handler/S_1_DeviceInformation/S_1_DeviceInformation_doGet.h
        handler/S_1_DeviceInformation/S_1_DeviceInformation_doGet.c
        handler/S_1_DeviceInformation/S_1_DeviceInformation_doSet.h
        handler/S_1_DeviceInformation/S_1_DeviceInformation_doSet.c
        handler/S_1_DeviceInformation/S_1_DeviceInformation_doInvoke.h
        handler/S_1_DeviceInformation/S_1_DeviceInformation_doInvoke.c
        handler/S_2_ModbusController/S_2_ModbusController_doGet.h
        handler/S_2_ModbusController/S_2_ModbusController_doGet.c
        handler/S_2_ModbusController/S_2_ModbusController_doSet.h
        handler/S_2_ModbusController/S_2_ModbusController_doSet.c
        handler/S_2_ModbusController/S_2_ModbusController_doInvoke.h
        handler/S_2_ModbusController/S_2_ModbusController_doInvoke.c
        handler/S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doGet.h
        handler/S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doGet.c
        handler/S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doSet.h
        handler/S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doSet.c
        handler/S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doInvoke.h
        handler/S_3_ModbusUnitDefinitionManagement/S_3_ModbusUnitDefinitionManagement_doInvoke.c
        handler/S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doGet.h
        handler/S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doGet.c
        handler/S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doSet.h
        handler/S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doSet.c
        handler/S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doInvoke.h
        handler/S_4_ModbusUnitManagement/S_4_ModbusUnitManagement_doInvoke.c
        handler/S_5_ModbusCollector/S_5_ModbusCollector_doGet.h
        handler/S_5_ModbusCollector/S_5_ModbusCollector_doGet.c
        handler/S_5_ModbusCollector/S_5_ModbusCollector_doSet.h
        handler/S_5_ModbusCollector/S_5_ModbusCollector_doSet.c
        handler/S_5_ModbusCollector/S_5_ModbusCollector_doInvoke.h
        handler/S_5_ModbusCollector/S_5_ModbusCollector_doInvoke.c
        )

SET(SRC
        ${HANDLER_SRC}
        print/PrintValue.h
        print/PrintValue.c
        iid/IID.h
        DeviceMonitor.h
        DeviceMonitor.c
        DeviceStack.h
        DeviceStack.c
        DeviceInitializer.h
        DeviceInitializer.c
        CommandReader.h
        CommandReader.c
        main.c
        tiny_print_mem.c
        tiny_sleep.c
        )

ADD_EXECUTABLE(sample_generic_loading_dynamic ${SRC})
TARGET_LINK_LIBRARIES(sample_generic_loading_dynamic
        xcpws_static
        xcp_webcmd_static
        xcp_message_codec_static
        xcp_message_static
        xcp_common_static
        ${DEPENDENCE_LIB})
