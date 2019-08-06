/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_7_CoilValue.h
 *
 * @remark
 *
 */

#include "P_2_7_CoilValue.h"

static TinyRet P_2_7_CoilValue_SetValueList(Property *thiz)
{
    TinyRet ret = TINY_RET_OK;
    JsonValue * v_off = NULL;
    JsonValue * v_on = NULL;

    do
    {
        v_off = JsonValue_NewString("0000");
        if (v_off == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        v_on = JsonValue_NewString("FF00");
        if (v_on == NULL)
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

        ret = ValueList_Put(thiz->valueList, v_off);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = ValueList_Put(thiz->valueList, v_on);
        if (RET_FAILED(ret))
        {
            break;
        }
    } while (false);

    if (v_off != NULL)
    {
        JsonValue_Delete(v_off);
    }
    if (v_on != NULL)
    {
        JsonValue_Delete(v_on);
    }

    return ret;
}

Property * P_2_7_CoilValue(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(7, "xiot-spec", "coil-value", 0x00000000, NULL, FORMAT_HEX, 0, NONE);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(P_2_7_CoilValue_SetValueList(thiz)))
        {
            Property_Delete(thiz);
            break;
        }
    } while (false);

    return thiz;
}