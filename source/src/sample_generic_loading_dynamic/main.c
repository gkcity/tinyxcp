#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>  
#endif

#include <tiny_socket.h>
#include "DeviceStack.h"
#include "DeviceMonitor.h"
#include "CommandReader.h"
#include "device/definition/DeviceInitializer.h"
#include "device/handler/OnPropertyGet.h"
#include "device/handler/OnPropertySet.h"
#include "device/handler/OnActionInvoke.h"

#define DID                 "10001"
#define IP                  "10.0.1.29"

int main(void)
{
#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

    Device *device = NULL;
    uint16_t port = 60006;

    tiny_socket_initialize();

    /**
     * 1. 初始化设备
     */
    device = DeviceInitialize(DID, IP);
    if (device == NULL)
    {
        return 0;
    }

    /**
     * 2. 线程1： 启动协议栈，连接到服务器，等待控制指令并执行。
     */
    StartDeviceStack(device, &port);

    /**
     * 3. 线程2： 监控设备数据，如果发生变化，则通过ipc端口通知服务器。
     */
//    StartDeviceMonitor(device->did, port);

    /**
     * 4. 线程3: 主线程，阻塞在这里，等待用户输入命令
     */
    WaitingForUserCommand(port);

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
