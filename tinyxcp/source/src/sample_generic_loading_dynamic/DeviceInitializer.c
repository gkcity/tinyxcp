/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceInitializer.c
 *
 * @remark
 *
 */

#include "DeviceInitializer.h"
#include <DeviceFactory.h>
#include <tiny_log.h>

#define TAG "DeviceInitializer"

Device *DeviceInitialize(const char *did,
                         uint16_t productId,
                         uint16_t productVersion,
                         const char *ltsk,
                         PropertyOnGet onGet,
                         PropertyOnSet onSet,
                         ActionOnInvoke onInvoke)
{
    Device *device = DeviceFactory_Create(did, productId, productVersion, ltsk, 10);
    if (device == NULL)
    {
        LOG_I(TAG, "DeviceFactory_Create FAILED!\n");
        return NULL;
    }

    strncpy(device->ip, "10.0.1.29", TINY_IP_LEN);
    device->port = 9898;

    LOG_I(TAG, "DeviceFactory_Create succeed!");
    LOG_I(TAG, "did: %s", device->did);
    LOG_I(TAG, "product-id: %d", device->productId);
    LOG_I(TAG, "product-version: %d", device->productVersion);

    Device_SetHandler(device, onGet, onSet, onInvoke);

    return device;
}