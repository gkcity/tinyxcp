/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   XcpwsServerLoopHook.c
 *
 * @remark
 *
 */

#include <product/Product.h>
#include <tiny_log.h>
#include "XcpwsServerLoopHook.h"

#define TAG     "XcpwsServerLoopHook"

void XcpwsServerLoopHook(Channel *thiz, void *ctx)
{
    Product *product = (Product *)ctx;
    LOG_D(TAG, "XcpwsServerLoopHook: %s, TODO: check product properties changed", thiz->id);

    Product_Lock(product);

    // XcpwsClient_SendQuery();

    Product_Unlock(product);
}
