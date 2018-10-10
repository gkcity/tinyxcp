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

typedef struct _ResultGetProperties
{
    PropertyOperations      operations;
} ResultGetProperties;


TINY_END_DECLS

#endif /* __GetProperties_H__  */
