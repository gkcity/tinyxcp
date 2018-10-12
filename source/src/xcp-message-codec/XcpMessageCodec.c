/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   XcpMessageCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */
#include <tiny_log.h>
#include <iq/IQCodec.h>
#include <value/JsonNumber.h>
#include "XcpMessageCodec.h"

#define TAG     "XcpMessageCodec"

TINY_LOR
JsonObject* XcpMessageCodec_Encode(XcpMessage *message)
{
    TinyRet ret = TINY_RET_OK;
    JsonObject *root = NULL;

    RETURN_VAL_IF_FAIL(message, NULL);

    do
    {
        root = JsonObject_New();
        if (root == NULL)
        {
            break;
        }

        ret = IQCodec_Encode(root, &message->iq);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "out of memory");
            JsonObject_Delete(root);
            root = NULL;
            break;
        }

    } while (false);

    return root;
}

TINY_LOR
XcpMessage* XcpMessageCodec_Decode(JsonObject *object)
{
    TinyRet ret = TINY_RET_OK;
    XcpMessage * message = NULL;

    RETURN_VAL_IF_FAIL(object, NULL);

    do
    {
        JsonObject *iq = NULL;

        message = XcpMessage_New();
        if (message == NULL)
        {
            break;
        }

        iq = JsonObject_GetObject(object, "iq");
        if (iq == NULL)
        {
            LOG_D(TAG, "invalid message, iq not found!");
            XcpMessage_Delete(message);
            message = NULL;
            break;
        }

        ret = IQCodec_Decode(&message->iq, iq);
        if (RET_FAILED(ret))
        {
            LOG_E(TAG, "IQCodec_Decode failed: %d", ret);
            XcpMessage_Delete(message);
            message = NULL;
            break;
        }
    } while (false);

    return message;
}
