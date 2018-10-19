/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   IID.h
*
* @remark
*
*/

#ifndef __IID_H__
#define __IID_H__


#define IID_1_DeviceInformation                                               1
#define IID_1_1_Manufacturer                                                  1
#define IID_1_2_Model                                                         2
#define IID_1_3_SerialNumber                                                  3
#define IID_1_4_FirmwareRevision                                              4

#define IID_2_ModbusController                                                2
#define IID_2_1_UnitId                                                        1
#define IID_2_2_OffsetAddress                                                 2
#define IID_2_3_NumberOfDiscreteInputs                                        3
#define IID_2_4_NumberOfCoils                                                 4
#define IID_2_5_NumberOfRegisters                                             5
#define IID_2_6_NumberOfBytes                                                 6
#define IID_2_7_CoilValue                                                     7
#define IID_2_8_CoilValues                                                    8
#define IID_2_9_DiscreteInputValues                                           9
#define IID_2_10_RegisterValues                                               10
#define IID_2_11_RegisterValue                                                11
#define IID_2_1_ReadDiscreteInputs                                            1
#define IID_2_2_ReadCoils                                                     2
#define IID_2_3_WriteSingleCoil                                               3
#define IID_2_4_WriteMultipleCoils                                            4
#define IID_2_5_ReadInputRegisters                                            5
#define IID_2_6_ReadMultipleHoldingRegisters                                  6
#define IID_2_7_WriteSingleHoldingRegister                                    7
#define IID_2_8_WriteMultipleHoldingRegisters                                 8
#define IID_2_1_InputRegistersChanged                                         1

#define IID_3_ModbusUnitDefinitionManagement                                  3
#define IID_3_1_UnitDefinitionId                                              1
#define IID_3_2_UnitDefinitionName                                            2
#define IID_3_3_UnitDefinitionDescription                                     3
#define IID_3_4_UnitDefinitionContent                                         4
#define IID_3_5_UnitDefinitionCount                                           5
#define IID_3_6_UnitDefinitionIndex                                           6
#define IID_3_1_AddUnitDefinition                                             1
#define IID_3_2_RemoveUnitDefinition                                          2
#define IID_3_3_ModifyUnitDefinition                                          3
#define IID_3_4_GetUnitDefinition                                             4

#define IID_4_ModbusUnitManagement                                            4
#define IID_4_1_UnitId                                                        1
#define IID_4_2_UnitName                                                      2
#define IID_4_3_UnitSerialNumber                                              3
#define IID_4_4_UnitDefinitionId                                              4
#define IID_4_5_UnitCount                                                     5
#define IID_4_6_UnitIndex                                                     6
#define IID_4_1_AddUnit                                                       1
#define IID_4_2_RemoveUnit                                                    2
#define IID_4_3_ModifyUnit                                                    3
#define IID_4_4_GetUnit                                                       4

#define IID_5_ModbusCollector                                                 5
#define IID_5_1_CollectInterval                                               1
#define IID_5_2_CollectingStatus                                              2
#define IID_5_1_StartCollecting                                               1
#define IID_5_2_StopCollecting                                                2


#endif /* __IID_H__ */