/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   IQErrorFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IQ_ERROR_FACTORY_H__
#define __IQ_ERROR_FACTORY_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
XcpMessage * IQError_New(const char *id, int32_t status, const char *description);


TINY_END_DECLS

#endif /* __IQ_ERROR_FACTORY_H__  */