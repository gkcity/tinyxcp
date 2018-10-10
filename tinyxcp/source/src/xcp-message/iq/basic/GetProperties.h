/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetProperties.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __GetProperties_H__
#define __GetProperties_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/PropertyOperations.h>

TINY_BEGIN_DECLS


typedef struct _QueryGetProperties
{
    PropertyOperations      operations;
} QueryGetProperties;

TinyRet QueryGetProperties_Construct(QueryGetProperties *thiz);
void QueryGetProperties_Dispose(QueryGetProperties *thiz);

typedef struct _ResultGetProperties
{
    PropertyOperations      operations;
} ResultGetProperties;

TinyRet ResultGetProperties_Construct(ResultGetProperties *thiz);
void ResultGetProperties_Dispose(ResultGetProperties *thiz);


TINY_END_DECLS

#endif /* __GetProperties_H__  */
