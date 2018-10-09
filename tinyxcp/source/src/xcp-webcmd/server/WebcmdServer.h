/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WebcmdServer.h
 *
 * @remark
 *
 */

#ifndef __WEBCMD_SERVER_H__
#define __WEBCMD_SERVER_H__

#include <channel/Channel.h>
#include <IotRuntime.h>

TINY_BEGIN_DECLS


#define XCMD_MAX_CONNECTIONS         10
#define XCMD_CONNECTION_TIMEOUT      60

TINY_LOR
Channel * WebcmdServer_New(IotRuntime *runtime);



TINY_END_DECLS

#endif /* __WEBCMD_SERVER_H__ */
