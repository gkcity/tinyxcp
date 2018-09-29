/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InvokeActionCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_log.h>
#include <value/JsonString.h>
#include "../../xid/AIDCodec.h"
#include <tiny_snprintf.h>
#include "InvokeActionCodec.h"

#define TAG "InvokeActionCodec"

TinyRet InvokeActionCodec_DecodeQuery(QueryInvokeAction *query, JsonObject *content)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(query, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(content, TINY_RET_E_ARG_NULL);

    do
    {
        JsonArray *in = JsonObject_GetArray(content, "in");
        JsonString *aid = JsonObject_GetString(content, "aid");
        if (aid == NULL)
        {
            LOG_E(TAG, "aid not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        ret = AIDCodec_Decode(&query->operation.aid, aid->value);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "AIDCodec_Decode FAILED");
            query->operation.status = -100;
            break;
        }

        if (in != NULL)
        {
            if (RET_FAILED(JsonArray_Copy(&query->operation.in, in)))
            {
                LOG_E(TAG, "JsonArray_Copy FAILED");
                query->operation.status = -1000;
                break;
            }
        }
    } while (false);

    return ret;
}

TinyRet InvokeActionCodec_EncodeResult(JsonObject *content, ResultInvokeAction *result)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(content, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(result, TINY_RET_E_ARG_NULL);

    do
    {
        char aid[256];
        JsonArray *out = NULL;

        memset(aid, 0, 256);
        tiny_snprintf(aid, 256, "%s.%u.%u", result->operation.aid.did, result->operation.aid.siid, result->operation.aid.iid);

        ret = JsonObject_PutString(content, "aid", aid);
        if (RET_FAILED(ret))
        {
            break;
        }

        ret = JsonObject_PutInteger(content, "status", result->operation.status);
        if (RET_FAILED(ret))
        {
            break;
        }

        if (result->operation.status != 0)
        {
            break;
        }

        if (result->operation.out.values.size == 0)
        {
            break;
        }

        out = JsonArray_NewFrom(&result->operation.out);
        if (out == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = JsonObject_PutArray(content, "out", out);
        if (RET_FAILED(ret))
        {
            JsonArray_Delete(out);
            break;
        }
    } while (false);

    return ret;
}