/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InvokeAction.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include "InvokeAction.h"

TinyRet QueryInvokeAction_Construct(QueryInvokeAction *thiz)
{
    return ActionOperation_Construct(&thiz->operation);
}

void QueryInvokeAction_Dispose(QueryInvokeAction *thiz)
{
    ActionOperation_Dispose(&thiz->operation);
}

TinyRet ResultInvokeAction_Construct(ResultInvokeAction *thiz)
{
    return ActionOperation_Construct(&thiz->operation);
}

void ResultInvokeAction_Dispose(ResultInvokeAction *thiz)
{
    ActionOperation_Dispose(&thiz->operation);
}