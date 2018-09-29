/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ByebyeFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "ByebyeFactory.h"

XcpMessage * Byebye_New(const char * id)
{
    XcpMessage * thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_QUERY;
        thiz->iq.content.query.method = IQ_METHOD_BYEBYE;
    }

    return thiz;
}

XcpMessage * Byebye_NewResult(const char * id)
{
    XcpMessage * thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_RESULT;
        thiz->iq.content.query.method = IQ_METHOD_BYEBYE;
    }

    return thiz;
}