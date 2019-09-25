/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerLoopHook.h
 *
 * @remark
 *
 */

#ifndef __XCP_WS_SERVER_LOOP_HOOK_H__
#define __XCP_WS_SERVER_LOOP_HOOK_H__

#include <channel/Channel.h>

TINY_BEGIN_DECLS


void XcpwsServerLoopHook(Channel *thiz, void *ctx);


TINY_END_DECLS

#endif /* __XCP_WS_SERVER_LOOP_HOOK_H__ */