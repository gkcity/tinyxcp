/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   HexString.c
*
* @remark
*
*/

#include <value/JsonString.h>
#include "HexString.h"

uint32_t decodeHex(JsonString *string, uint8_t bytes[], uint32_t length)
{
    uint32_t size = string->length / 2;

    if (size > length)
    {
        return 0;
    }

    for (uint32_t i = 0; i < size; i ++)
    {
        char value[4];
        char *stop = NULL;
        uint8_t byte = 0;

        memset(value, 0, 4);

        value[0] = string->value[(i * 2)];
        value[1] = string->value[(i * 2) + 1];

        byte = (uint8_t) strtol(value, &stop, 16);

        bytes[i] = byte;
    }

    return size;
}

JsonValue * encodeHex(uint8_t bytes[], uint32_t length)
{
    char value[1024];

    memset(value, 0, 1024);

    for (uint32_t i = 0; i < length; ++i)
    {
        char v[16];

        memset(v, 0, 16);
        snprintf(v, 16, "%02X", bytes[i]);

        value[i * 2] = v[0];
        value[i * 2 + 1] = v[1];
    }

    return JsonValue_NewString(value);
}