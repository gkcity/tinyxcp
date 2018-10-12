/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   S_1_DeviceInformation.c
 *
 * @remark
 *
 */

#include "S_1_DeviceInformation.h"
#include "P_1_1_Manufacturer.h"
#include "P_1_2_Model.h"
#include "P_1_3_SerialNumber.h"
#include "P_1_4_FirmwareRevision.h"

Service * S_1_DeviceInformation(void)
{
    Service *thiz = NULL;

    do
    {
        thiz = Service_NewInstance(1, "xiot-spec", "device-information", 0x00007801, NULL);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_1_1_Manufacturer())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_1_2_Model())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_1_3_SerialNumber())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(TinyList_AddTail(&thiz->properties, P_1_4_FirmwareRevision())))
        {
            Service_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}