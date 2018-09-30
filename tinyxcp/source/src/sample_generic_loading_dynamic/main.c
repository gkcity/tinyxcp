#include <tiny_log.h>
#include <tiny_socket.h>
#include <device/Property.h>
#include <device/Action.h>
#include <value/JsonString.h>
#include <value/JsonNumber.h>
#include <value/JsonBoolean.h>
#include <DeviceFactory.h>
#include <device/Service.h>
#include "handler/OnActionInvoke.h"
#include "handler/OnPropertySet.h"
#include "handler/OnPropertyGet.h"
#include "Runner.h"

#define TAG             "sample"

void tiny_print_mem(const char *tag, const char *function)
{

}

void tiny_sleep(int ms)
{

}

#define DID                 "10001"
#define PRODUCT_ID          10006
#define PRODUCT_VERSION     1
#define LTSK                "Cy/HZRcyrCK5h6OhBc6hMFXN1q0x+p8tu+bcYODkSJc="

static void Fan_On_Changed(bool value)
{
    TinyRet ret = TINY_RET_OK;
    PropertyOperation *o = PropertyOperation_New();

    strncpy(o->pid.did, DID, DEVICE_ID_LENGTH);
    o->status = 0;
    o->pid.siid = 2;
    o->pid.iid = 1;
    o->value = JsonValue_NewBoolean(value);
    if (o->value == NULL)
    {
        printf("JsonValue_NewBoolean failed");
        PropertyOperation_Delete(o);
        return;
    }

    ret = Runner_ChangePropertyValue(o);
    if (RET_FAILED(ret))
    {
        printf("Device_TryChangePropertyValue error: %d", ret);
    }

    PropertyOperation_Delete(o);
}

//static void reset(void)
//{
//    TinyRet ret = Runner_ResetAccessKey();
//    if (RET_FAILED(ret))
//    {
//        printf("Runner_Reset error: %d", ret);
//    }
//}
//
//static void get_access_key(void)
//{
//    TinyRet ret = Runner_GetAccessKey();
//    if (RET_FAILED(ret))
//    {
//        printf("Runner_GetAccessKey error: %d", ret);
//    }
//}

static TinyRet run(void)
{
    TinyRet ret = TINY_RET_OK;

    /**
     * 1. 初始化设备
     * 参数:
     *      DID: 设备ID
     *      PRODUCT_ID: 产品ID
     *      PRODUCT_VERSION: 产品版本
     *      LTSK: 设备私钥
     *      10: 超时时间
     */
    Device *device = DeviceFactory_Create(DID, PRODUCT_ID, PRODUCT_VERSION, LTSK, 10);
    if (device == NULL)
    {
        LOG_E(TAG, "DeviceFactory_Create FAILED!");
        return TINY_RET_E_INTERNAL;
    }

    strncpy(device->ip, "10.0.1.29", TINY_IP_LEN);
    device->port = 9898;

    LOG_I(TAG, "DeviceFactory_Create succeed!");
    LOG_I(TAG, "did: %s", device->did);
    LOG_I(TAG, "product-id: %d", device->productId);
    LOG_I(TAG, "product-version: %d", device->productVersion);

    /**
     * 2. 设置回调函数
     * 参数:
     *      OnPropertyGet: 读属性的回调函数
     *      OnPropertySet: 写属性的回调函数
     *      OnActionInvoke: 方法执行的回调函数
     */
    Device_SetHandler(device, OnPropertyGet, OnPropertySet, OnActionInvoke);

    /**
     * 3. 运行,　如果不出错将不会返回．
     */
    ret = Runner_Run(device);
    if (RET_FAILED(ret))
    {
        LOG_E(TAG, "Runner Finished: %d", ret);
    }

    /**
     * 4. 销毁设备
     */
    Device_Delete(device);

    return ret;
}

int main(void)
{
    tiny_socket_initialize();

    run();

    tiny_socket_finalize();
    return 0;
}
