/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   IotService.h
*
* @remark
*
*/

#ifndef __IotService_H__
#define __IotService_H__

#include <product/Product.h>
#include <XcpwsClientRuntime.h>

TINY_BEGIN_DECLS


/**
 * 运行IoT服务：连接到服务器，等待控制指令并执行。
 */
void IotService_Run(Product *product);

/**
 * 停止IoT服务：断开与服务器的连接。
 */
void IotService_Stop(void);

/**
 * 读取AccessKey
 */
void IotService_GetAccessKey(XcpMessageHandler handler, void *ctx);

/**
 * 重置AccessKey
 */
void IotService_ResetAccessKey(const char *key, XcpMessageHandler handler, void *ctx);


TINY_END_DECLS

#endif /* __IotService_H__ */