/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpKeyCreator.c
 *
 * @remark
 *
 */

#include "XcpKeyCreator.h"

#define SESSION_VERIFY_START_SALT               "Session-Verify-Encrypt-Salt"
#define SESSION_VERIFY_START_SALT_LENGTH        27
#define SESSION_VERIFY_START_INFO               "Session-Verify-Encrypt-Info\001"
#define SESSION_VERIFY_START_INFO_LENGTH        28

#define SESSION_SALT                            "Session-Encryption-Salt"
#define SESSION_SALT_LENGTH                     23
#define DEVICE_TO_SERVER                        "Session-D2S-Encryption-Info\001"
#define DEVICE_TO_SERVER_LENGTH                 28
#define SERVER_TO_DEVICE                        "Session-S2D-Encryption-Info\001"
#define SERVER_TO_DEVICE_LENGTH                 28

TinyRet XcpKeyCreator_Create(HKDF *key, Curve25519SharedKey *sharedKey, XcpKeyType type)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(key, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(sharedKey, TINY_RET_E_ARG_NULL);

    switch (type)
    {
        case SESSION_VERIFY_ENCRYPT_KEY:
            HKDF_Generate(key,
                          HASH_DIGEST_SHA512,
                          (const uint8_t *) SESSION_VERIFY_START_SALT,
                          SESSION_VERIFY_START_SALT_LENGTH,
                          (const uint8_t *) SESSION_VERIFY_START_INFO,
                          SESSION_VERIFY_START_INFO_LENGTH,
                          sharedKey->value,
                          sharedKey->length);
            break;

        case DEVICE_TO_SERVER_KEY:
            HKDF_Generate(key,
                          HASH_DIGEST_SHA512,
                          (const uint8_t *) SESSION_SALT,
                          SESSION_SALT_LENGTH,
                          (const uint8_t *) DEVICE_TO_SERVER,
                          DEVICE_TO_SERVER_LENGTH,
                          sharedKey->value,
                          sharedKey->length);
            break;

        case SERVER_TO_DEVICE_KEY:
            HKDF_Generate(key,
                          HASH_DIGEST_SHA512,
                          (const uint8_t *) SESSION_SALT,
                          SESSION_SALT_LENGTH,
                          (const uint8_t *) SERVER_TO_DEVICE,
                          SERVER_TO_DEVICE_LENGTH,
                          sharedKey->value,
                          sharedKey->length);
            break;

        default:
            break;
    }

    return ret;
}