/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PropertiesChanged.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "PropertiesChanged.h"

TinyRet QueryPropertiesChanged_Construct(QueryPropertiesChanged *thiz)
{
    return PropertyOperations_Construct(&thiz->operations);
}

void QueryPropertiesChanged_Dispose(QueryPropertiesChanged *thiz)
{
    PropertyOperations_Dispose(&thiz->operations);
}

TinyRet ResultPropertiesChanged_Construct(ResultPropertiesChanged *thiz)
{
    return PropertyOperations_Construct(&thiz->operations);
}

void ResultPropertiesChanged_Dispose(ResultPropertiesChanged *thiz)
{
    PropertyOperations_Dispose(&thiz->operations);
}