/********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  log.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 19时03分36秒"
 *                 
 ********************************************************************************/
#ifndef LOG_H_
#define LOG_H_

#include <stdarg.h>
#include "g4_sms_cat_main.h"
#include "comport.h"

#define LOG_FILE "server.log"



#define LOG_MAXSIZE 1024*1024//日志文件的大小,默认1M
#define VASIZE 500//可变参数的大小
#define LOG_BUSSIZE 1024//日志缓存区的大小


/* 定义日志等级*/
enum LogLevel
{
        ERROR = 0,
        WARN,
        INFO,
        DEBUG,
};

extern int mylog(char *file,const char *function, int line, enum LogLevel level, const char *fmt, ...);
extern int log_init(int loglevel);


#define write_log_info(fmt,...) mylog(__FILE__,__func__,__LINE__,INFO,fmt,##__VA_ARGS__) 
#define write_log_error(fmt,...) mylog(__FILE__,__func__,__LINE__,ERROR,fmt,##__VA_ARGS__) 
#define write_log_warn(fmt,...) mylog(__FILE__,__func__,__LINE__,WARN,fmt,##__VA_ARGS__) 
#define write_log_debug(fmt,...) mylog(__FILE__,__func__,__LINE__,DEBUG,fmt,##__VA_ARGS__) 

#endif

