/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   ChildrenRemovedCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ChildrenRemovedCodec_H__
#define __ChildrenRemovedCodec_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <JsonObject.h>
#include <iq/basic/ChildrenRemoved.h>

TINY_BEGIN_DECLS



TINY_LOR
TinyRet ChildrenRemovedCodec_EncodeQuery(JsonObject *root, QueryChildrenRemoved *childrenRemoved);



TINY_END_DECLS

#endif /* __ChildrenRemovedCodec_H__  */
