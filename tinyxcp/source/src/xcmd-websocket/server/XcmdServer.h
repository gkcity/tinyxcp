/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcmdServer.h
 *
 * @remark
 *
 */

#ifndef __XCMD_SERVER_H__
#define __XCMD_SERVER_H__

#include <channel/Channel.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


#define XCMD_MAX_CONNECTIONS         10
#define XCMD_CONNECTION_TIMEOUT      60

TINY_LOR
Channel * XcmdServer_New(void);



TINY_END_DECLS

#endif /* __XCMD_SERVER_H__ */
