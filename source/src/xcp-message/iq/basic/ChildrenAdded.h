/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ChildrenAdded.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ChildrenAdded_H__
#define __ChildrenAdded_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <TinyList.h>

TINY_BEGIN_DECLS


/**
 * Query
 */
typedef struct _QueryChildrenAdded
{
    TinyList        children;
} QueryChildrenAdded;


TINY_LOR
TinyRet QueryChildrenAdded_Construct(QueryChildrenAdded *thiz);

TINY_LOR
void QueryChildrenAdded_Dispose(QueryChildrenAdded *thiz);

/**
 * Result
 */



TINY_END_DECLS

#endif /* __ChildrenAdded_H__  */
