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
    XcpMessage *thiz = NULL;

    RETURN_VAL_IF_FAIL(publicKey, NULL);

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeQuery(&thiz->iq, id, IQ_METHOD_VERIFY_START)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }

        strncpy(thiz->iq.content.query.content.verifyStart.publicKey, publicKey, XCP_PUBLIC_KEY_LENGTH);
    } while (false);

    return thiz;
}