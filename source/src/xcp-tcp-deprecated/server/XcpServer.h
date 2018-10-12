/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpServer.h
 *
 * @remark
 *
 */

#ifndef __XCP_SERVER_H__
#define __XCP_SERVER_H__

#include <device/Device.h>
#include <channel/Channel.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


#define XCP_MAX_CONNECTIONS         10
#define XCP_CONNECTION_TIMEOUT      60

TINY_LOR
Channel * XcpServer_New(Device *device);



TINY_END_DECLS

#endif /* __XCP_SERVER_H__ */
