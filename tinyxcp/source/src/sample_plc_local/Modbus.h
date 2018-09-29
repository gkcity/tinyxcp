/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   Modbus.h
*
* @remark
*
*/

#ifndef __Modbus_H__
#define __Modbus_H__

#include <tiny_base.h>
#include <JsonValue.h>

TINY_BEGIN_DECLS


JsonValue * mb_send(JsonString *request);

JsonValue * mb_read_discrete_inputs(uint8_t unit, uint16_t firstAddress, uint16_t numberOfDiscreteInputs);

JsonValue * mb_read_coils(uint8_t unit, uint16_t firstAddress, uint16_t numberOfCoils);

int mb_write_single_coil(uint8_t unit, uint16_t firstAddress, uint16_t coilValue);

int mb_write_multiple_coils(uint8_t unit, uint16_t firstAddress, uint16_t numberOfCoils, uint8_t numberOfBytes, uint8_t *coilValues);

JsonValue * mb_read_input_registers(uint8_t unit, uint16_t firstAddress, uint16_t numberOfRegisters);

JsonValue * mb_read_multiple_holding_registers(uint8_t unit, uint16_t firstAddress, uint16_t numberOfRegisters);

int mb_write_single_holding_register(uint8_t unit, uint16_t firstAddress, uint16_t registerValue);

int mb_write_multiple_holding_registers(uint8_t unit, uint16_t firstAddress, uint16_t numberOfRegisters, uint8_t numberOfBytes, uint8_t *registerValues);


TINY_END_DECLS

#endif /* __Modbus_H__ */