/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetChildrenCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __GetChildrenCodec_H__
#define __GetChildrenCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/GetChildren.h>

TINY_BEGIN_DECLS



TINY_LOR
TinyRet GetChildrenCodec_EncodeResult(JsonObject *content, ResultGetChildren *getChildren);



TINY_END_DECLS

#endif /* __GetChildrenCodec_H__  */
