/*********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  run_server.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2020年07月31日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月31日 16时49分08秒"
 *                 
 ********************************************************************************/
#include "Msg_4G_server.h"

/* *****************************************************************
 * 函数名：
 * 功能：
 * 参数：
 * 返回值：
 * *****************************************************************/
int run_server(int SERVER_PORT,ComportAttr *comport)
{
    struct sockaddr_in        sin;
    struct evconnlistener     *listener;
    int                       rv;
    
    EventBase *base = event_base_new();    // 创建一个event base 
    assert(base);

    memset(&sin, 0, sizeof(sin));   //清零sin结构体
    sin.sin_family = AF_INET;   //设置为IP通信
    sin.sin_addr.s_addr = htonl(INADDR_ANY);     //服务器IP地址
    sin.sin_port = htons(SERVER_PORT);   //服务器端口

    /* 开始创建evconnlistener_new_bind并调设置回调函数 */
    listener = evconnlistener_new_bind(base, acceptcb, base,LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_EXEC,-1,  (struct sockaddr *)&sin, sizeof(sin));
    assert(listener);
    assert(evconnlistener_get_fd(listener) > 0);

    /* 开始循环loop，其主要作用是循环监听*/
    rv = event_base_dispatch(base);
    /* return 0 if successful, -1 if an error occurred, or 1 if we exited */
    assert(rv >= 0);

    /* 用完释放base */
    event_base_free(base);

    return 0;

}

/* **********************************************************
 * 函数名：acceptcb
 * 功能：连接客户端
 * 参数：listener，fd，addr，socklen，arg
 * 返回值：
 * **********************************************************/
void acceptcb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int socklen, void *arg, ComportAttr *comport)
{
    EventBase          *base = (EventBase *)arg;
    struct sockaddr_in *sin = (struct sockaddr_in *)addr;
    struct bufferevent *bev;

    printf("connection from %s:%d\n", inet_ntoa(sin->sin_addr), ntohs(sin->sin_port));

    /* 设置连接 */
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, check_sms, NULL, eventcb, comport);

    bufferevent_enable(bev, EV_READ);
}

/* ************************************************************
 * 函数名：eventcb
 * 功能：出错处理
 * 参数：bev，flag，arg
 * 返回值：
 * ************************************************************/
void eventcb(struct bufferevent *bev, short flag, void *arg)
{
    if(flag & BEV_EVENT_EOF)
    {
        printf("remote peer closed\n");
    }
    else if(flag & BEV_EVENT_ERROR)
    {
        printf("error\n");
    }
    else if (flag & BEV_EVENT_TIMEOUT)
    {
        printf("timeout\n");
    }

    /* 出错了就释放 */
    bufferevent_free(bev);
}


