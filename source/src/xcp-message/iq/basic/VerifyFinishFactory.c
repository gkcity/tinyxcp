/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyFinishFactory.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_snprintf.h>
#include "VerifyFinishFactory.h"

TINY_LOR
XcpMessage *QueryVerifyFinish_New(const char *id, const char *udid, const char *signature, uint8_t codec)
{
    XcpMessage *thiz = NULL;

    RETURN_VAL_IF_FAIL(udid, NULL);
    RETURN_VAL_IF_FAIL(signature, NULL);

    do
    {
        thiz = XcpMessage_New();
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(IQ_InitializeQuery(&thiz->iq, id, IQ_METHOD_VERIFY_FINISH)))
        {
            XcpMessage_Delete(thiz);
            thiz = NULL;
            break;
        }

        strncpy(thiz->iq.content.query.content.verifyFinish.udid, udid, UDID_LENGTH);
        strncpy(thiz->iq.content.query.content.verifyFinish.signature, signature, XCP_SIGNATURE_LENGTH);
        thiz->iq.content.query.content.verifyFinish.codec = codec;
    } while (false);

    return thiz;
}