/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetAccessKeyCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "GetAccessKeyCodec.h"

TinyRet GetAccessKeyCodec_DecodeResult(ResultGetAccessKey *result, JsonObject *content)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(result, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(content, TINY_RET_E_ARG_NULL);

    do
    {
        JsonString *key = JsonObject_GetString(content, "key");
        if (key == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        strncpy(result->key, key->value, XCP_ACCESS_KEY_LEN);
    } while (false);

    return ret;
}