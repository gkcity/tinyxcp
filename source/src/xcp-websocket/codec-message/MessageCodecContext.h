/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   MessageCodecContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MESSAGE_CODEC_CONTEXT_H__
#define __MESSAGE_CODEC_CONTEXT_H__

#include <tiny_base.h>
#include <channel/ChannelHandler.h>
#include <device/Thing.h>
#include <ByteBuffer.h>
#include "MessageCodecSide.h"

TINY_BEGIN_DECLS


#define MESSAGE_BUFFER_SIZE         (1024 * 2)

typedef struct _MessageCodecContext
{
    ByteBuffer                    buffer;
    Thing                       * thing;
    MessageCodecSide              side;
} MessageCodecContext;

TINY_LOR
MessageCodecContext * MessageCodecContext_New(Thing *thing, MessageCodecSide side);

TINY_LOR
void MessageCodecContext_Delete(MessageCodecContext *thiz);


TINY_END_DECLS

#endif /* __MESSAGE_CODEC_CONTEXT_H__  */