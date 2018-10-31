/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpClientVerifier.h
 *
 * @remark
 *
 */

#include <tiny_log.h>
#include <XcpMessage.h>
#include <tiny_malloc.h>
#include <base64/tiny_base64.h>
#include <x25519/tiny_curve25519.h>
#include <chacha20poly1305/tiny_chacha20poly1305.h>
#include <iq/basic/VerifyStartFactory.h>
#include <iq/basic/VerifyFinishFactory.h>
#include <iq/basic/InitializeFactory.h>
#include <tiny_snprintf.h>
#include "XcpClientVerifier.h"
#include "XcpKeyCreator.h"

#define TAG     "XcpClientVerifier"

TINY_LOR
static void _OnInitializeResult(XcpMessage * message, void *ctx)
{
    XcpClientVerifier *thiz = (XcpClientVerifier *)ctx;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(message);

    LOG_D(TAG, "_OnInitializeResult");

    if (message->iq.type != IQ_TYPE_RESULT)
    {
        LOG_E(TAG, "_OnInitializeResult ERROR: message not result");
        thiz->onFailure(thiz->ctx);
        return;
    }

    if (message->iq.content.result.method != IQ_METHOD_INITIALIZE)
    {
        LOG_E(TAG, "_OnInitializeResult ERROR: method invalid");
        thiz->onFailure(thiz->ctx);
        return;
    }

    if (thiz->stage != XCP_STAGE_INIT)
    {
        LOG_E(TAG, "_OnInitializeResult ERROR: stage != XCP_STAGE_INIT");
        thiz->onFailure(thiz->ctx);
        return;
    }

    thiz->stage = XCP_STAGE_INITIALIZED;

    XcpClientVerifier_VerifyStart(thiz);
}

TINY_LOR
static TinyRet _compute_shared_key(XcpClientVerifier *thiz, const char *publicKeyBase64)
{
    uint8_t buf[128];
    Curve25519PublicKey serverPubicKey;

    memset(&serverPubicKey, 0, sizeof(Curve25519PublicKey));

    serverPubicKey.length = tiny_base64_decode(publicKeyBase64, buf);
    LOG_D(TAG, "decode server public-key.length: %d", serverPubicKey.length);

    if (serverPubicKey.length != CURVE25519_PUBLIC_KEY_LENGTH)
    {
        LOG_E(TAG, "server public-key invalid, length: %d", serverPubicKey.length);
        return TINY_RET_E_ARG_INVALID;
    }
    memcpy(serverPubicKey.value, buf, CURVE25519_PUBLIC_KEY_LENGTH);

    LOG_D(TAG, "generate shared key");
    tiny_curve25519_generateSharedKey(&thiz->privateKey, &serverPubicKey, &thiz->sharedKey);

    LOG_D(TAG, "generate verify key");
    XcpKeyCreator_Create(&thiz->verifyKey, &thiz->sharedKey, SESSION_VERIFY_ENCRYPT_KEY);

    LOG_D(TAG, "generate session info");
    XcpSessionInfo_Create(&thiz->sessionInfo, &thiz->publicKey, &serverPubicKey);

    LOG_D(TAG, "compute shared key finished!");

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet _verify_signature(XcpClientVerifier *thiz, const char *signatureBase64)
{
    TinyRet ret = TINY_RET_OK;

    LOG_D(TAG, "signatureBase64: %s", signatureBase64);

    do
    {
        ED25519Signature signature;

        uint8_t data[128];
        uint32_t length = 0;

        memset(&signature, 0, sizeof(ED25519Signature));
        memset(data, 0, 128);

        length = tiny_base64_decode(signatureBase64, data);
        if (length != (ED25519_SIGNATURE_LENGTH + 16))
        {
            LOG_E(TAG, "signature invalid length: %d", length);
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        signature.length = length - 16;

        LOG_D(TAG, "tiny_chacha20poly1305_decrypt...");

        ret = tiny_chacha20poly1305_decrypt(thiz->verifyKey.value,
                                            thiz->verifyKey.length,
                                            (const uint8_t *)"SV-Msg02",
                                            data,
                                            length - 16,
                                            data + length - 16,
                                            signature.value,
                                            NULL,
                                            0);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "tiny_chacha20poly1305_decrypt signature FAILED!");
            break;
        }

        LOG_D(TAG, "tiny_chacha20poly1305_decrypt finished!");

        ret = tiny_ed25519_verify(&thiz->serverLTPK, &signature, thiz->sessionInfo.value, thiz->sessionInfo.length);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "tiny_ed25519_verify signature FAILED!");
            break;
        }

        LOG_I(TAG, "signature verified!");
    } while (false);

    return ret;
}

