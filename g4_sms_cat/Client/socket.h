/********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  socket.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 10时38分17秒"
 *                 
 ********************************************************************************/
#ifndef _SOCKET_H_
#define _SOCKET_H_

#define DISCONNECTED 0
#define CONNECTED 1

typedef struct socket_s
{
    int             fd;                     //文件描述符
    int             status;                 //连接状态
    char            *server_ip;             //服务器ip
    int             server_port;            //端口
    struct          sockaddr_in  serv_addr; //服务器结构体
}socket_st;




int socket_init(socket_st *socket_t);
int socket_connect(socket_st *s_socket_t);


#endif

