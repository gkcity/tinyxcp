/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyFinishCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "VerifyFinishCodec.h"

TinyRet VerifyFinishCodec_EncodeQuery(JsonObject *content, QueryVerifyFinish *verifyFinish)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        ret = JsonObject_PutString(content, "device-id", verifyFinish->did);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = JsonObject_PutInteger(content, "product-id", verifyFinish->productId);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = JsonObject_PutInteger(content, "product-version", verifyFinish->productVersion);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = JsonObject_PutString(content, "signature", verifyFinish->signature);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = JsonObject_PutInteger(content, "codec", verifyFinish->codec);
        if (RET_FAILED(ret))
        {
            break;
        }
    } while (false);

    return ret;
}