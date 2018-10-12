/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   PIDCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */


#ifndef __PID_CODEC_H__
#define __PID_CODEC_H__

#include <tiny_base.h>
#include <operation/PID.h>

TINY_BEGIN_DECLS


TINY_LOR
TinyRet PIDCodec_Decode(PID *pid, const char *string);


TINY_END_DECLS

#endif /* __PID_CODEC_H__  */