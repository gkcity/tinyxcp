/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceInitializer.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_INITIALIZER_H__
#define __DEVICE_INITIALIZER_H__

#include <device/Device.h>

TINY_BEGIN_DECLS


/**
 * 初始化设备并设置回调函数
 * 参数:
 *      did: 设备ID
 *      productId: 产品ID
 *      productVersion: 产品版本
 *      ltsk: 设备私钥
 *      ltpk: 设备公钥
 *      onGet: 读属性的回调函数
 *      onSet: 写属性的回调函数
 *      onInvoke: 方法执行的回调函数
 */
Device *DeviceInitialize(const char *did,
                         uint16_t productId,
                         uint16_t productVersion,
                         const char *ltsk,
                         const char *ltpk,
                         PropertyOnGet onGet,
                         PropertyOnSet onSet,
                         ActionOnInvoke onInvoke);


TINY_END_DECLS


#endif /* __DEVICE_INITIALIZER_H__ */
