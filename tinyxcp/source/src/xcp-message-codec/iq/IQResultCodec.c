/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQResultCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_log.h>
#include <value/JsonString.h>
#include <iq/basic/GetAccessKeyCodec.h>
#include "basic/GetChildrenCodec.h"
#include "basic/GetPropertiesCodec.h"
#include "basic/SetPropertiesCodec.h"
#include "basic/EventOccurredCodec.h"
#include "basic/PropertiesChangedCodec.h"
#include "basic/VerifyStartCodec.h"
#include "basic/InvokeActionCodec.h"
#include "IQResultCodec.h"

#define TAG     "IQResultCodec"

TINY_LOR
TinyRet IQResultCodec_Encode(JsonObject *root, IQResult *result)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(root, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(result, TINY_RET_E_ARG_NULL);

    do
    {
        JsonObject *content = JsonObject_New();
        if (content == NULL)
        {
            ret = TINY_RET_E_NEW;
            LOG_E(TAG, "out of memory");
            break;
        }

        ret = JsonObject_PutString(root, "method", IQMethod_ToString(result->method));
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "out of memory");
            JsonObject_Delete(content);
            break;
        }

        switch (result->method)
        {
            case IQ_METHOD_BYEBYE:
                break;

            case IQ_METHOD_GET_CHILDREN:
                ret = GetChildrenCodec_EncodeResult(content, &result->content.getChildren);
                if (RET_SUCCEEDED(ret))
                {
                    ret = JsonObject_PutObject(root, "content", content);
                }
                break;

            case IQ_METHOD_GET_PROPERTIES:
                ret = GetPropertiesCodec_EncodeResult(content, &result->content.getProperties);
                if (RET_SUCCEEDED(ret))
                {
                    ret = JsonObject_PutObject(root, "content", content);
                }
                break;

            case IQ_METHOD_PING:
                break;

            case IQ_METHOD_SET_PROPERTIES:
                ret = SetPropertiesCodec_EncodeResult(content, &result->content.setProperties);
                if (RET_SUCCEEDED(ret))
                {
                    ret = JsonObject_PutObject(root, "content", content);
                }
                break;

            case IQ_METHOD_INVOKE_ACTION:
                ret = InvokeActionCodec_EncodeResult(content, &result->content.invokeAction);
                if (RET_SUCCEEDED(ret))
                {
                    ret = JsonObject_PutObject(root, "content", content);
                }
                break;

            default:
                LOG_D(TAG, "not support method: %s", IQMethod_ToString(result->method));
                ret = TINY_RET_E_ARG_INVALID;
                break;
        }

        if (RET_FAILED(ret))
        {
            JsonObject_Delete(content);
        }
    } while (false);

    return ret;
}

TINY_LOR
TinyRet IQResultCodec_Decode(IQResult* result, JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(result, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(object, TINY_RET_E_ARG_NULL);

    do
    {
        JsonObject *content = JsonObject_GetObject(object, "content");
        JsonString *method = JsonObject_GetString(object, "method");

        if (method == NULL)
        {
            LOG_D(TAG, "method is null");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        result->method = IQMethod_FromString(method->value);
        switch (result->method)
        {
            case IQ_METHOD_BYEBYE:
                break;

            case IQ_METHOD_CHILDREN_ADDED:
//                ret = ChildrenAddedCodec_DecodeResult(&result->content.childrenAdded, content);
                break;

            case IQ_METHOD_CHILDREN_REMOVED:
//                ret = ChildrenRemovedCodec_DecodeResult(&result->content.childrenRemoved, content);
                break;

            case IQ_METHOD_EVENT_OCCURRED:
                ret = EventOccurredCodec_DecodeResult(&result->content.eventOccurred, content);
                break;

            case IQ_METHOD_GET_ACCESS_KEY:
                ret = GetAccessKeyCodec_DecodeResult(&result->content.getAccessKey, content);
                break;

            case IQ_METHOD_INITIALIZE:
                break;

            case IQ_METHOD_PING:
                break;

            case IQ_METHOD_PROPERTIES_CHANGED:
                ret = PropertiesChangedCodec_DecodeResult(&result->content.propertiesChanged, content);
                break;

            case IQ_METHOD_SET_ACCESS_KEY:
                break;

            case IQ_METHOD_VERIFY_FINISH:
                break;

            case IQ_METHOD_VERIFY_START:
                ret = VerifyStartCodec_DecodeResult(&result->content.verifyStart, content);
                break;

            default:
                LOG_D(TAG, "not support method: %s", method->value);
                ret = TINY_RET_E_ARG_INVALID;
                break;
        }
    } while (false);

    return ret;
}