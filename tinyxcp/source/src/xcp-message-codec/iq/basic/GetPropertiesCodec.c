/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetPropertiesCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <JsonArray.h>
#include <tiny_log.h>
#include <value/JsonString.h>
#include <operation/PropertyOperation.h>
#include "../../xid/PIDCodec.h"
#include <tiny_snprintf.h>
#include "GetPropertiesCodec.h"

#define TAG "GetPropertiesCodec"

TinyRet GetPropertiesCodec_DecodeQuery(QueryGetProperties *query, JsonObject *content)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(query, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(content, TINY_RET_E_ARG_NULL);

    do
    {
        JsonArray *array = JsonObject_GetArray(content, "properties");
        if (array == NULL)
        {
            LOG_E(TAG, "properties not found");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        ret = PropertyOperations_Construct(&query->properties);
        if (RET_FAILED(ret))
        {
            break;
        }

        for (uint32_t i = 0; i < array->values.size; ++i)
        {
            PropertyOperation *operation = NULL;
            JsonValue *value = (JsonValue *) TinyList_GetAt(&array->values, i);
            if (value->type != JSON_STRING)
            {
                LOG_E(TAG, "invalid content");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            operation = PropertyOperation_New();
            if (operation == NULL)
            {
                LOG_E(TAG, "PropertyOperation_New failed");
                ret = TINY_RET_E_NEW;
                break;
            }

            ret = PIDCodec_Decode(&operation->pid, value->data.string->value);
            if (RET_FAILED(ret))
            {
                operation->status = -100;
            }

            ret = TinyList_AddTail(&query->properties.properties, operation);
            if (RET_FAILED(ret))
            {
                LOG_E(TAG, "TinyList_AddTail failed");
                PropertyOperation_Delete(operation);
                break;
            }
        }
    } while (false);

    return ret;
}

TinyRet GetPropertiesCodec_EncodeResult(JsonObject *content, ResultGetProperties *getProperties)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(content, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(getProperties, TINY_RET_E_ARG_NULL);

    do
    {
        JsonArray *array = JsonArray_New();
        if (array == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        for (uint32_t i = 0; i < getProperties->properties.properties.size; ++i)
        {
            PropertyOperation *o = (PropertyOperation *) TinyList_GetAt(&getProperties->properties.properties, i);
            JsonObject *object = NULL;
            JsonValue *value = NULL;
            char pid[256];

            object = JsonObject_New();
            if (object == NULL)
            {
                ret = TINY_RET_E_NEW;
                break;
            }

            memset(pid, 0, 256);
            tiny_snprintf(pid, 256, "%s.%u.%u", o->pid.did, o->pid.siid, o->pid.iid);

            ret = JsonObject_PutString(object, "pid", pid);
            if (RET_FAILED(ret))
            {
                JsonObject_Delete(object);
                break;
            }

            ret = JsonObject_PutInteger(object, "status", o->status);
            if (RET_FAILED(ret))
            {
                JsonObject_Delete(object);
                break;
            }

            if (o->status != 0)
            {
                continue;
            }

            if (o->value == NULL)
            {
                continue;
            }

            value = JsonValue_NewFrom(o->value);
            if (value == NULL)
            {
                JsonObject_Delete(object);
                break;
            }

            ret = JsonObject_PutValue(object, "value", value);
            if (RET_FAILED(ret))
            {
                JsonObject_Delete(object);
                break;
            }

            ret = JsonArray_AddObject(array, object);
            if (RET_FAILED(ret))
            {
                JsonObject_Delete(object);
                break;
            }
        }

        if (RET_FAILED(ret))
        {
            JsonArray_Delete(array);
            break;
        }

        ret = JsonObject_PutArray(content, "properties", array);
        if (RET_FAILED(ret))
        {
            JsonArray_Delete(array);
            break;
        }
    } while (false);

    return ret;
}