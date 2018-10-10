/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   GetAccessKeyHandler.h
 *
 * @remark
 *
 */

#ifndef __GetAccessKeyHandler_H__
#define __GetAccessKeyHandler_H__

#include <tiny_base.h>
#include <channel/Channel.h>
#include <IotRuntime.h>

TINY_BEGIN_DECLS


void onGetAccessKey(Channel *channel, IotRuntime *runtime);


TINY_END_DECLS

#endif /* __GetAccessKeyHandler_H__ */
