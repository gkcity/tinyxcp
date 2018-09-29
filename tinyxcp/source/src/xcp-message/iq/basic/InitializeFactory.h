/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   InitializeFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __InitializeFactory_H__
#define __InitializeFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpConstant.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
XcpMessage * QueryInitialize_New(const char *id, const char *version, const char *authentication);


TINY_END_DECLS

#endif /* __InitializeFactory_H__  */
