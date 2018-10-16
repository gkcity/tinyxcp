/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpKeyCreator.h
 *
 * @remark
 *
 */

#ifndef __XCP_KEY_CREATOR_H__
#define __XCP_KEY_CREATOR_H__

#include <tiny_base.h>
#include <secret/SecretKey.h>
#include <x25519/tiny_curve25519.h>
#include <hkdf/HKDF.h>

TINY_BEGIN_DECLS


typedef enum _XcpKeyType
{
    SESSION_VERIFY_ENCRYPT_KEY = 1,
    DEVICE_TO_SERVER_KEY = 2,
    SERVER_TO_DEVICE_KEY = 3,
} XcpKeyType;

TinyRet XcpKeyCreator_Create(HKDF *key, Curve25519SharedKey *sharedKey, XcpKeyType type);


TINY_END_DECLS

#endif /* __XCP_KEY_CREATOR_H__ */