/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   VerifyStartFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __VerifyStartFactory_H__
#define __VerifyStartFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
XcpMessage * QueryVerifyStart_New(const char *id, const char * publicKey);



TINY_END_DECLS

#endif /* __VerifyStartFactory_H__  */
