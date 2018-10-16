/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ChildrenRemoved.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "ChildrenRemoved.h"


TINY_LOR
TinyRet QueryChildrenRemoved_Construct(QueryChildrenRemoved *thiz)
{
    return TinyList_Construct(&thiz->children, NULL, NULL);
}

TINY_LOR
void QueryChildrenRemoved_Dispose(QueryChildrenRemoved *thiz)
{
    TinyList_Dispose(&thiz->children);
}
