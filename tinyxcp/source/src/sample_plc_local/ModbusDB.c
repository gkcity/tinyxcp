/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   ModbusDB.c
*
* @remark
*
*/

#include <dirent.h>
#include <tiny_str_equal.h>
#include <JsonArray.h>
#include <tiny_log.h>
#include <StringArray.h>
#include <tiny_snprintf.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ModbusDB.h"

#define TAG "ModbusDB"

JsonObject * ModbusDB_GetDevices(void)
{
    JsonObject *object = NULL;
    DIR *dir = NULL;

    do
    {
        JsonArray *array = NULL;

        object = JsonObject_New();
        if (object == NULL)
        {
            LOG_E(TAG, "JsonObject_New");
            break;
        }

        array = JsonArray_New();
        if (array == NULL)
        {
            LOG_E(TAG, "JsonArray_New");
            break;
        }

        if (RET_FAILED(JsonObject_PutArray(object, "devices", array)))
        {
            LOG_E(TAG, "JsonObject_PutArray");
            JsonArray_Delete(array);
            break;
        }

        dir = opendir("./db/modbus/devices");
        if (dir == NULL)
        {
            LOG_E(TAG, "opendir");
            break;
        }

        while (true)
        {
            struct dirent *ent = readdir(dir);
            if (ent == NULL)
            {
                LOG_E(TAG, "readdir");
                break;
            }

            if (ent->d_type != 8)
            {
                continue;
            }

            if (str_equal(ent->d_name, ".", false) || str_equal(ent->d_name, "..", false))
            {
                continue;
            }

            StringArray *a = StringArray_NewString(ent->d_name, ".");

            do
            {
                if (a == NULL)
                {
                    LOG_E(TAG, "StringArray_NewString");
                    break;
                }

                if (a->values.size != 2)
                {
                    break;
                }

                const char *name = TinyList_GetAt(&a->values, 0);
                const char *ext = TinyList_GetAt(&a->values, 1);
                if (! str_equal(ext, "json", true))
                {
                    break;
                }

                if (RET_FAILED(JsonArray_AddString(array, name)))
                {
                    LOG_E(TAG, "JsonArray_AddString");
                    break;
                }
            } while (false);

            if (a != NULL)
            {
                StringArray_Delete(a);
            }
        }
    } while (false);

    if (dir != NULL)
    {
        closedir(dir);
    }

    return object;
}

JsonObject * ModbusDB_GetDevice(const char *id)
{
    JsonObject *object = NULL;
    int fd = 0;
    char name[256];

    do
    {
        char buffer[1024 * 4];
        ssize_t size = 0;

        memset(name, 0, 256);
        tiny_snprintf(name, 255, "./db/modbus/devices/%s.json", id);

        fd = open(name, O_RDONLY);
        if (fd <= 0)
        {
            LOG_E(TAG, "open: %s", name);
            perror(strerror(errno));
            break;
        }

        LOG_D(TAG, "%s opened", name);
        memset(buffer, 0, 1024 * 4);

        size = read(fd, buffer, 1024 * 4);
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
    } while (false);

    if (fd > 0)
    {
        close(fd);
    }

    return object;
}

int EmptyDir(char *destDir)
{

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(destDir)) == NULL)
    {
        fprintf(stderr, "cannot open directory: %s\n", destDir);
        return -1;
    }
    chdir (destDir);
    while ((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if (S_ISREG(statbuf.st_mode))
        {
            remove(entry->d_name);
        }
    }

    return 0;
}

bool ModbusDB_DeleteDevice(const char *id)
{
    int ret = 0;
    char name[512];

    memset(name, 0, 512);
    tiny_snprintf(name, 255, "./db/modbus/devices/%s.json", id);

    ret = remove(name);
    if (ret != 0)
    {
        LOG_E(TAG, "remove: %s", name);
        perror(strerror(errno));
    }

    return (ret == 0);
}

bool ModbusDB_SaveDevice(const char *id, const char *buf)
{
    bool ret = false;
    int fd = 0;
    char name[256];

    do
    {
        memset(name, 0, 256);
        tiny_snprintf(name, 255, "./db/modbus/devices/%s.json", id);

        fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd <= 0)
        {
            LOG_E(TAG, "open: %s", name);
            perror(strerror(errno));
            break;
        }

        LOG_D(TAG, "%s opened", name);

        ssize_t size = write(fd, buf, strlen(buf));
        if (size <= 0)
        {
            LOG_E(TAG, "write: %ld", size);
            perror(strerror(errno));
            break;
        }

        ret = true;
    } while (false);

    if (fd > 0)
    {
        close(fd);
    }

    return ret;
}

