/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   DeviceCreator.c
*
* @remark
*
*/

#include "DeviceCreator.h"
#include <DeviceFactory.h>
#include <tiny_log.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <tiny_snprintf.h>

#define TAG "DeviceCreator"

Device* Device_CreateFromFile(const char *name)
{
    Device *device = NULL;
    JsonObject *object = NULL;
    int fd = 0;

    do
    {
        char buffer[1024 * 10];
        ssize_t size = 0;

        fd = open(name, O_RDONLY);
        if (fd <= 0)
        {
            LOG_E(TAG, "open: %s", name);
            perror(strerror(errno));
            break;
        }

        LOG_D(TAG, "%s opened", name);
        memset(buffer, 0, 1024 * 10);

        size = read(fd, buffer, 1024 * 10);
        if (size <= 0)
        {
            LOG_E(TAG, "read: %ld", size);
            perror(strerror(errno));
            break;
        }

        object = JsonObject_NewString(buffer);
        if (object == NULL)
        {
            LOG_E(TAG, "JsonObject_NewString");
        }

        device = Device_NewInstance(object);
    } while (false);

    if (object != NULL)
    {
        JsonObject_Delete(object);
    }

    LOG_I(TAG, "Device_CreateFrom finished!");

    return device;
}

Device* Device_CreateFrom(const char *did, uint16_t productId, uint16_t productVersion, const char *ltsk, const char *file)
{
    Device* device = Device_CreateFromFile(file);
    if (device != NULL)
    {
        strncpy(device->ltsk, ltsk, DEVICE_LTSK_LENGTH);
        tiny_snprintf(device->did, DEVICE_ID_LENGTH, "%s@%d", did, productId);
        device->productId = productId;
        device->productVersion = productVersion;
    }

    return device;
}