TINY_LOR
static void _printHex(const char *tag, const uint8_t *value, uint32_t length)
{
    printf("%s.length: %d\n", tag, length);
    for (uint32_t i = 0; i < length; ++i)
    {
        printf("\"%02x\", ", value[i]);
        if (((i+1) % 8) == 0)
        {
            printf("\n");
        }
    }
    printf("\n");
}

TINY_LOR
static void _sign(XcpClientVerifier *thiz, char signatureBase64[128])
{
    uint8_t encryptedSignature[ED25519_SIGNATURE_LENGTH + 16];
    uint32_t length = ED25519_SIGNATURE_LENGTH + 16;

    ED25519Signature signature;

    LOG_D(TAG, "_sign");

    _printHex("sessionInfo", thiz->sessionInfo.value, thiz->sessionInfo.length);
    _printHex("deviceLTSK", thiz->deviceLTSK.value, thiz->deviceLTSK.length);
    _printHex("deviceLTPK", thiz->deviceLTPK.value, thiz->deviceLTPK.length);

    memset(&signature, 0, sizeof(ED25519Signature));

    tiny_ed25519_sign(&thiz->deviceLTSK, &thiz->deviceLTPK, &signature, thiz->sessionInfo.value, thiz->sessionInfo.length);

    _printHex("signature", signature.value, signature.length);
    _printHex("verifyKey", thiz->verifyKey.value, thiz->verifyKey.length);

    tiny_chacha20poly1305_encrypt(thiz->verifyKey.value,
                                  thiz->verifyKey.length,
                                  (const uint8_t *)"SV-Msg03",
                                  signature.value,
                                  signature.length,
                                  encryptedSignature,
                                  encryptedSignature + signature.length,
                                  NULL,
                                  0);

    _printHex("encryptedSignature", encryptedSignature, length);

    memset(signatureBase64, 0, 128);
    tiny_base64_encode(encryptedSignature, length, signatureBase64);

    LOG_D(TAG, "signatureBase64: [%s]", signatureBase64);
}

TINY_LOR
static void _encode_udid(XcpClientVerifier *thiz, char udidEncryptAndBase64[256])
{
    char udid[UDID_LENGTH + 1];
    uint8_t udidEncrypt[256];
    uint32_t length = 0;

    memset(udid, 0, UDID_LENGTH + 1);
    tiny_snprintf(udid, UDID_LENGTH, "%s@%d/%d",
            thiz->device->config.serialNumber,
            thiz->device->config.productId,
            thiz->device->config.productVersion);

    LOG_D(TAG, "_encode_udid: %s", udid);

    length = (uint32_t) strlen(udid);

    tiny_chacha20poly1305_encrypt(thiz->verifyKey.value,
                                  thiz->verifyKey.length,
                                  (const uint8_t *)"SV-Msg03",
                                  (uint8_t *)udid,
                                  length,
                                  udidEncrypt,
                                  udidEncrypt + length,
                                  NULL,
                                  0);

    LOG_D(TAG, "base64");

    memset(udidEncryptAndBase64, 0, 256);
    tiny_base64_encode(udidEncrypt, length + 16, udidEncryptAndBase64);
}

//TINY_LOR
//static void _encode_type(XcpClientVerifier *thiz, char typeEncryptAndBase64[256])
//{
//    uint8_t type[200];
//    uint32_t length = 0;
//
//    LOG_D(TAG, "_encode_type");
//
//    length = (uint32_t) strlen(thiz->device->type);
//
//    tiny_chacha20poly1305_encrypt(thiz->verifyKey.value,
//                                  thiz->verifyKey.length,
//                                  "SV-Msg03",
//                                  (uint8_t *)(thiz->device->type),
//                                  length,
//                                  type,
//                                  type + length,
//                                  NULL,
//                                  0);
//
//    LOG_D(TAG, "base64");
//
//    memset(typeEncryptAndBase64, 0, 256);
//    tiny_base64_encode(type, length + 16, typeEncryptAndBase64);
//}

TINY_LOR
static void _OnVerifyStartResult(XcpMessage * message, void *ctx)
{
    XcpClientVerifier *thiz = (XcpClientVerifier *)ctx;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(message);

    LOG_D(TAG, "_OnVerifyStartResult");

    if (message->iq.type != IQ_TYPE_RESULT)
    {
        LOG_E(TAG, "_OnVerifyStartResult ERROR: message not result");
        thiz->onFailure(thiz->ctx);
        return;
    }

    if (message->iq.content.result.method != IQ_METHOD_VERIFY_START)
    {
        LOG_E(TAG, "_OnVerifyStartResult ERROR: method invalid");
        thiz->onFailure(thiz->ctx);
        return;
    }

    if (thiz->stage != XCP_STAGE_INITIALIZED)
    {
        LOG_E(TAG, "_OnVerifyStartResult ERROR: stage != XCP_STAGE_INITIALIZED");
        thiz->onFailure(thiz->ctx);
        return;
    }

    if (RET_FAILED(_compute_shared_key(thiz, message->iq.content.result.content.verifyStart.publicKey)))
    {
        LOG_E(TAG, "_OnVerifyStartResult ERROR: compute shared key failed");
        thiz->onFailure(thiz->ctx);
        return;
    }

    if (RET_FAILED(_verify_signature(thiz, message->iq.content.result.content.verifyStart.signature)))
    {
        LOG_E(TAG, "_OnVerifyStartResult ERROR: server signature verify failed");
        thiz->onFailure(thiz->ctx);
        return;
    }

    thiz->stage = XCP_STAGE_VERIFY_STARTED;

    XcpClientVerifier_VerifyFinish(thiz);
}

