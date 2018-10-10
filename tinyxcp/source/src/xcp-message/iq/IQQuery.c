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

void IQQuery_Dispose(IQQuery *thiz)
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
            break;

        case IQ_METHOD_GET_CHILDREN:
            break;

        case IQ_METHOD_GET_DEVICE_TYPE:
            break;

        case IQ_METHOD_GET_PROPERTIES:
            break;

        case IQ_METHOD_INITIALIZE:
            break;

        case IQ_METHOD_INVOKE_ACTION:
            break;

        case IQ_METHOD_PING:
            break;

        case IQ_METHOD_PROPERTIES_CHANGED:
            break;

        case IQ_METHOD_SET_ACCESS_KEY:
            break;

        case IQ_METHOD_SET_PROPERTIES:
            break;

        case IQ_METHOD_UPDATE_DEVICE_TYPE:
            break;

        case IQ_METHOD_VERIFY_FINISH:
            break;

        case IQ_METHOD_VERIFY_START:
            break;

        default:
            LOG_E(TAG, "method not supported: %d", thiz->method);
            break;
    }
}