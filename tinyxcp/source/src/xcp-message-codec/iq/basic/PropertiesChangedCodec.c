/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertiesChangedCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <JsonArray.h>
#include <operation/PropertyOperation.h>
#include <tiny_snprintf.h>
#include <tiny_log.h>
#include "PropertiesChangedCodec.h"
#include "xid/PIDCodec.h"

#define TAG     "PropertiesChangedCodec"

TinyRet PropertiesChangedCodec_EncodeQuery(JsonObject *root, QueryPropertiesChanged *propertiesChanged)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(root, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(propertiesChanged, TINY_RET_E_ARG_NULL);

    do
    {
        JsonArray *array = JsonArray_New();
        if (array == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        for (uint32_t i = 0; i < propertiesChanged->operations.properties.size; ++i)
        {
            PropertyOperation *o = (PropertyOperation *) TinyList_GetAt(&propertiesChanged->operations.properties, i);
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

        ret = JsonObject_PutArray(root, "properties", array);
        if (RET_FAILED(ret))
        {
            JsonArray_Delete(array);
            break;
        }
    } while (false);

    return ret;
}

TinyRet PropertiesChangedCodec_DecodeResult(ResultPropertiesChanged *propertiesChanged, JsonObject *content)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(propertiesChanged, TINY_RET_E_ARG_NULL);
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

        ret = PropertyOperations_Construct(&propertiesChanged->operations);
        if (RET_FAILED(ret))
        {
            break;
        }

        for (uint32_t i = 0; i < array->values.size; ++i)
        {
            JsonString *piid = NULL;
            JsonNumber *status = NULL;
            PropertyOperation *operation = NULL;
            JsonValue *p = (JsonValue *) TinyList_GetAt(&array->values, i);
             if (p->type != JSON_OBJECT)
            {
                LOG_E(TAG, "invalid content");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            piid = JsonObject_GetString(p->data.object, "piid");
            if (piid == NULL)
            {
                LOG_E(TAG, "invalid content");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            status = JsonObject_GetNumber(p->data.object, "status");
            if (status == NULL)
            {
                LOG_E(TAG, "invalid content");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            if (status->type != JSON_NUMBER_INTEGER)
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

            ret = PIDCodec_Decode(&operation->pid, piid->value);
            if (RET_FAILED(ret))
            {
                LOG_E(TAG, "invalid content");
                ret = TINY_RET_E_ARG_INVALID;
                break;
            }

            operation->status = (int) status->value.intValue;

            ret = TinyList_AddTail(&propertiesChanged->operations.properties, operation);
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