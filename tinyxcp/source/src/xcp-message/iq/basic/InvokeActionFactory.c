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
    XcpMessage * thiz = NULL;

    RETURN_VAL_IF_FAIL(operation, NULL);

    thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_RESULT;
        thiz->iq.content.result.method = IQ_METHOD_INVOKE_ACTION;

        if (RET_FAILED(ActionOperation_Copy(&thiz->iq.content.result.content.invokeAction.operation, operation)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
        }
    }

    return thiz;
}