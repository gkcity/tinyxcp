/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   AIDCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */


#ifndef __AID_CODEC_H__
#define __AID_CODEC_H__

#include <tiny_base.h>
#include <operation/AID.h>

TINY_BEGIN_DECLS


TINY_LOR
TinyRet AIDCodec_Decode(AID *pid, const char *string);


TINY_END_DECLS

#endif /* __AID_CODEC_H__  */