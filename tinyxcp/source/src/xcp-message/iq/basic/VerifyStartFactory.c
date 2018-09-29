/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyStart.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "VerifyStartFactory.h"

TINY_LOR
XcpMessage * QueryVerifyStart_New(const char *id, const char * publicKey)
{
    XcpMessage * thiz = NULL;

    RETURN_VAL_IF_FAIL(publicKey, NULL);

    thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_QUERY;
        thiz->iq.content.query.method = IQ_METHOD_VERIFY_START;
        strncpy(thiz->iq.content.query.content.verifyStart.publicKey, publicKey, XCP_PUBLIC_KEY_LENGTH);
    }

    return thiz;
}