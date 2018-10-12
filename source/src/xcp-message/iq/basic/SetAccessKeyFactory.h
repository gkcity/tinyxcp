/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetAccessKeyFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SetAccessKeyFactory_H__
#define __SetAccessKeyFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS



TINY_LOR
XcpMessage * QuerySetAccessKey_New(const char *id, const char *key);



TINY_END_DECLS

#endif /* __SetAccessKeyFactory_H__  */
