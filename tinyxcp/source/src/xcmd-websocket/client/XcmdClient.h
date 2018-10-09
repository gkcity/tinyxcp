/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdClient.h
 *
 * @remark
 *
 */

#ifndef __XCMD_CLIENT_H__
#define __XCMD_CLIENT_H__

#include <device/Device.h>
#include <channel/Channel.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
Channel * XcmdClient_New(Device *device, const char *ip, uint16_t port);


//typedef void(*XcpResultHandler) (IQ *result, void *ctx);

//TINY_LOR
//TinyRet XcmdClient_SendQuery(IQ *query, XcpResultHandler handler, void *ctx);



TINY_END_DECLS

#endif /* __XCMD_CLIENT_H__ */