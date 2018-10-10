/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ByebyeFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ByebyeFactory_H__
#define __ByebyeFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
XcpMessage * QueryByebye_New(const char *id);

TINY_LOR
XcpMessage * ResultByebye_New(const char *id);



TINY_END_DECLS

#endif /* __ByebyeFactory_H__  */
