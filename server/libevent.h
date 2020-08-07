/********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  libevent.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(2020年07月26日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月26日 19时34分30秒"
 *                 
 ********************************************************************************/

#ifndef LIBEVENT_H_
#define LIBEVENT_H_


/*  连接客户端 */
void do_accept(evutil_socket_t listener, short event, void *arg);
/*  读取客户端的数据 */
void read_cb(struct bufferevent *bev, void *arg);
/*  一些出错处理 */
void error_cb(struct bufferevent *bev, short event, void *arg);


#endif