TINY_LOR
static void _OnVerifyFinishResult(XcpMessage * message, void *ctx)
{
    XcpClientVerifier *thiz = (XcpClientVerifier *)ctx;
    TinyRet ret = TINY_RET_OK;
    HKDF deviceToServerKey;
    HKDF serverToDeviceKey;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(message);

    LOG_D(TAG, "_OnVerifyFinishResult");

    if (message->iq.type != IQ_TYPE_RESULT)
    {
        LOG_E(TAG, "_OnVerifyFinishResult ERROR: message not result");
        thiz->onFailure(thiz->ctx);
        return;
    }

    if (message->iq.content.result.method != IQ_METHOD_VERIFY_FINISH)
    {
        LOG_E(TAG, "_OnVerifyFinishResult ERROR: method invalid");
        thiz->onFailure(thiz->ctx);
        return;
    }

    if (thiz->stage != XCP_STAGE_VERIFY_STARTED)
    {
        LOG_E(TAG, "_OnVerifyFinishResult ERROR: stage != XCP_STAGE_VERIFY_STARTED");
        thiz->onFailure(thiz->ctx);
        return;
    }

    ret = XcpKeyCreator_Create(&deviceToServerKey, &thiz->sharedKey, DEVICE_TO_SERVER_KEY);
    if (RET_FAILED(ret))
    {
        LOG_E(TAG, "XcpKeyCreator_Create FAILED!");
        thiz->onFailure(thiz->ctx);
        return;
    }

    ret = XcpKeyCreator_Create(&serverToDeviceKey, &thiz->sharedKey, SERVER_TO_DEVICE_KEY);
    if (RET_FAILED(ret))
    {
        LOG_E(TAG, "XcpKeyCreator_Create FAILED!");
        thiz->onFailure(thiz->ctx);
        return;
    }

//    _printHex("deviceToServerKey", deviceToServerKey.value, deviceToServerKey.length);
//    _printHex("serverToDeviceKey", serverToDeviceKey.value, serverToDeviceKey.length);

    thiz->stage = XCP_STAGE_VERIFY_FINISHED;
    thiz->onSuccess(&deviceToServerKey, &serverToDeviceKey, thiz->ctx);
}

