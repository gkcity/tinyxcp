/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   GetPropertiesFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __GetPropertiesFactory_H__
#define __GetPropertiesFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/PropertyOperations.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
XcpMessage * ResultGetProperties_New(const char *id, PropertyOperations *properties);


TINY_END_DECLS

#endif /* __GetPropertiesFactory_H__  */
