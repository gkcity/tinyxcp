/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetProperties.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "SetProperties.h"

TinyRet QuerySetProperties_Construct(QuerySetProperties *thiz)
{
    return PropertyOperations_Construct(&thiz->properties);
}

void QuerySetProperties_Dispose(QuerySetProperties *thiz)
{
    PropertyOperations_Dispose(&thiz->properties);
}

TinyRet ResultSetProperties_Construct(ResultSetProperties *thiz)
{
    return PropertyOperations_Construct(&thiz->properties);
}

void ResultSetProperties_Dispose(ResultSetProperties *thiz)
{
    PropertyOperations_Dispose(&thiz->properties);
}