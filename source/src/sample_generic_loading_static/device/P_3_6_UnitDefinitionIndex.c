/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_6_UnitDefinitionIndex.h
 *
 * @remark
 *
 */

#include "P_3_6_UnitDefinitionIndex.h"

Property * P_3_6_UnitDefinitionIndex(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(6, "xiot-spec", "unit-definition-index", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}