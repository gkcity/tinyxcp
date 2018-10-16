/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ModbusMaster.h
 *
 * @remark
 *
 */

#ifndef __ModbusMaster_H__
#define __ModbusMaster_H__

#include <device/Device.h>

TINY_BEGIN_DECLS


Device * ModbusMaster(const char *did,
                uint16_t productId,
                uint16_t productVersion,
                const char *ltsk,
                const char *ltpk,
                PropertyOnGet onGet,
                PropertyOnSet onSet,
                ActionOnInvoke onInvoke);


TINY_END_DECLS

#endif /* __ModbusMaster_H__ */
