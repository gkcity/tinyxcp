/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   ModbusDB.h
*
* @remark
*
*/

#ifndef __ModbusDB_H__
#define __ModbusDB_H__

#include <tiny_base.h>
#include <JsonObject.h>

TINY_BEGIN_DECLS


JsonObject * ModbusDB_GetDevices(void);

JsonObject * ModbusDB_GetDevice(const char *id);

bool ModbusDB_DeleteDevice(const char *id);

bool ModbusDB_SaveDevice(const char *id, const char *buf);

JsonObject * ModbusDB_GetDefinitions(void);

JsonObject * ModbusDB_GetDefinition(const char *id);

bool ModbusDB_DeleteDefinition(const char *id);

bool ModbusDB_SaveDefinition(const char *id, const char *buf);


TINY_END_DECLS

#endif /* __ModbusDB_H__ */