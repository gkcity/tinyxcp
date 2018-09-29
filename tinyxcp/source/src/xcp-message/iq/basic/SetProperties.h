/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetProperties.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SetProperties_H__
#define __SetProperties_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/PropertyOperations.h>

TINY_BEGIN_DECLS


typedef struct _QuerySetProperties
{
    PropertyOperations      properties;
} QuerySetProperties;

typedef struct _ResultSetProperties
{
    PropertyOperations      properties;
} ResultSetProperties;



TINY_END_DECLS

#endif /* __SetProperties_H__  */
