/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQQuery.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_log.h>
#include "IQQuery.h"

#define TAG     "IQQuery"

TinyRet IQQuery_Initialize(IQQuery *thiz)
{
    TinyRet ret = TINY_RET_OK;

    switch (thiz->method)
    {
        case IQ_METHOD_BYEBYE:
            break;

        case IQ_METHOD_CHILDREN_ADDED:
            ret = QueryChildrenAdded_Construct(&thiz->content.childrenAdded);
            break;

        case IQ_METHOD_CHILDREN_REMOVED:
            ret = QueryChildrenRemoved_Construct(&thiz->content.childrenRemoved);
            break;

        case IQ_METHOD_EVENT_OCCURRED:
            ret = QueryEventOccurred_Construct(&thiz->content.eventOccurred);
            break;

        case IQ_METHOD_GET_ACCESS_KEY:
            break;

        case IQ_METHOD_GET_CHILDREN:
            break;

        case IQ_METHOD_GET_DEVICE_TYPE:
            break;

        case IQ_METHOD_GET_PROPERTIES:
            ret = QueryGetProperties_Construct(&thiz->content.getProperties);
            break;

        case IQ_METHOD_INITIALIZE:
            ret = QueryInitialize_Construct(&thiz->content.initialize);
            break;

        case IQ_METHOD_INVOKE_ACTION:
            ret = QueryInvokeAction_Construct(&thiz->content.invokeAction);
            break;

        case IQ_METHOD_PING:
            break;

        case IQ_METHOD_PROPERTIES_CHANGED:
            ret = QueryPropertiesChanged_Construct(&thiz->content.propertiesChanged);
            break;

        case IQ_METHOD_SET_ACCESS_KEY:
            ret = QuerySetAccessKey_Construct(&thiz->content.setAccessKey);
            break;

        case IQ_METHOD_SET_PROPERTIES:
            ret = QuerySetProperties_Construct(&thiz->content.setProperties);
            break;

        case IQ_METHOD_UPDATE_DEVICE_TYPE:
            break;

        case IQ_METHOD_VERIFY_FINISH:
            ret = QueryVerifyFinish_Construct(&thiz->content.verifyFinish);
            break;

        case IQ_METHOD_VERIFY_START:
            ret = QueryVerifyStart_Construct(&thiz->content.verifyStart);
            break;

        default:
            LOG_E(TAG, "method not supported: %d", thiz->method);
            ret = TINY_RET_E_ARG_INVALID;
            break;
    }

    return ret;
}

void IQQuery_Dispose(IQQuery *thiz)
{
    switch (thiz->method)
    {
        case IQ_METHOD_UNDEFINED:
            break;

        case IQ_METHOD_BYEBYE:
            break;

        case IQ_METHOD_CHILDREN_ADDED:
            QueryChildrenAdded_Dispose(&thiz->content.childrenAdded);
            break;

        case IQ_METHOD_CHILDREN_REMOVED:
            QueryChildrenRemoved_Dispose(&thiz->content.childrenRemoved);
            break;

        case IQ_METHOD_EVENT_OCCURRED:
            QueryEventOccurred_Dispose(&thiz->content.eventOccurred);
            break;

        case IQ_METHOD_GET_ACCESS_KEY:
            break;

        case IQ_METHOD_GET_CHILDREN:
            break;

        case IQ_METHOD_GET_DEVICE_TYPE:
            break;

        case IQ_METHOD_GET_PROPERTIES:
            QueryGetProperties_Dispose(&thiz->content.getProperties);
            break;

        case IQ_METHOD_INITIALIZE:
            QueryInitialize_Dispose(&thiz->content.initialize);
            break;

        case IQ_METHOD_INVOKE_ACTION:
            QueryInvokeAction_Dispose(&thiz->content.invokeAction);
            break;

        case IQ_METHOD_PING:
            break;

        case IQ_METHOD_PROPERTIES_CHANGED:
            QueryPropertiesChanged_Dispose(&thiz->content.propertiesChanged);
            break;

        case IQ_METHOD_SET_ACCESS_KEY:
            QuerySetAccessKey_Dispose(&thiz->content.setAccessKey);
            break;

        case IQ_METHOD_SET_PROPERTIES:
            QuerySetProperties_Dispose(&thiz->content.setProperties);
            break;

        case IQ_METHOD_UPDATE_DEVICE_TYPE:
            break;

        case IQ_METHOD_VERIFY_FINISH:
            QueryVerifyFinish_Dispose(&thiz->content.verifyFinish);
            break;

        case IQ_METHOD_VERIFY_START:
            QueryVerifyStart_Dispose(&thiz->content.verifyStart);
            break;

        default:
            LOG_E(TAG, "method not supported: %d", thiz->method);
            break;
    }
}