/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertiesChangedFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "PropertiesChangedFactory.h"

TINY_LOR
XcpMessage * QueryPropertiesChanged_New(const char *id, PropertyOperations *operations)
{
    XcpMessage *thiz = NULL;

    RETURN_VAL_IF_FAIL(operations, NULL);

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeQuery(&thiz->iq, id, IQ_METHOD_PROPERTIES_CHANGED)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(PropertyOperations_Copy(&thiz->iq.content.query.content.propertiesChanged.operations, operations)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}