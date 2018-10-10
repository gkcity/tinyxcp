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
    PropertyOperations      operations;
} QueryPropertiesChanged;

/**
 * Result
 */
typedef struct _ResultPropertiesChanged
{
    PropertyOperations      operations;
} ResultPropertiesChanged;



TINY_END_DECLS

#endif /* __PropertiesChanged_H__  */
