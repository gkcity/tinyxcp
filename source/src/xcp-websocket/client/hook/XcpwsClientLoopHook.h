/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsClientLoopHook.h
 *
 * @remark
 *
 */

#ifndef __XCP_WS_CLIENT_LOOP_HOOK_H__
#define __XCP_WS_CLIENT_LOOP_HOOK_H__

#include <channel/Channel.h>

TINY_BEGIN_DECLS


void XcpwsClientLoopHook(Channel *thiz, void *ctx);


TINY_END_DECLS

#endif /* __XCP_WS_CLIENT_LOOP_HOOK_H__ */