/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_4_4_UnitDefinitionId.h
 *
 * @remark
 *
 */

#include "P_4_4_UnitDefinitionId.h"

Property * P_4_4_UnitDefinitionId(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(4, "xiot-spec", "unit-definition-id", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = 0;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}