JsonObject * ModbusDB_GetDefinitions(void)
{
    JsonObject *object = NULL;
    DIR *dir = NULL;

    do
    {
        JsonArray *array = NULL;

        object = JsonObject_New();
        if (object == NULL)
        {
            LOG_E(TAG, "JsonObject_New");
            break;
        }

        array = JsonArray_New();
        if (array == NULL)
        {
            LOG_E(TAG, "JsonArray_New");
            break;
        }

        if (RET_FAILED(JsonObject_PutArray(object, "definitions", array)))
        {
            LOG_E(TAG, "JsonObject_PutArray");
            JsonArray_Delete(array);
            break;
        }

        dir = opendir("./db/modbus/definitions");
        if (dir == NULL)
        {
            LOG_E(TAG, "opendir");
            break;
        }

        while (true)
        {
            struct dirent *ent = readdir(dir);
            if (ent == NULL)
            {
                LOG_E(TAG, "readdir");
                break;
            }

            if (ent->d_type != 8)
            {
                continue;
            }

            if (str_equal(ent->d_name, ".", false) || str_equal(ent->d_name, "..", false))
            {
                continue;
            }

            StringArray *a = StringArray_NewString(ent->d_name, ".");

            do
            {
                if (a == NULL)
                {
                    LOG_E(TAG, "StringArray_NewString");
                    break;
                }

                if (a->values.size != 2)
                {
                    break;
                }

                const char *name = TinyList_GetAt(&a->values, 0);
                const char *ext = TinyList_GetAt(&a->values, 1);
                if (! str_equal(ext, "json", true))
                {
                    break;
                }

                if (RET_FAILED(JsonArray_AddString(array, name)))
                {
                    LOG_E(TAG, "JsonArray_AddString");
                    break;
                }
            } while (false);

            if (a != NULL)
            {
                StringArray_Delete(a);
            }
        }
    } while (false);

    if (dir != NULL)
    {
        closedir(dir);
    }

    return object;
}

JsonObject * ModbusDB_GetDefinition(const char *id)
{
    JsonObject *object = NULL;
    int fd = 0;
    char name[256];

    do
    {
        char buffer[1024 * 4];
        ssize_t size = 0;

        memset(name, 0, 256);
        tiny_snprintf(name, 255, "./db/modbus/definitions/%s.json", id);

        fd = open(name, O_RDONLY);
        if (fd <= 0)
        {
            LOG_E(TAG, "open: %s", name);
            perror(strerror(errno));
            break;
        }

        LOG_D(TAG, "%s opened", name);
        memset(buffer, 0, 1024 * 4);

        size = read(fd, buffer, 1024 * 4);
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
    } while (false);

    if (fd > 0)
    {
        close(fd);
    }

    return object;
}

bool ModbusDB_DeleteDefinition(const char *id)
{
    int ret = 0;
    char name[512];

    memset(name, 0, 512);
    tiny_snprintf(name, 255, "./db/modbus/definitions/%s.json", id);

    ret = remove(name);
    if (ret != 0)
    {
        LOG_E(TAG, "remove: %s", name);
        perror(strerror(errno));
    }

    return (ret == 0);
}

bool ModbusDB_SaveDefinition(const char *id, const char *buf)
{
    bool ret = false;
    int fd = 0;
    char name[256];

    do
    {
        memset(name, 0, 256);
        tiny_snprintf(name, 255, "./db/modbus/definitions/%s.json", id);

        fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd <= 0)
        {
            LOG_E(TAG, "open: %s", name);
            perror(strerror(errno));
            break;
        }

        LOG_D(TAG, "%s opened", name);

        ssize_t size = write(fd, buf, strlen(buf));
        if (size <= 0)
        {
            LOG_E(TAG, "write: %ld", size);
            perror(strerror(errno));
            break;
        }

        ret = true;
    } while (false);

    if (fd > 0)
    {
        close(fd);
    }

    return ret;
}
