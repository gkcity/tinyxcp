#include <tiny_socket.h>
#include "device/definition/Lightbulb.h"
#include "CommandReader.h"
#include "task_iot.h"
#include "task_light.h"

#define SERIAL_NUMBER       "10001"
#define IP                  "10.0.1.29"

static Product *product = NULL;

void start_tasks()
{
    /**
     * 任务1： 开启一个线程运行IoT服务
     */
    task_iot_start(product);

    /**
     * 任务2： 开启一个线程运行灯光服务
     */
    task_light_start(product);
}

void stop_tasks()
{
    /**
     * 停止IoT服务
     */
    task_iot_stop();

    /**
     * 停止灯光服务
     */
    task_light_stop();
}

int main(void)
{
    tiny_socket_initialize();

    /**
     * 1. 初始化产品
     */
    product = Lightbulb(SERIAL_NUMBER, IP);
    if (product == NULL)
    {
        return 0;
    }

    /**
     * 2. 启动3个任务
     */
    start_tasks();

    /**
     * 3. 等待用户输入命令
     */
    WaitingForUserCommand();

    /**
     * 4. 停止所有任务
     */
    stop_tasks();

    /**
     * 5. 删除产品定义，准备退出
     */
    Product_Delete(product);

    tiny_socket_finalize();

    return 0;
}

