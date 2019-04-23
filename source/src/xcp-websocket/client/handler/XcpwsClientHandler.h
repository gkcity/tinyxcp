/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsClientHandler.h
 *
 * @remark
 *
 */


#ifndef __XCP_WS_CLIENT_HANDLER_H__
#define __XCP_WS_CLIENT_HANDLER_H__

#include <tiny_base.h>
#include <channel/ChannelHandler.h>
#include <product/Product.h>

TINY_BEGIN_DECLS


#define XcpwsClientHandler_Name  "XcpwsClientHandler"

TINY_LOR
ChannelHandler * XcpwsClientHandler(Product *product);


TINY_END_DECLS

#endif /* __XCP_WS_CLIENT_HANDLER_H__ */