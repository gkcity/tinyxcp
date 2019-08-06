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
#include <ProductFactory.h>
#include <tiny_log.h>
#include "../handler/OnPropertyGet.h"
#include "../handler/OnPropertySet.h"
#include "../handler/OnActionInvoke.h"
#include "../initializer/InitializeConfiguration.h"

#define TAG "DeviceInitializer"

Product *DeviceInitialize(const char *serialNumber, const char *ip)
{
    Product *thiz = NULL;

    do
    {
        thiz = ProductFactory_Create(PRODUCT_ID, PRODUCT_VERSION, 10);
        if (thiz == NULL)
        {
            LOG_I(TAG, "DeviceFactory_Create FAILED!\n");
            return NULL;
        }

        thiz->onGet = OnPropertyGet;
        thiz->onSet = OnPropertySet;
        thiz->onInvoke = OnActionInvoke;

        InitializeConfiguration(&thiz->config, serialNumber, ip);
    } while (false);

    return thiz;
}