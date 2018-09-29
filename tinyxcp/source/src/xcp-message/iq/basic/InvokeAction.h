/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InvokeAction.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __InvokeAction_H__
#define __InvokeAction_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/ActionOperation.h>

TINY_BEGIN_DECLS


typedef struct _QueryInvokeAction
{
    ActionOperation      operation;
} QueryInvokeAction;

typedef struct _ResultInvokeAction
{
    ActionOperation      operation;
} ResultInvokeAction;



TINY_END_DECLS

#endif /* __InvokeAction_H__  */
