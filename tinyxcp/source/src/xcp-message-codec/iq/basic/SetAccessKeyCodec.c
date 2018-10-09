/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetAccessKeyCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "SetAccessKeyCodec.h"


TinyRet SetAccessKeyCodec_EncodeQuery(JsonObject *root, QuerySetAccessKey *query)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(root, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(query, TINY_RET_E_ARG_NULL);

    do
    {
        JsonObject *content = JsonObject_New();
        if (content == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = JsonObject_PutString(content, "key", query->key);
        if (RET_FAILED(ret))
        {
            JsonObject_Delete(content);
            break;
        }

        ret = JsonObject_PutObject(root, "content", content);
        if (RET_FAILED(ret))
        {
            JsonObject_Delete(content);
            break;
        }
    } while (false);

    return ret;}