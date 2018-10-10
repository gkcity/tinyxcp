/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQQuery.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_QUERY_H__
#define __IQ_QUERY_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <TinyList.h>
#include <iq/basic/ChildrenAdded.h>
#include <iq/basic/ChildrenRemoved.h>
#include <iq/basic/Initialize.h>
#include <iq/basic/EventOccurred.h>
#include <iq/basic/PropertiesChanged.h>
#include <iq/basic/SetAccessKey.h>
#include <iq/basic/VerifyFinish.h>
#include <iq/basic/VerifyStart.h>
#include <iq/basic/GetProperties.h>
#include <iq/basic/SetProperties.h>
#include <iq/basic/InvokeAction.h>

#include "IQMethod.h"

TINY_BEGIN_DECLS


typedef struct _IQQuery
{
    IQMethod method;

    union _query
    {
        QueryChildrenAdded              childrenAdded;
        QueryChildrenRemoved            childrenRemoved;
        QueryInitialize                 initialize;
        QueryEventOccurred              eventOccurred;
        QueryPropertiesChanged          propertiesChanged;
        QuerySetAccessKey               setAccessKey;
        QueryVerifyFinish               verifyFinish;
        QueryVerifyStart                verifyStart;
        QueryGetProperties              getProperties;
        QuerySetProperties              setProperties;
        QueryInvokeAction               invokeAction;
    } content;
} IQQuery;


void IQQuery_Dispose(IQQuery *thiz);


TINY_END_DECLS

#endif /* __IQ_QUERY_H__  */