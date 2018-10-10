/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQResult.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_RESULT_H__
#define __IQ_RESULT_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <iq/basic/EventOccurred.h>
#include <iq/basic/GetChildren.h>
#include <iq/basic/GetProperties.h>
#include <iq/basic/SetProperties.h>
#include <iq/basic/PropertiesChanged.h>
#include <iq/basic/VerifyStart.h>
#include <iq/basic/InvokeAction.h>
#include <iq/basic/GetAccessKey.h>
#include "IQMethod.h"

TINY_BEGIN_DECLS


typedef struct _IQResult
{
    IQMethod                    method;

    union _result
    {
        ResultGetChildren               getChildren;
        ResultGetProperties             getProperties;
        ResultSetProperties             setProperties;
        ResultInvokeAction              invokeAction;
//        ResultChildrenAdded             childrenAdded;
        ResultPropertiesChanged         propertiesChanged;
        ResultVerifyStart               verifyStart;
        ResultGetAccessKey              getAccessKey;
    } content;
} IQResult;


void IQResult_Dispose(IQResult *thiz);


TINY_END_DECLS

#endif /* __IQ_RESULT_H__  */