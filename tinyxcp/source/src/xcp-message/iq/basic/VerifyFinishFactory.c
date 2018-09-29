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

#include "VerifyFinishFactory.h"

TINY_LOR
XcpMessage * QueryVerifyFinish_New(const char *id,
                                   const char *did,
                                   uint16_t productId,
                                   uint16_t productVersion,
                                   const char *signature,
                                   uint8_t codec)
{
    XcpMessage * thiz = NULL;

    RETURN_VAL_IF_FAIL(did, NULL);
    RETURN_VAL_IF_FAIL(productId, NULL);
    RETURN_VAL_IF_FAIL(productVersion, NULL);
    RETURN_VAL_IF_FAIL(signature, NULL);

    thiz = XcpMessage_New();
    if (thiz != NULL)
    {
        strncpy(thiz->iq.id, id, MESSAGE_ID_LENGTH);
        thiz->iq.type = IQ_TYPE_QUERY;
        thiz->iq.content.query.method = IQ_METHOD_VERIFY_FINISH;
        strncpy(thiz->iq.content.query.content.verifyFinish.did, did, DEVICE_ID_LENGTH);
        strncpy(thiz->iq.content.query.content.verifyFinish.signature, signature, XCP_SIGNATURE_LENGTH);
        thiz->iq.content.query.content.verifyFinish.productId = productId;
        thiz->iq.content.query.content.verifyFinish.productVersion = productVersion;
        thiz->iq.content.query.content.verifyFinish.codec = codec;
    }

    return thiz;
}