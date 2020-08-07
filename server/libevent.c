/*********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  libevent.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(26/07/20)
 *         Author:  wangruijie <1046299465@qq.com>
 *      ChangeLog:  1, Release initial version on "26/07/20 10:05:06"
 *                 
 ********************************************************************************/
#include "json_server.h"

/* *********************************************
 * 函数名：do_accept
 * 功能：连接客户端并设置bufferevent
 * 参数：listen_fd, event, arg
 * 返回值：
 * ***********************************************/
void do_accept(evutil_socket_t listen_fd, short event, void *arg)
{
    struct event_base               *base = (struct event_base *)arg;
    evutil_socket_t                 fd;
    struct sockaddr_in              serv_addr;
    socklen_t                       slen = sizeof(serv_addr);

    fd = accept(listen_fd, (struct sockaddr *)&serv_addr, &slen);
    if(fd < 0)
    {
        printf("accept error :%s\n", strerror(errno));
        return ;
    }

    printf("ACCEPT: fd = %u\n", fd);

    //关联该sockfd，托管给event_base
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    //设置读写对应的回调函数
    bufferevent_setcb(bev, read_cb, NULL, error_cb, arg);
    bufferevent_enable(bev, EV_READ|EV_PERSIST);
    /* 进入bufferevent_setcb回调函数
     * 在read_cb里面从input中读取数据，处理完毕后填充到output中；
     * writecb对于服务端程序，只需要readcb就可以了，可以置为NULL；
     * error_cd处理一些错误*/
}

/* ***********************************************************************************
 * 函数名:read_cb
 * 功能：读取客户端的数据和发送服务器数据
 * 参数：bev, arg
 * *************************************************************************************/
void read_cb(struct bufferevent *bev, void *arg)
{
    char            buf[MAX_LINE+1];
    int             n;
    evutil_socket_t fd = bufferevent_getfd(bev);

    /* 读取客户端的内容 */
    while (n = bufferevent_read(bev, buf, MAX_LINE), n > 0)
    {
        buf[n] = '\0';
        printf("fd=%u, Server gets the message from client read buf: %s\n", fd, buf);
        /* 收到数据后，可以选择发送的内容，这里直接回显 */
        bufferevent_write(bev, buf, n);
    }
}

/* ************************************************************
 * 函数名：error_cb
 * 功能：出错处理
 * 参数：bev, event, arg
 * 返回值：
 * *************************************************************/
void error_cb(struct bufferevent *bev, short event, void *arg)
{
    evutil_socket_t             fd = bufferevent_getfd(bev);
    
    printf("fd = %u, ", fd);
    /* 超时 */
    if (event & BEV_EVENT_TIMEOUT)
    {
        printf("Timed out\n");
    }
    else if (event & BEV_EVENT_EOF)
    {
        printf("connection closed\n");
    }
    /* 错误 */
    else if (event & BEV_EVENT_ERROR)
    {
        printf("some other error\n");
    }
    /* 释放 */
    bufferevent_free(bev);
}