TINY_LOR
static TinyRet XcpClientVerifier_Construct(XcpClientVerifier *thiz,
                                           const char *serverLTPK,
                                           Device *device,
                                           XcpSendQuery sendQuery,
                                           uint8_t binaryCodec)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(serverLTPK, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(device, TINY_RET_E_ARG_NULL);

    LOG_D(TAG, "XcpClientVerifier_Construct");

    do
    {
        uint32_t length = 0;
        uint8_t buf[128];

        memset(thiz, 0, sizeof(XcpClientVerifier));
        thiz->device = device;
        thiz->sendQuery = sendQuery;
        thiz->binaryCodec = binaryCodec;

        tiny_curve25519_generateKeyPair(&thiz->publicKey, &thiz->privateKey);

        memset(buf, 0, 128);
        length = tiny_base64_decode(serverLTPK, buf);
        if (length == ED25519_PUBLIC_KEY_LENGTH)
        {
            memcpy(thiz->serverLTPK.value, buf, ED25519_PUBLIC_KEY_LENGTH);
            thiz->serverLTPK.length = ED25519_PUBLIC_KEY_LENGTH;
        }
        else
        {
            LOG_E(TAG, "serverLTPK.length invalid: %d", length);
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        memset(buf, 0, 128);
        length = tiny_base64_decode(device->config.ltsk, buf);
        if (length <= ED25519_PRIVATE_KEY_LENGTH)
        {
            LOG_E(TAG, "deviceLTSK.length: %d", length);
            memcpy(thiz->deviceLTSK.value, buf, length);
            thiz->deviceLTSK.length = length;
        }
        else
        {
            LOG_E(TAG, "deviceLTSK.length invalid: %d", length);
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        memset(buf, 0, 128);
        length = tiny_base64_decode(device->config.ltpk, buf);
        if (length <= ED25519_PUBLIC_KEY_LENGTH)
        {
            LOG_E(TAG, "deviceLTPK.length: %d", length);
            memcpy(thiz->deviceLTPK.value, buf, length);
            thiz->deviceLTPK.length = length;
        }
        else
        {
            LOG_E(TAG, "deviceLTPK.length invalid: %d", length);
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }
    } while (false);

    return ret;
}

TINY_LOR
static void XcpClientVerifier_Dispose(XcpClientVerifier *thiz)
{
    RETURN_IF_FAIL(thiz);
}

TINY_LOR
XcpClientVerifier * XcpClientVerifier_New(const char *serverLTPK,
                                          Device *device,
                                          XcpSendQuery sendQuery,
                                          uint8_t binaryCodec)
{
    XcpClientVerifier *thiz = NULL;

    do
    {
        thiz = (XcpClientVerifier *)tiny_malloc(sizeof(XcpClientVerifier));
        if (thiz == NULL)
        {
            LOG_E(TAG, "tiny_malloc FAILED");
            break;
        }

        if (RET_FAILED(XcpClientVerifier_Construct(thiz, serverLTPK, device, sendQuery, binaryCodec)))
        {
            LOG_E(TAG, "XcpClientVerifier_Construct FAILED");
            XcpClientVerifier_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
void XcpClientVerifier_Delete(XcpClientVerifier *thiz)
{
    XcpClientVerifier_Dispose(thiz);
    tiny_free(thiz);
}

TINY_LOR
void XcpClientVerifier_Start(XcpClientVerifier *thiz,
                             XcpVerifySuccessHandler successHandler,
                             XcpVerifyFailureHandler failureHandler,
                             void *ctx)
{
    TinyRet ret = TINY_RET_OK;
    XcpMessage * message = NULL;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(successHandler);
    RETURN_IF_FAIL(failureHandler);
    RETURN_IF_FAIL(ctx);

    thiz->ctx = ctx;
    thiz->onSuccess = successHandler;
    thiz->onFailure = failureHandler;
    thiz->stage = XCP_STAGE_INIT;

    LOG_D(TAG, "Start");

    message = QueryInitialize_New("", "1.0", "product-id");
    if (message == NULL)
    {
        LOG_D(TAG, "QueryInitialize_New FAILED!");
        thiz->onFailure(thiz->ctx);
        return;
    }

    ret = thiz->sendQuery(thiz->ctx, message, _OnInitializeResult, thiz);
    if (RET_FAILED(ret))
    {
        LOG_D(TAG, "sendQuery FAILED: %d", ret);
        thiz->onFailure(thiz->ctx);
    }

    XcpMessage_Delete(message);
}

TINY_LOR
void XcpClientVerifier_VerifyStart(XcpClientVerifier *thiz)
{
    TinyRet ret = TINY_RET_OK;
    XcpMessage * message = NULL;
    char publicKeyBase64[128];

    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "VerifyStart");

    memset(publicKeyBase64, 0, 128);
    tiny_base64_encode(thiz->publicKey.value, thiz->publicKey.length, publicKeyBase64);

    message = QueryVerifyStart_New("", publicKeyBase64);
    if (message == NULL)
    {
        LOG_D(TAG, "QueryVerifyStart_New FAILED!");
        thiz->onFailure(thiz->ctx);
        return;
    }

    ret = thiz->sendQuery(thiz->ctx, message, _OnVerifyStartResult, thiz);
    if (RET_FAILED(ret))
    {
        LOG_D(TAG, "sendQuery FAILED: %d", ret);
        thiz->onFailure(thiz->ctx);
    }

    XcpMessage_Delete(message);
}

TINY_LOR
void XcpClientVerifier_VerifyFinish(XcpClientVerifier *thiz)
{
    TinyRet ret = TINY_RET_OK;
    XcpMessage * message = NULL;
    char udid[256];
    char signature[128];

    RETURN_IF_FAIL(thiz);

    LOG_D(TAG, "VerifyFinish");

    _sign(thiz, signature);

    _encode_udid(thiz, udid);

    LOG_E(TAG, "signature: %s", signature);

    message = QueryVerifyFinish_New("", udid, signature, thiz->binaryCodec);
    if (message == NULL)
    {
        LOG_D(TAG, "QueryVerifyFinish_New FAILED!");
        thiz->onFailure(thiz->ctx);
        return;
    }

    ret = thiz->sendQuery(thiz->ctx, message, _OnVerifyFinishResult, thiz);
    if (RET_FAILED(ret))
    {
        LOG_D(TAG, "sendQuery FAILED: %d", ret);
        thiz->onFailure(thiz->ctx);
    }

    XcpMessage_Delete(message);
}
