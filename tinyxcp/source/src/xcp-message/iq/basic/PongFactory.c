/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   Pong.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "PongFactory.h"

XcpMessage * Pong_New(const char *id)
{
    XcpMessage * thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_RESULT;
        thiz->iq.content.query.method = IQ_METHOD_PING;
    }

    return thiz;
}
