/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InvokeActionFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "InvokeActionFactory.h"


TINY_LOR
XcpMessage * ResultInvokeAction_New(const char *id, ActionOperation *operation)
{
    XcpMessage *thiz = NULL;

    RETURN_VAL_IF_FAIL(operation, NULL);

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeResult(&thiz->iq, id, IQ_METHOD_INVOKE_ACTION)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(ActionOperation_Copy(&thiz->iq.content.result.content.invokeAction.operation, operation)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (false);

    return thiz;
}