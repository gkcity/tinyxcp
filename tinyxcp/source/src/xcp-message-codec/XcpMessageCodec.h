/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   XcpMessageCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __XCP_MESSAGE_CODEC_H__
#define __XCP_MESSAGE_CODEC_H__

#include <tiny_base.h>
#include <JsonObject.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
JsonObject* XcpMessageCodec_Encode(XcpMessage *message);

TINY_LOR
XcpMessage* XcpMessageCodec_Decode(JsonObject *object);


TINY_END_DECLS

#endif /* __XCP_MESSAGE_CODEC_H__  */