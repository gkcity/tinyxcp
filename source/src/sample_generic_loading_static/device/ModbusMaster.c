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
#include "S_1_DeviceInformation.h"
#include "S_2_ModbusController.h"
#include "S_3_ModbusUnitDefinitionManagement.h"
#include "S_4_ModbusUnitManagement.h"
#include "S_5_ModbusCollector.h"

Device *ModbusMaster(const char *did,
                     uint16_t productId,
                     uint16_t productVersion,
                     const char *ltsk,
                     PropertyOnGet onGet,
                     PropertyOnSet onSet,
                     ActionOnInvoke onInvoke)
{
    Device *thiz = NULL;

    do
    {
        thiz = Device_New();
        if (thiz == NULL)
        {
            break;
        }

        strncpy(thiz->ltsk, ltsk, DEVICE_LTSK_LENGTH);
        tiny_snprintf(thiz->did, DEVICE_ID_LENGTH, "%s@%d", did, productId);
        thiz->productId = productId;
        thiz->productVersion = productVersion;
        thiz->onSet = onSet;
        thiz->onGet = onGet;
        thiz->onInvoke = onInvoke;

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
    } while (false);

    return thiz;
}