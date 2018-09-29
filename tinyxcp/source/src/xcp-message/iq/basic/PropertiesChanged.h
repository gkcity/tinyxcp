/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertiesChanged.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __PropertiesChanged_H__
#define __PropertiesChanged_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/PropertyOperations.h>

TINY_BEGIN_DECLS


/**
 * Query
 */
typedef struct _QueryPropertiesChanged
{
    PropertyOperations      properties;
} QueryPropertiesChanged;

TINY_LOR
TinyRet QueryPropertiesChanged_Construct(QueryPropertiesChanged *thiz);

TINY_LOR
void QueryPropertiesChanged_Dispose(QueryPropertiesChanged *thiz);

/**
 * Result
 */
typedef struct _ResultPropertiesChanged
{
    PropertyOperations      properties;
} ResultPropertiesChanged;

TINY_LOR
TinyRet ResultPropertiesChanged_Construct(ResultPropertiesChanged *thiz);

TINY_LOR
void ResultPropertiesChanged_Dispose(ResultPropertiesChanged *thiz);


TINY_END_DECLS

#endif /* __PropertiesChanged_H__  */
