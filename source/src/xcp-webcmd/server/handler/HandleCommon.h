/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HandleCommon.h
 *
 * @remark
 *
 */

#ifndef __HandleCommon_H__
#define __HandleCommon_H__

#include <tiny_base.h>
#include <channel/Channel.h>
#include <JsonObject.h>
#include <iq/IQError.h>

TINY_BEGIN_DECLS


void sendResponse(Channel *channel, int code, const char *reason);

void sendTextResponse(Channel *channel, int code, const char *reason, const char *text);

void sendJsonResponse(Channel *channel, int code, const char *reason, JsonObject *object);

void sendError(Channel *channel, IQError *error);


TINY_END_DECLS

#endif /* __HandleCommon_H__ */
