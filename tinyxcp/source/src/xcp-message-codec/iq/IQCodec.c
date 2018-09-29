/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <value/JsonString.h>
#include <tiny_log.h>
#include <value/JsonNumber.h>
#include "IQCodec.h"
#include "IQErrorCodec.h"
#include "IQQueryCodec.h"
#include "IQResultCodec.h"

#define TAG     "IQCodec"

TINY_LOR
TinyRet IQCodec_Encode(JsonObject *root, IQ *iq)
{
    TinyRet ret = TINY_RET_OK;
    JsonObject *object = NULL;

    do
    {
        object = JsonObject_New();
        if (object == NULL)
        {
            ret = TINY_RET_E_OUT_OF_MEMORY;
            break;
        }

        ret = JsonObject_PutString(object, "id", iq->id);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "out of memory");
            ret = TINY_RET_E_OUT_OF_MEMORY;
            break;
        }

        switch (iq->type)
        {
            case IQ_TYPE_QUERY:
                ret = JsonObject_PutString(object, "type", "query");
                if (RET_SUCCEEDED(ret))
                {
                    ret = IQQueryCodec_Encode(object, &iq->content.query);
                }
                break;

            case IQ_TYPE_RESULT:
                ret = JsonObject_PutString(object, "type", "result");
                if (RET_SUCCEEDED(ret))
                {
                    ret = IQResultCodec_Encode(object, &iq->content.result);
                }
                break;

            case IQ_TYPE_ERROR:
                ret = JsonObject_PutString(object, "type", "error");
                if (RET_SUCCEEDED(ret))
                {
                    ret = IQErrorCodec_Encode(object, &iq->content.error);
                }
                break;

            default:
                ret = TINY_RET_E_ARG_INVALID;
                break;
        }

        if (RET_FAILED(ret))
        {
            break;
        }

        ret = JsonObject_PutObject(root, "iq", object);
        if (RET_FAILED(ret))
        {
            break;
        }
    } while (false);

    if (RET_FAILED(ret))
    {
        if (object != NULL)
        {
            JsonObject_Delete(object);
        }
    }

    return ret;
}

TINY_LOR
TinyRet IQCodec_Decode(IQ* iq, JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;

    do
    {
        JsonString *id = JsonObject_GetString(object, "id");
        if (id == NULL)
        {
            LOG_E(TAG, "#id not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        strncpy(iq->id, id->value, MESSAGE_ID_LENGTH);

        JsonString *type = JsonObject_GetString(object, "type");
        if (type == NULL)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        if (STR_EQUAL("query", type->value))
        {
            iq->type = IQ_TYPE_QUERY;
            ret = IQQueryCodec_Decode(&iq->content.query, object);
            break;
        }
        else if (STR_EQUAL("result", type->value))
        {
            iq->type = IQ_TYPE_RESULT;
            ret = IQResultCodec_Decode(&iq->content.result, object);
            break;
        }
        else if (STR_EQUAL("error", type->value))
        {
            iq->type = IQ_TYPE_ERROR;
            ret = IQErrorCodec_Decode(&iq->content.error, object);
            break;
        }
        else
        {
            LOG_E(TAG, "iq type not support");
            ret = TINY_RET_E_ARG_INVALID;
        }
    } while (false);

    return ret;
}