/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   Initialize.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "InitializeFactory.h"

XcpMessage * QueryInitialize_New(const char *id, const char *version, const char *authentication)
{
    XcpMessage * thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_QUERY;
        thiz->iq.content.query.method = IQ_METHOD_INITIALIZE;
        strncpy(thiz->iq.content.query.content.initialize.version, version, XCP_INITIALIZE_VERSION_LEN);
        strncpy(thiz->iq.content.query.content.initialize.authentication, authentication, XCP_AUTHENTICATION_LEN);
    }

    return thiz;
}