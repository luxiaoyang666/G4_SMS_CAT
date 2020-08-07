/*********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  log.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 19时02分30秒"
 *                 
 ********************************************************************************/

#include <stdarg.h>
#include "server_main.h"
#include "comport.h"

#define LOG_FILE "server.log"



#define LOG_MAXSIZE 1024*1024//日志文件的大小,默认1M
#define VASIZE 500//可变参数的大小
#define LOG_BUSSIZE 1024//日志缓存区的大小
FILE *fp;
int  fd;

static int s_loglevel = DEBUG;
//gcc扩展语法,通过s_loginfo数组即可获取等级对应的字符串
static const char* s_loginfo[] =
{
    "ERROR","WARN","INFO","DEBUG"
};


/* 
 * 功能：初始化日志系统
 * 参数：无
 * 返回值：成功返回0，失败返回-1*
 */
int log_init(int loglevel)
{
    if((fp = fopen(LOG_FILE,"a+")) == NULL)
    {
        write_log_error("open client.log failed:%s\n",strerror(errno));
        return -1;
    }
    fd = fileno(fp);//文件指针转化为文件描述符
    if(fd < 0)
    {
        printf("fileno error:%s\n",strerror(errno));
        return -1;
    } 


    return 0;
}


/*
 * 功能：将日志信息写入日志文件
 * 参数：file：哪个文件发生写日志事件(input)
 *       function：哪个函数发生写日志事件(input)
 *       line：哪一行发生写日志事件(input)
 *       LogLevel：日志等级
 *       fmt：日志的格式
 *       ...：参数列表
 * 返回值：成功返回0,失败返回-1
 */
int mylog(char *file,const char *function, int line, enum LogLevel level, const char *fmt, ...)//含有可变参数的函数
{
        time_t         t;
        struct tm      *p;
        struct timeval tv;
        char           buf[VASIZE];
        char           log_buf[LOG_BUSSIZE];
        char           time_buf[32];
        va_list        arg_list;
        int            millisec;
        off_t          filesize;

        memset(buf,0,sizeof(buf));

        //开始应用可变参数
        va_start(arg_list,fmt);//指向可变参数表中的第一个参数
        vsnprintf(buf,sizeof(buf),fmt,arg_list);//将可变参数输出到buf中

        //可变参数的应用区结束
        va_end(arg_list);

        //获取事件戳
        t = time(NULL);
        p = localtime(&t);

        gettimeofday(&tv,NULL);
        millisec = (int)(tv.tv_usec/100);

        //制作时间的格式：年月日时分秒毫秒
        snprintf(time_buf,32,"%04d-%02d-%02d %02d:%02d:%02d:%03d",p->tm_year+1900,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec,
millisec);
		if(level > s_loglevel)//日志等级不存在则返回
                return -1;

        //制作日志格式：时间+函数+行+信息
        snprintf(log_buf,sizeof(buf),"%s: [%s][%s:%s:%d]information is: %s",s_loginfo[level],time_buf, file, function, line, buf);

        //刚打开文件的时候文件指针默认在文件头，所以先将文件指针偏移到文件尾
        if((filesize=lseek(fd,0,SEEK_END)) ==-1 )
        {
            printf("lseek failed:%s\n",strerror(errno));
            return -1;
        }

        //控制文件不要无限制增长，设置文件最大容量，到达就清空
        if(filesize > LOG_MAXSIZE)
        {
            printf("The log file size reaches the upper limit and the file is cleared!\n");
            if(ftruncate(fd,0) ==-1 )//清空文件
            {
                printf("ftruncate failed:%s\n",strerror(errno));
                return -1;
            }
        }

        write(fd,log_buf,strlen(log_buf));

        return 0;

}
