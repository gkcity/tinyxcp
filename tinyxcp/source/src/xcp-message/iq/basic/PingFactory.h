/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PingFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __PingFactory_H__
#define __PingFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS



TINY_LOR
XcpMessage * Ping_New(const char *id);



TINY_END_DECLS

#endif /* __PingFactory_H__  */
