/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   FanController.c
*
* @remark
*
*/

#include "FanController.h"


#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <memory.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define GPIO_EXPORT         "/sys/class/gpio/export"
#define GPIO_UNEXPORT       "/sys/class/gpio/unexport"
#define GPIO_PIN            "/sys/class/gpio/gpio%d/value"

#if 0
static int gpio_export(int pin)
{
    char value[64];
    int fd = 0;
    ssize_t ret = 0;

    printf("exporting pin: %d\n", pin);

    fd = open(GPIO_EXPORT, O_WRONLY);
    if (fd < 0)
    {
        printf("open file failed: %d %s\n", fd, GPIO_EXPORT);
        printf("errno: %d\n", errno);
	perror("gpio_export open");
        return fd;
    }

    memset(value, 0, 64);
    snprintf(value, 64, "%d", pin);

    ret = write(fd, value, strlen(value));
    if (ret < 0)
    {
        printf("write failed: %ld\n", ret);
        printf("errno: %d\n", errno);
	perror("gpio_export write");
        return -1;
    }

    close(fd);

    return 0;
}

static int gpio_unexport(int pin)
{
    char value[64];
    int fd = 0;
    ssize_t ret = 0;

    printf("unexporting pin: %d\n", pin);

    fd = open(GPIO_UNEXPORT, O_WRONLY);
    if (fd < 0)
    {
        printf("open file failed: %d %s\n", fd, GPIO_UNEXPORT);
        printf("errno: %d\n", errno);
	perror("gpio_unexport open");
        return fd;
    }

    memset(value, 0, 64);
    snprintf(value, 64, "%d", pin);

    ret = write(fd, value, strlen(value));
    if (ret < 0)
    {
        printf("write failed: %ld\n", ret);
        printf("errno: %d\n", errno);
	perror("gpio_unexport write");
        return fd;
        return -1;
    }

    close(fd);

    return 0;
}

static int gpio_set(int pin, int value)
{
    char string[64];
    char file[128];
    int fd = 0;
    ssize_t ret = 0;

    printf("gpio_set %d = %d\n", pin, value);

    memset(file, 0, 128);
    snprintf(file, 128, GPIO_PIN, pin);

    fd = open(file, O_WRONLY);
    if (fd < 0)
    {
        printf("open file failed: %d %s\n", fd, file);
        printf("errno: %d\n", errno);
	perror("gpio_set open");
        return fd;
    }

    memset(string, 0, 64);
    snprintf(string, 64, "%d", value);

    ret = write(fd, string, strlen(string));
    if (ret < 0)
    {
        printf("write failed: %ld\n", ret);
        printf("errno: %d\n", errno);
	perror("gpio_set write");
        return -1;
    }

    close(fd);

    return 0;
}
#else
static int gpio_export(int pin)
{
    char value[64];
    FILE *fp = NULL;
    ssize_t ret = 0;

    printf("exporting pin: %d\n", pin);

    fp = fopen(GPIO_EXPORT, "w");
    if (fp == 0)
    {
        printf("open file failed: %s\n", GPIO_EXPORT);
        printf("errno: %d\n", errno);
        perror("gpio_export open");
        return -1;
    }

    memset(value, 0, 64);
    snprintf(value, 64, "%d", pin);

    ret = fwrite(value, strlen(value), 1, fp);
    if (ret <= 0)
    {
        printf("write failed: %ld\n", ret);
        printf("errno: %d\n", errno);
        perror("gpio_export write");
        return -2;
    }

    fclose(fp);

    return 0;
}

static int gpio_unexport(int pin)
{
    char value[64];
    FILE *fp = 0;
    ssize_t ret = 0;

    printf("unexporting pin: %d\n", pin);

    fp = fopen(GPIO_UNEXPORT, "w");
    if (fp == NULL)
    {
        printf("open file failed: %s\n", GPIO_UNEXPORT);
        printf("errno: %d\n", errno);
        perror("gpio_unexport open");
        return -1;
    }

    memset(value, 0, 64);
    snprintf(value, 64, "%d", pin);

    ret = fwrite(value, strlen(value), 1, fp);
    if (ret <= 0)
    {
        printf("write failed: %ld\n", ret);
        printf("errno: %d\n", errno);
        perror("gpio_unexport write");
        return -2;
    }

    fclose(fp);

    return 0;
}

static int gpio_set(int pin, int value)
{
    char string[64];
    char file[128];
    FILE *fp = NULL;
    ssize_t ret = 0;

    printf("gpio_set %d = %d\n", pin, value);

    memset(file, 0, 128);
    snprintf(file, 128, GPIO_PIN, pin);

    fp = fopen(file, "w");
    if (fp == NULL)
    {
        printf("open file failed: %s\n", file);
        printf("errno: %d\n", errno);
        perror("gpio_set open");
        return -1;
    }

    memset(string, 0, 64);
    snprintf(string, 64, "%d", value);

    ret = fwrite(string, strlen(string), 1, fp);
    if (ret < 0)
    {
        printf("write failed: %ld\n", ret);
        printf("errno: %d\n", errno);
        perror("gpio_set write");
        return -2;
    }

    fclose(fp);

    return 0;
}

#endif


static bool OnOff = false;

void fan_set_on(bool on)
{
    int ret = 0;
    int pin = 251;
    int value = on ? 1 : 0;

    do
    {
        ret = gpio_export(pin);
        if (ret != 0)
        {
            break;
        }

        ret = gpio_set(pin, value);
        if (ret != 0)
        {
            break;
        }

        ret = gpio_unexport(pin);
        if (ret != 0)
        {
            break;
        }

        OnOff = on;
    } while (false);
}

bool fan_get_on(void)
{
    return OnOff;
}