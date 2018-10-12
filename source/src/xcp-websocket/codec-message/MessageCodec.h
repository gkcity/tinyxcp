/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   MessageCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MESSAGE_CODEC_H__
#define __MESSAGE_CODEC_H__

#include <tiny_base.h>
#include <channel/ChannelHandler.h>
#include <device/Device.h>
#include "MessageCodecSide.h"

TINY_BEGIN_DECLS


#define MessageCodec_Name    "MessageCodec"


TINY_LOR
ChannelHandler * MessageCodec(Device *device, MessageCodecSide side);


TINY_END_DECLS

#endif /* __MESSAGE_CODEC_H__  */