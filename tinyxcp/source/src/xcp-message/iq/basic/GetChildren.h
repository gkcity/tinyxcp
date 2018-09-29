/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetChildren.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __GetChildren_H__
#define __GetChildren_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/PropertyOperations.h>

TINY_BEGIN_DECLS


/**
 * Query
 */

/**
 * Result
 */
typedef struct _ResultGetChildren
{
    TinyList                children;
} ResultGetChildren;

TINY_LOR
TinyRet ResultGetChildren_Construct(ResultGetChildren *thiz);

TINY_LOR
void ResultGetChildren_Dispose(ResultGetChildren *thiz);


TINY_END_DECLS

#endif /* __GetChildren_H__  */
