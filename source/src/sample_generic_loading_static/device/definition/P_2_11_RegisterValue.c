/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_2_11_RegisterValue.h
 *
 * @remark
 *
 */

#include "P_2_11_RegisterValue.h"

static TinyRet P_2_11_RegisterValue_SetValueRange(Property *thiz)
{
    TinyRet ret = TINY_RET_OK;
    JsonValue * min = NULL;
    JsonValue * max = NULL;
    JsonValue * step = NULL;

    do
    {
        min = JsonValue_NewString("0000");
        if (min == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        max = JsonValue_NewString("FFFF");
        if (min == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        step = JsonValue_NewString("01");
        if (min == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        thiz->valueRange = ValueRange_New(min, max, step);
        if (thiz->valueRange == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }
    } while (false);

    if (min != NULL)
    {
        JsonValue_Delete(min);
    }

    if (max != NULL)
    {
        JsonValue_Delete(max);
    }

    if (step != NULL)
    {
        JsonValue_Delete(step);
    }

    return ret;
}

Property * P_2_11_RegisterValue(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(11, "xiot-spec", "register-value", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = 0;
        thiz->format = FORMAT_HEX;

        if (RET_FAILED(P_2_11_RegisterValue_SetValueRange(thiz)))
        {
            Property_Delete(thiz);
            break;
        }
    } while (false);

    return thiz;
}