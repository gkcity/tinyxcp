/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetChildren.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "GetChildren.h"

TINY_LOR
TinyRet ResultGetChildren_Construct(ResultGetChildren *thiz)
{
    return TinyList_Construct(&thiz->children);
}

TINY_LOR
void ResultGetChildren_Dispose(ResultGetChildren *thiz)
{
    TinyList_Dispose(&thiz->children);
}
