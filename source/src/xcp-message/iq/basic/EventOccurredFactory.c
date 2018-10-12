/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   EventOccurredFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "EventOccurredFactory.h"

TINY_LOR
XcpMessage * QueryEventOccurred_New(const char *id, EventOperation *operation)
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

        if (RET_FAILED(IQ_InitializeQuery(&thiz->iq, id, IQ_METHOD_EVENT_OCCURRED)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }

        if (RET_FAILED(EventOperation_Copy(&thiz->iq.content.query.content.eventOccurred.operation, operation)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
        }
    } while (false);

    return thiz;
}