/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   CommonHandler.h
 *
 * @remark
 *
 */

#ifndef __CommonHandler_H__
#define __CommonHandler_H__

#include <tiny_base.h>
#include <channel/Channel.h>
#include <JsonObject.h>
#include <iq/IQError.h>

TINY_BEGIN_DECLS


void sendResponse(Channel *channel, int code, const char *status);

void sendJsonObject(Channel *channel, int code, const char *reason, JsonObject *object);

void sendError(Channel *channel, IQError *error);


TINY_END_DECLS

#endif /* __CommonHandler_H__ */
