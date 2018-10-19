#include <tiny_socket.h>
#include "device/definition/ModbusMaster.h"
#include "DeviceStack.h"
#include "DeviceMonitor.h"
#include "CommandReader.h"

/**
 * 设备基本信息
 */
#define DID                 "10001@10006"
#define IP                  "10.0.1.29"

int main(void)
{
    Device *device = NULL;
    uint16_t port = 60006;

    tiny_socket_initialize();

    /**
     * 1. 初始化设备
     */
    device = ModbusMaster(DID, IP);
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

