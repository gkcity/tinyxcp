/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_5_2_CollectingStatus.h
 *
 * @remark
 *
 */

#include "P_5_2_CollectingStatus.h"

static TinyRet P_5_2_CollectingStatus_SetValueList(Property *thiz)
{
    TinyRet ret = TINY_RET_OK;
    JsonValue * v_stopped = NULL;
    JsonValue * v_collecting = NULL;

    do
    {
        v_stopped = JsonValue_NewInteger(0);
        if (v_stopped == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        v_collecting = JsonValue_NewInteger(1);
        if (v_collecting == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        thiz->valueList = ValueList_New();
        if (thiz->valueList == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = ValueList_Put(thiz->valueList, v_stopped);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = ValueList_Put(thiz->valueList, v_collecting);
        if (RET_FAILED(ret))
        {
            break;
        }
    } while (false);

    if (v_stopped != NULL)
    {
        JsonValue_Delete(v_stopped);
    }
    if (v_collecting != NULL)
    {
        JsonValue_Delete(v_collecting);
    }

    return ret;
}

Property * P_5_2_CollectingStatus(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(2, "xiot-spec", "collecting-status", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_UINT32;

        if (RET_FAILED(P_5_2_CollectingStatus_SetValueList(thiz)))
        {
            Property_Delete(thiz);
            break;
        }
    } while (false);

    return thiz;
}