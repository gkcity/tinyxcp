/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   SetPropertiesFactory.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SetPropertiesFactory_H__
#define __SetPropertiesFactory_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <operation/PropertyOperations.h>
#include <XcpMessage.h>

TINY_BEGIN_DECLS


TINY_LOR
XcpMessage * ResultSetProperties_New(const char *id, PropertyOperations *properties);



TINY_END_DECLS

#endif /* __SetPropertiesFactory_H__  */
