/*********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  socket.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 10时44分33秒"
 *                 
 ********************************************************************************/
#include "g4_sms_cat_main.h"
#include "socket.h"

int socket_init(socket_st *socket_t)
{
   //创建socket套接字，并连接至服务器端
    //struct sockaddr_in      servaddr;
	socket_t->fd = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_t->fd < 0)
    {
		printf("create socket failure: %s\n", strerror(errno));
        return -1;
    }
    memset(&socket_t->serv_addr, 0, sizeof(socket_t->serv_addr));
  	socket_t->serv_addr.sin_family = AF_INET;
    socket_t->serv_addr.sin_port = htons(socket_t->server_port);
    inet_pton( AF_INET,socket_t->server_ip, &socket_t->serv_addr.sin_addr);

    return 0;
}

int socket_connect(socket_st *socket_t)
{
    int rv = -1;
    if((rv = connect(socket_t->fd, (struct sockaddr *)&socket_t->serv_addr, sizeof(socket_t->serv_addr))) <  0)
    {
        printf("connect failure: %s\n", strerror(errno));
        return rv;
    }

    socket_t->status = CONNECTED;
    return 0;

}

