/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InvokeActionFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __InvokeActionFactory_H__
#define __InvokeActionFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/ActionOperation.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS

TINY_LOR
XcpMessage * ResultInvokeAction_New(const char *id, ActionOperation *operation);


TINY_END_DECLS

#endif /* __InvokeActionFactory_H__  */
