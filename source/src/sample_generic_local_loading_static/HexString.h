/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   HexString.h
*
* @remark
*
*/

#ifndef __HexString_H__
#define __HexString_H__

#include <tiny_base.h>
#include <JsonValue.h>

TINY_BEGIN_DECLS


uint32_t decodeHex(JsonString *string, uint8_t bytes[], uint32_t length);

JsonValue * encodeHex(uint8_t bytes[], uint32_t length);


TINY_END_DECLS

#endif /* __HexString_H__ */