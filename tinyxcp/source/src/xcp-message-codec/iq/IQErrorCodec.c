/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQErrorCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_log.h>
#include <value/JsonNumber.h>
#include <value/JsonString.h>
#include "IQErrorCodec.h"

#define TAG     "IQErrorCodec"

TINY_LOR
TinyRet IQErrorCodec_Encode(JsonObject *root, IQError *error)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(root, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(error, TINY_RET_E_ARG_NULL);

    do
    {
        JsonObject *content = JsonObject_New();
        if (content == NULL)
        {
            LOG_E(TAG, "out of memory");
            break;
        }

        ret = JsonObject_PutInteger(content, "status", error->status);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "out of memory");
            JsonObject_Delete(content);
            break;
        }

        ret = JsonObject_PutString(content, "description", error->description);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "out of memory");
            JsonObject_Delete(content);
            break;
        }

        ret = JsonObject_PutObject(root, "content", content);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "out of memory");
            JsonObject_Delete(content);
            break;
        }
    } while (false);

    return ret;
}

TINY_LOR
TinyRet IQErrorCodec_Decode(IQError* error, JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(error, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(object, TINY_RET_E_ARG_NULL);

    do
    {
        JsonObject *content = NULL;
        JsonValue * status = NULL;
        JsonValue * description = NULL;

        content = JsonObject_GetObject(object, "content");
        if (content == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        status = JsonObject_GetValue(content, "status");
        if (status == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        description = JsonObject_GetValue(content, "description");
        if (description == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (status->type != JSON_NUMBER || description->type != JSON_STRING)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (status->data.number->type != JSON_NUMBER_INTEGER)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        error->status = (int)status->data.number->value.intValue;
        strncpy(error->description, description->data.string->value, XCP_DESCRIPTION_LENGTH);
    } while (false);

    return ret;
}