/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebcmdServerHandler.h
 *
 * @remark
 *
 */


#ifndef __XCMD_SERVER_HANDLER_H__
#define __XCMD_SERVER_HANDLER_H__

#include <tiny_base.h>
#include <channel/ChannelHandler.h>
#include <IotRuntime.h>

TINY_BEGIN_DECLS


#define WebcmdServerHandler_Name  "WebcmdServerHandler"

TINY_LOR
ChannelHandler * WebcmdServerHandler(IotRuntime *runtime);


TINY_END_DECLS

#endif /* __XCMD_SERVER_HANDLER_H__ */