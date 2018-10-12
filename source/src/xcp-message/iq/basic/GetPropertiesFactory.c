/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetPropertiesFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "GetPropertiesFactory.h"

TINY_LOR
XcpMessage * ResultGetProperties_New(const char *id, PropertyOperations *operations)
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

        if (RET_FAILED(IQ_InitializeResult(&thiz->iq, id, IQ_METHOD_GET_PROPERTIES)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }


        if (RET_FAILED(PropertyOperations_Copy(&thiz->iq.content.result.content.getProperties.operations, operations)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}