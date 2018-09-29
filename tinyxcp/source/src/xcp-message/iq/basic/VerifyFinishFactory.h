/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyFinishFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __VerifyFinishFactory_H__
#define __VerifyFinishFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <constant/iot_constant.h>
#include <XcpConstant.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
XcpMessage * QueryVerifyFinish_New(const char *id,
                                   const char *did,
                                   uint16_t productId,
                                   uint16_t productVersion,
                                   const char *signature,
                                   uint8_t codec);


TINY_END_DECLS

#endif /* __VerifyFinishFactory_H__  */
