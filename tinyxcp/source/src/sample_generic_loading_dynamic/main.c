#include <tiny_socket.h>
#include "DeviceStack.h"
#include "DeviceMonitor.h"
#include "CommandReader.h"
#include "DeviceInitializer.h"
#include "handler/OnPropertyGet.h"
#include "handler/OnPropertySet.h"
#include "handler/OnActionInvoke.h"

/**
 * 设备基本信息
 */
#define DID                 "10001"
#define PRODUCT_ID          10006
#define PRODUCT_VERSION     1
#define LTSK                "Cy/HZRcyrCK5h6OhBc6hMFXN1q0x+p8tu+bcYODkSJc="

int main(void)
{
    Device *device = NULL;

    tiny_socket_initialize();

    /**
     * 1. 初始化设备
     */
    device = DeviceInitialize(DID, PRODUCT_ID, PRODUCT_VERSION, LTSK, OnPropertyGet, OnPropertySet, OnActionInvoke);
    if (device == NULL)
    {
        return 0;
    }

    /**
     * 2. 线程1： 启动协议栈，连接到服务器，等待控制指令并执行。
     */
    StartDeviceStack(device);

    /**
     * 3. 线程2： 监控设备数据，如果发生变化，则通知服务器。
     */
    StartDeviceMonitor(device);

    /**
     * 4. 线程3: 主线程，阻塞在这里，等待用户输入命令
     */
    WaitingForUserCommand();

    /**
     * 5. 停止数据监控
     */
    StopDeviceMonitor();

    /**
     * 6. 停止协议栈
     */
    StopDeviceStack();

    /**
     * 7. 删除设备，准备退出
     */
    Device_Delete(device);

    tiny_socket_finalize();

    return 0;
}
