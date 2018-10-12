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

TinyRet SetAccessKeyCodec_EncodeQuery(JsonObject *content, QuerySetAccessKey *query)
{
    RETURN_VAL_IF_FAIL(content, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(query, TINY_RET_E_ARG_NULL);

    return JsonObject_PutString(content, "key", query->key);
}