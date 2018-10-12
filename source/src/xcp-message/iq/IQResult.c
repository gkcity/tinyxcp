/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQResult.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_log.h>
#include "IQResult.h"

#define TAG     "IQResult"

TinyRet IQResult_Initialize(IQResult *thiz)
{
    TinyRet ret = TINY_RET_OK;

    switch (thiz->method)
    {
        case IQ_METHOD_BYEBYE:
            break;

        case IQ_METHOD_CHILDREN_ADDED:
            break;

        case IQ_METHOD_CHILDREN_REMOVED:
            break;

        case IQ_METHOD_EVENT_OCCURRED:
            break;

        case IQ_METHOD_GET_ACCESS_KEY:
            ret = ResultGetAccessKey_Construct(&thiz->content.getAccessKey);
            break;

        case IQ_METHOD_GET_CHILDREN:
            ret = ResultGetChildren_Construct(&thiz->content.getChildren);
            break;

        case IQ_METHOD_GET_DEVICE_TYPE:
            break;

        case IQ_METHOD_GET_PROPERTIES:
            ret = ResultGetProperties_Construct(&thiz->content.getProperties);
            break;

        case IQ_METHOD_INITIALIZE:
            break;

        case IQ_METHOD_INVOKE_ACTION:
            ret = ResultInvokeAction_Construct(&thiz->content.invokeAction);
            break;

        case IQ_METHOD_PING:
            break;

        case IQ_METHOD_PROPERTIES_CHANGED:
            ret = ResultPropertiesChanged_Construct(&thiz->content.propertiesChanged);
            break;

        case IQ_METHOD_SET_ACCESS_KEY:
            break;

        case IQ_METHOD_SET_PROPERTIES:
            ret = ResultSetProperties_Construct(&thiz->content.setProperties);
            break;

        case IQ_METHOD_UPDATE_DEVICE_TYPE:
            break;

        case IQ_METHOD_VERIFY_FINISH:
            break;

        case IQ_METHOD_VERIFY_START:
            ret = ResultVerifyStart_Construct(&thiz->content.verifyStart);
            break;

        default:
            LOG_E(TAG, "method not supported: %d", thiz->method);
            ret = TINY_RET_E_ARG_INVALID;
            break;
    }

    return ret;
}

void IQResult_Dispose(IQResult *thiz)
{
    switch (thiz->method)
    {
        case IQ_METHOD_UNDEFINED:
            break;

        case IQ_METHOD_BYEBYE:
            break;

        case IQ_METHOD_CHILDREN_ADDED:
            break;

        case IQ_METHOD_CHILDREN_REMOVED:
            break;

        case IQ_METHOD_EVENT_OCCURRED:
            break;

        case IQ_METHOD_GET_ACCESS_KEY:
            ResultGetAccessKey_Dispose(&thiz->content.getAccessKey);
            break;

        case IQ_METHOD_GET_CHILDREN:
            ResultGetChildren_Dispose(&thiz->content.getChildren);
            break;

        case IQ_METHOD_GET_DEVICE_TYPE:
            break;

        case IQ_METHOD_GET_PROPERTIES:
            ResultGetProperties_Dispose(&thiz->content.getProperties);
            break;

        case IQ_METHOD_INITIALIZE:
            break;

        case IQ_METHOD_INVOKE_ACTION:
            ResultInvokeAction_Dispose(&thiz->content.invokeAction);
            break;

        case IQ_METHOD_PING:
            break;

        case IQ_METHOD_PROPERTIES_CHANGED:
            ResultPropertiesChanged_Dispose(&thiz->content.propertiesChanged);
            break;

        case IQ_METHOD_SET_ACCESS_KEY:
            break;

        case IQ_METHOD_SET_PROPERTIES:
            ResultSetProperties_Dispose(&thiz->content.setProperties);
            break;

        case IQ_METHOD_UPDATE_DEVICE_TYPE:
            break;

        case IQ_METHOD_VERIFY_FINISH:
            break;

        case IQ_METHOD_VERIFY_START:
            ResultVerifyStart_Dispose(&thiz->content.verifyStart);
            break;

        default:
            LOG_E(TAG, "method not supported: %d", thiz->method);
            break;
    }
}