/**
 * Copyright (C) 2017-2020
 *
 * @author jxfengzi@gmail.com
 * @date   2017-7-1
 *
 * @file   AIDCodec.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_str_split.h>
#include "AIDCodec.h"

TINY_LOR
TinyRet AIDCodec_Decode(AID *pid, const char *string)
{
    TinyRet ret = TINY_RET_OK;
    int32_t count = 0;
    char group[3][128];
    char *p = NULL;

    do
    {
        memset(group, 0, 3 * 128);

        count = tiny_str_split(string, ".", group, 3);
        if (count != 3)
        {
            ret = TINY_RET_E_ARG_INVALID;
            break;
        }

        strncpy(pid->did, group[0], IOT_DEVICE_ID_LENGTH);
        pid->siid = (uint16_t) strtol(group[1], &p, 10);
        pid->iid = (uint16_t) strtol(group[2], &p, 10);
    } while (false);

    return ret;
}