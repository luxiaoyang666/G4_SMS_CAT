/********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  g4_sms_cat_main.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(14/07/20)
 *         Author:  LuXiaoyang <920916829@qq.com>
 *      ChangeLog:  1, Release initial version on "14/07/20 04:42:06"
 *                 
 ********************************************************************************/
#ifndef  _G4_SMS_CAT_MAIN_H_
#define  _G4_SMS_CAT_MAIN_H_


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <pthread.h>
#include <getopt.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#include <pthread.h>

#include <event2/event.h>
#include <event2/listener.h>
#include <assert.h>
#include <event2/bufferevent.h>
#include <openssl/md5.h>

#include "cmd_arg_analysis.h"
#include "at_cmd.h"
#include "log.h"
#include "thread.h"
#include "MD5.h"
#include "sql.h"
#include "comport.h"
#include "iniparser.h"
#include "libevent.h"

#define BACKLOG              13 
#define BUFFER_SIZE          1024
#define LE_ADDRESS_SIZE      32
#define INI_PATH             "etc/gsmd.conf"



/* 将struct event_base重命名为EventBase，方便以后使用 */
typedef struct event_base EventBase;

/* 将struct event重命名为Event，方便后面使用 */
typedef struct event Event;

/* 初始化服务器的连接 */
int run_server(int SERVER_PORT,ComportAttr *comport);

/* 连接客户端 */
void acceptcb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int socklen, void *arg, ComportAttr *comport);

/* 检测登录信息、发送短信 */
int check_sms(struct bufferevent *bev,void *arg,ComportAttr *comport);

/* 从客户端读取数据 */
int readcb(struct bufferevent *bev, void *arg,char *rbuf);

/* 一些出错处理 */
void eventcb(struct bufferevent *bev, short flag, void *arg);

/* 设置信号 */
void sighandler(int sig_num);

/*打包数据*/
int pack_json(char *data,char *json_buf);

/*解包数据*/
int unpack_json(char *buf,char *rbuf);



#endif   /*  ----- #ifndef _G4_SMS_CAT_MAIN_H_  ----- */ 
