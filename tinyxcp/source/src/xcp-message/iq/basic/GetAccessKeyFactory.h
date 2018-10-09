/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetAccessKeyFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __GetAccessKeyFactory_H__
#define __GetAccessKeyFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS



TINY_LOR
XcpMessage * QueryGetAccessKey_New(const char *id);



TINY_END_DECLS

#endif /* __GetAccessKeyFactory_H__  */
