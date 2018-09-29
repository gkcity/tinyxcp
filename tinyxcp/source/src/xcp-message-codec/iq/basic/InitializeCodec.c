/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InitializeCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "InitializeCodec.h"

TinyRet InitializeCodec_EncodeQuery(JsonObject *root, QueryInitialize *initialize)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        JsonObject *content = JsonObject_New();
        if (content == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = JsonObject_PutString(content, "version", initialize->version);
        if (RET_FAILED(ret))
        {
            JsonObject_Delete(content);
            break;
        }

        ret = JsonObject_PutString(content, "authentication", initialize->authentication);
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

    return ret;
}
