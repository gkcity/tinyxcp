/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   EventOccurredCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_snprintf.h>
#include "EventOccurredCodec.h"

TinyRet EventOccurredCodec_EncodeQuery(JsonObject *content, QueryEventOccurred *eventOccurred)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(content, TINY_RET_E_ARG_NULL);
    RETURN_VAL_IF_FAIL(eventOccurred, TINY_RET_E_ARG_NULL);

    do
    {
        EID *e = &eventOccurred->operation.eid;
        char eid[256];
        memset(eid, 0, 256);
        tiny_snprintf(eid, 256, "%s.%u.%u", e->did, e->siid, e->iid);

        ret = JsonObject_PutString(content, "eid", eid);
        if (RET_FAILED(ret))
        {
            break;
        }

        if (eventOccurred->operation.arguments == NULL)
        {
            break;
        }

        JsonArray *arguments = JsonArray_NewFrom(eventOccurred->operation.arguments);
        if (arguments == NULL)
        {
            ret = TINY_RET_E_NEW;
            break;
        }

        ret = JsonObject_PutArray(content, "arguments", arguments);
        if (RET_FAILED(ret))
        {
            JsonArray_Delete(arguments);
            break;
        }
    } while (false);

    return ret;
}