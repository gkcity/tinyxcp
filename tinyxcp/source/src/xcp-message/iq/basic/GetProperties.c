/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetProperties.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "GetProperties.h"

TinyRet QueryGetProperties_Construct(QueryGetProperties *thiz)
{
    return PropertyOperations_Construct(&thiz->operations);
}

void QueryGetProperties_Dispose(QueryGetProperties *thiz)
{
    PropertyOperations_Dispose(&thiz->operations);
}

TinyRet ResultGetProperties_Construct(ResultGetProperties *thiz)
{
    return PropertyOperations_Construct(&thiz->operations);
}

void ResultGetProperties_Dispose(ResultGetProperties *thiz)
{
    PropertyOperations_Dispose(&thiz->operations);
}