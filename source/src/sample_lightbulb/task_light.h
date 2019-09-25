/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   task_light.h
*
* @remark
*
*/

#ifndef __task_light_H__
#define __task_light_H__

#include <product/Product.h>

TINY_BEGIN_DECLS


TinyRet task_light_start(Product *product);
TinyRet task_light_stop(void);


TINY_END_DECLS

#endif /* __task_light_H__ */