/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_1_UnitId.h
 *
 * @remark
 *
 */

#include "P_4_1_UnitId.h"

static TinyRet P_4_1_UnitId_SetValueRange(Property *thiz)
{
    TinyRet ret = TINY_RET_OK;
    JsonValue * min = NULL;
    JsonValue * max = NULL;
    JsonValue * step = NULL;

    do
    {
        min = JsonValue_NewString("00");
        if (min == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        max = JsonValue_NewString("FF");
        if (max == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        step = JsonValue_NewString("01");
        if (step == NULL)
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

Property * P_4_1_UnitId(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(1, "xiot-spec", "unit-id", 0x00000000, NULL, FORMAT_HEX, 0, NONE);
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(P_4_1_UnitId_SetValueRange(thiz)))
        {
            Property_Delete(thiz);
            break;
        }
    } while (false);

    return thiz;
}