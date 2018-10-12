/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HandleEventOccurred.h
 *
 * @remark
 *
 */

#ifndef __HandleEventOccurred_H__
#define __HandleEventOccurred_H__

#include <tiny_base.h>
#include <channel/Channel.h>
#include <IotRuntime.h>
#include <codec-http/HttpContent.h>

TINY_BEGIN_DECLS


void HandleEventOccurred(Channel *channel, HttpContent *content, IotRuntime *runtime);


TINY_END_DECLS

#endif /* __HandleEventOccurred_H__ */
