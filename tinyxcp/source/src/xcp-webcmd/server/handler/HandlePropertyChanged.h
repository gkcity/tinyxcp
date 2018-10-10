/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HandlePropertyChanged.h
 *
 * @remark
 *
 */

#ifndef __HandlePropertyChanged_H__
#define __HandlePropertyChanged_H__

#include <tiny_base.h>
#include <channel/Channel.h>
#include <IotRuntime.h>
#include <codec-http/HttpContent.h>

TINY_BEGIN_DECLS


void HandlePropertyChanged(Channel *channel, HttpContent *content, IotRuntime *runtime);


TINY_END_DECLS

#endif /* __HandlePropertyChanged_H__ */
