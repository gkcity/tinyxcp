/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ChildrenAddedCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ChildrenAddedCodec_H__
#define __ChildrenAddedCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/ChildrenAdded.h>

TINY_BEGIN_DECLS



TINY_LOR
TinyRet ChildrenAddedCodec_EncodeQuery(JsonObject *root, QueryChildrenAdded *childrenAdded);



TINY_END_DECLS

#endif /* __ChildrenAddedCodec_H__  */
