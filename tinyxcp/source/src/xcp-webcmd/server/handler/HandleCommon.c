/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   CommonHandler.c
 *
 * @remark
 *
 */

#include <codec-http/HttpMessage.h>
#include <channel/SocketChannel.h>
#include "CommonHandler.h"

void sendResponse(Channel *channel, int code, const char *status)
{
    HttpMessage *response = HttpMessage_New();
    if (response != NULL)
    {
        HttpMessage_SetResponse(response, 404, "NOT FOUND");
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpHeader_SetInteger(&response->header, "Content-Length", 0);
        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, response, 0);
        HttpMessage_Delete(response);
    }
}

void sendJsonObject(Channel *channel, int code, const char *reason, JsonObject *object)
{
    do
    {
        if (RET_FAILED(JsonObject_Encode(object, true)))
        {
            break;
        }

        HttpMessage *response = HttpMessage_New();
        if (response == NULL)
        {
            break;
        }

        HttpMessage_SetResponse(response, code, reason);
        HttpMessage_SetProtocolIdentifier(response, "HTTP");
        HttpMessage_SetVersion(response, 1, 1);
        HttpMessage_SetContent(response, "application/json; charset=utf-8", object->size, (const uint8_t *)object->string);

        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, response, 0);
        HttpMessage_Delete(response);
    } while (false);
}

void sendError(Channel *channel, IQError *error)
{
    do
    {
        JsonObject *o = JsonObject_New();
        if (o == NULL)
        {
            break;
        }

        JsonObject_PutInteger(o, "status", error->status);
        JsonObject_PutString(o, "description", error->description);

        sendJsonObject(channel, 400, "ERROR", o);

        JsonObject_Delete(o);
    } while (false);
}