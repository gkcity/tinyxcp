/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ResetAccessKeyHandler.h
 *
 * @remark
 *
 */

#ifndef __ResetAccessKeyHandler_H__
#define __ResetAccessKeyHandler_H__

#include <tiny_base.h>
#include <channel/Channel.h>
#include <IotRuntime.h>

TINY_BEGIN_DECLS


void onResetAccessKey(Channel *channel, IotRuntime *runtime);


TINY_END_DECLS

#endif /* __ResetAccessKeyHandler_H__ */
