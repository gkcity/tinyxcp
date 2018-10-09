/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetAccessKeyFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "SetAccessKeyFactory.h"

TINY_LOR
XcpMessage * QuerySetAccessKey_New(const char *id, const char *key)
{
    XcpMessage * thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_QUERY;
        thiz->iq.content.query.method = IQ_METHOD_SET_ACCESS_KEY;
        strncpy(thiz->iq.content.query.content.setAccessKey.key, key, XCP_ACCESS_KEY_LEN);
    }

    return thiz;
}
