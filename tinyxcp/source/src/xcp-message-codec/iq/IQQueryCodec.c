/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQQueryCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_base.h>
#include <tiny_log.h>
#include <JsonObject.h>
#include <iq/IQQuery.h>
#include <value/JsonString.h>
#include "basic/ChildrenAddedCodec.h"
#include "basic/ChildrenRemovedCodec.h"
#include "basic/EventOccurredCodec.h"
#include "basic/InitializeCodec.h"
#include "basic/PropertiesChangedCodec.h"
#include "basic/SetAccessKeyCodec.h"
#include "basic/VerifyFinishCodec.h"
#include "basic/VerifyStartCodec.h"
#include "basic/GetPropertiesCodec.h"
#include "basic/SetPropertiesCodec.h"
#include "basic/InvokeActionCodec.h"

#define TAG     "IQQueryCodec"

TINY_BEGIN_DECLS


TINY_LOR
TinyRet IQQueryCodec_Encode(JsonObject *root, IQQuery *query)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(root, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(query, TINY_RET_E_ARG_NULL);

    do
    {
        ret = JsonObject_PutString(root, "method", IQMethod_ToString(query->method));
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "JsonObject_PutString");
            break;
        }

        JsonObject *content = JsonObject_New();
        if (content == NULL)
        {
            LOG_E(TAG, "JsonObject_New");
            break;
        }

        switch (query->method)
        {
            case IQ_METHOD_BYEBYE:
                break;

            case IQ_METHOD_CHILDREN_ADDED:
                ret = ChildrenAddedCodec_EncodeQuery(content, &query->content.childrenAdded);
                break;

            case IQ_METHOD_CHILDREN_REMOVED:
                ret = ChildrenRemovedCodec_EncodeQuery(content, &query->content.childrenRemoved);
                break;

            case IQ_METHOD_EVENT_OCCURRED:
                ret = EventOccurredCodec_EncodeQuery(content, &query->content.eventOccurred);
                break;

            case IQ_METHOD_GET_ACCESS_KEY:
                break;

            case IQ_METHOD_INITIALIZE:
                ret = InitializeCodec_EncodeQuery(content, &query->content.initialize);
                break;

            case IQ_METHOD_PING:
                break;

            case IQ_METHOD_PROPERTIES_CHANGED:
                ret = PropertiesChangedCodec_EncodeQuery(content, &query->content.propertiesChanged);
                break;

            case IQ_METHOD_SET_ACCESS_KEY:
                ret = SetAccessKeyCodec_EncodeQuery(content, &query->content.setAccessKey);
                break;

            case IQ_METHOD_VERIFY_FINISH:
                ret = VerifyFinishCodec_EncodeQuery(content, &query->content.verifyFinish);
                break;

            case IQ_METHOD_VERIFY_START:
                ret = VerifyStartCodec_EncodeQuery(content, &query->content.verifyStart);
                break;

            default:
                LOG_D(TAG, "not support method: %s", IQMethod_ToString(query->method));
                ret = TINY_RET_E_ARG_INVALID;
                break;
        }

        if (RET_FAILED(ret))
        {
            JsonObject_Delete(content);
            break;
        }

        if (content->data.list.size == 0)
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

TINY_LOR
TinyRet IQQueryCodec_Decode(IQQuery* query, JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(query, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(object, TINY_RET_E_ARG_NULL);

    do
    {
        JsonString *method = JsonObject_GetString(object, "method");
        JsonObject *content = JsonObject_GetObject(object, "content");

        if (method == NULL)
        {
            LOG_D(TAG, "method is null");
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        query->method = IQMethod_FromString(method->value);
        switch (query->method)
        {
            case IQ_METHOD_BYEBYE:
                break;

            case IQ_METHOD_GET_PROPERTIES:
                ret = GetPropertiesCodec_DecodeQuery(&query->content.getProperties, content);
                break;

            case IQ_METHOD_PING:
                break;

            case IQ_METHOD_SET_PROPERTIES:
                ret = SetPropertiesCodec_DecodeQuery(&query->content.setProperties, content);
                break;

            case IQ_METHOD_INVOKE_ACTION:
                ret = InvokeActionCodec_DecodeQuery(&query->content.invokeAction, content);
                break;

            default:
                LOG_D(TAG, "not support method: %s => %d", method->value, query->method);
                ret = TINY_RET_E_ARG_INVALID;
                break;
        }
    } while (false);

    return ret;
}