/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   MessageCodecSide.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MESSAGE_CODEC_SIDE_H__
#define __MESSAGE_CODEC_SIDE_H__

#include <tiny_base.h>


TINY_BEGIN_DECLS


typedef enum _MessageCodecSide
{
    MESSAGE_CODEC_CLIENT = 0,
    MESSAGE_CODEC_SERVER = 1,
} MessageCodecSide;



TINY_END_DECLS

#endif /* __MESSAGE_CODEC_SIDE_H__  */