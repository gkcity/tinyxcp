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
    XcpMessage * thiz = NULL;

    RETURN_VAL_IF_FAIL(operation, NULL);

    thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_RESULT;
        thiz->iq.content.query.method = IQ_METHOD_EVENT_OCCURRED;

        if (RET_FAILED(EventOperation_Copy(&thiz->iq.content.query.content.eventOccurred.operation, operation)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
        }
    }

    return thiz;
}