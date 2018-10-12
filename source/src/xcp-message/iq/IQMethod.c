/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQMethod.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "IQMethod.h"

typedef struct _IQMethod_String
{
    IQMethod        method;
    const char    * string;
} IQMethod_String;

static IQMethod_String _method_string_mappings[] =
        {
                {IQ_METHOD_BYEBYE, "urn:xiot:bye-bye"},
                {IQ_METHOD_CHILDREN_ADDED, "urn:xiot:children-added"},
                {IQ_METHOD_CHILDREN_REMOVED, "urn:xiot:children-removed"},
                {IQ_METHOD_EVENT_OCCURRED, "urn:xiot:event-occurred"},
                {IQ_METHOD_GET_ACCESS_KEY, "urn:xiot:get-access-key"},
                {IQ_METHOD_GET_CHILDREN, "urn:xiot:get-children"},
                {IQ_METHOD_GET_DEVICE_TYPE, "urn:xiot:get-device-type"},
                {IQ_METHOD_GET_PROPERTIES, "urn:xiot:get-properties"},
                {IQ_METHOD_INITIALIZE, "urn:xiot:initialize"},
                {IQ_METHOD_INVOKE_ACTION, "urn:xiot:invoke-action"},
                {IQ_METHOD_PING, "urn:xiot:ping"},
                {IQ_METHOD_PROPERTIES_CHANGED, "urn:xiot:properties-changed"},
                {IQ_METHOD_SET_ACCESS_KEY, "urn:xiot:set-access-key"},
                {IQ_METHOD_SET_PROPERTIES, "urn:xiot:set-properties"},
                {IQ_METHOD_UPDATE_DEVICE_TYPE, "urn:xiot:update-device-type"},
                {IQ_METHOD_VERIFY_FINISH, "urn:xiot:verify-finish"},
                {IQ_METHOD_VERIFY_START, "urn:xiot:verify-start"},
        };

const char * IQMethod_ToString(IQMethod method)
{
    uint32_t size = DIM(_method_string_mappings);

    for (uint32_t i = 0; i < size; ++i)
    {
        if (_method_string_mappings[i].method == method)
        {
            return _method_string_mappings[i].string;
        }
    }

    return NULL;
}

IQMethod IQMethod_FromString(const char *string)
{
    uint32_t size = DIM(_method_string_mappings);

    for (uint32_t i = 0; i < size; ++i)
    {
        if (STR_EQUAL(_method_string_mappings[i].string, string))
        {
            return _method_string_mappings[i].method;
        }
    }

    return IQ_METHOD_UNDEFINED;
}