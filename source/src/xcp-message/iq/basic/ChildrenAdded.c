/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ChildrenAdded.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "ChildrenAdded.h"


TINY_LOR
TinyRet QueryChildrenAdded_Construct(QueryChildrenAdded *thiz)
{
    return TinyList_Construct(&thiz->children, NULL, NULL);
}

TINY_LOR
void QueryChildrenAdded_Dispose(QueryChildrenAdded *thiz)
{
    TinyList_Dispose(&thiz->children);
}
