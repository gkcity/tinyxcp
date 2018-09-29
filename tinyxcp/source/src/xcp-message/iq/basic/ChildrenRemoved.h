/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ChildrenRemoved.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ChildrenRemoved_H__
#define __ChildrenRemoved_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <TinyList.h>

TINY_BEGIN_DECLS


/**
 * Query
 */
typedef struct _QueryChildrenRemoved
{
    TinyList        children;
} QueryChildrenRemoved;


TINY_LOR
TinyRet QueryChildrenRemoved_Construct(QueryChildrenRemoved *thiz);

TINY_LOR
void QueryChildrenRemoved_Dispose(QueryChildrenRemoved *thiz);

/**
 * Result
 */



TINY_END_DECLS

#endif /* __ChildrenRemoved_H__  */
