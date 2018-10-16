/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   P_3_3_UnitDefinitionDescription.h
 *
 * @remark
 *
 */

#include "P_3_3_UnitDefinitionDescription.h"

Property * P_3_3_UnitDefinitionDescription(void)
{
    Property *thiz = NULL;

    do
    {
        thiz = Property_NewInstance(3, "xiot-spec", "unit-definition-description", 0x00000000, NULL);
        if (thiz == NULL)
        {
            break;
        }

        thiz->access = 0;
        thiz->format = FORMAT_STRING;
    } while (false);

    return thiz;
}