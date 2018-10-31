/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ModbusMaster.c
 *
 * @remark
 *
 */

#include <tiny_snprintf.h>
#include "ModbusMaster.h"
#include "../handler/OnPropertySet.h"
#include "../handler/OnActionInvoke.h"
#include "../handler/OnPropertyGet.h"
#include "../initializer/InitializeConfiguration.h"
#include "S_1_DeviceInformation.h"
#include "S_2_ModbusController.h"
#include "S_3_ModbusUnitDefinitionManagement.h"
#include "S_4_ModbusUnitManagement.h"
#include "S_5_ModbusCollector.h"

Device * ModbusMaster(const char *serialNumber, const char *ip)
{
    Device *thiz = NULL;

    do
    {
        thiz = Device_New();
        if (thiz == NULL)
        {
            break;
        }

        thiz->onGet = OnPropertyGet;
        thiz->onSet = OnPropertySet;
        thiz->onInvoke = OnActionInvoke;

        if (RET_FAILED(TinyList_AddTail(&thiz->services, S_1_DeviceInformation())))
        {
            Device_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->services, S_2_ModbusController())))
        {
            Device_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->services, S_3_ModbusUnitDefinitionManagement())))
        {
            Device_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->services, S_4_ModbusUnitManagement())))
        {
            Device_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->services, S_5_ModbusCollector())))
        {
            Device_Delete(thiz);
            thiz = NULL;
            break;
        }

        InitializeConfiguration(&thiz->config, serialNumber, ip);
    } while (false);

    return thiz;
}