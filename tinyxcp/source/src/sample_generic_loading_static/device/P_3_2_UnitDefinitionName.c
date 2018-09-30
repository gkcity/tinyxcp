/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_2_UnitDefinitionName.h
 *
 * @remark
 *
 */

#include "P_3_2_UnitDefinitionName.h"

Property * P_3_2_UnitDefinitionName(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(2, "xiot-spec", "unit-definition-name", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = ACCESS_READ;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}