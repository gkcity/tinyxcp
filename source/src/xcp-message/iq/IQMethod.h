/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQMethod.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_METHOD_H__
#define __IQ_METHOD_H__

#include <tiny_base.h>
#include <tiny_lor.h>

TINY_BEGIN_DECLS


typedef enum _IQMethod
{
    IQ_METHOD_UNDEFINED             = 0x00,
    IQ_METHOD_BYEBYE                = 0x01,
    IQ_METHOD_CHILDREN_ADDED        = 0x02,
    IQ_METHOD_CHILDREN_REMOVED      = 0x03,
    IQ_METHOD_EVENT_OCCURRED        = 0x04,
    IQ_METHOD_GET_ACCESS_KEY        = 0x05,
    IQ_METHOD_GET_CHILDREN          = 0x06,
    IQ_METHOD_GET_DEVICE_TYPE       = 0x07,
    IQ_METHOD_GET_PROPERTIES        = 0x08,
    IQ_METHOD_INITIALIZE            = 0x09,
    IQ_METHOD_INVOKE_ACTION         = 0x0A,
    IQ_METHOD_PING                  = 0x0B,
    IQ_METHOD_PROPERTIES_CHANGED    = 0x0C,
    IQ_METHOD_SET_ACCESS_KEY        = 0x0D,
    IQ_METHOD_SET_PROPERTIES        = 0x0E,
    IQ_METHOD_UPDATE_DEVICE_TYPE    = 0x0F,
    IQ_METHOD_VERIFY_FINISH         = 0x10,
    IQ_METHOD_VERIFY_START          = 0x11,
} IQMethod;

const char * IQMethod_ToString(IQMethod method);

IQMethod IQMethod_FromString(const char *string);


TINY_END_DECLS

#endif /* __IQ_METHOD_H__  */