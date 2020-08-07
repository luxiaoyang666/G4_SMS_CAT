/*********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  server.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(14/07/20)
 *         Author:  wangruijie <1046299465@qq.com>
 *      ChangeLog:  1, Release initial version on "14/07/20 09:05:12"
 *                 
 ********************************************************************************/
#include "cJSON.h"
#include "server_main.h"
#include "ppp.h"


int main(int argc, char **argv) 
{
    int                     rv = -1; 
    int                     listen_fd,  client_fd = -1; 
    struct sockaddr_in      serv_addr; 
    struct sockaddr_in      cli_addr;
    socklen_t               cliaddr_len; 
    int                     LISTEN_PORT;
    static int              loglevel = DEBUG;
	ComportAttr         	*comport;
    pthread_t               tid;
    pthread_mutex_t         mutex;
    pthread_mutexattr_t     attr;
    char                    *iface ="wlan0";


    comport = (ComportAttr *)malloc(sizeof(ComportAttr));
    memset(comport,0,sizeof(ComportAttr));
    //参数解析
    rv = arg_analysis(argc,argv,comport,&LISTEN_PORT);
 
    //初始化日志
    log_init(loglevel);


    pthread_mutex_init(&mutex, &attr);
    pthread_mutex_init(&mutex,&attr);  //初始化锁
    pthread_mutex_trylock(&mutex);     //非阻塞上锁 
    /*   pthread_mutex_lock(pthread_mutex_t *mutex);
     *   阻塞锁          
     *  */               

    if (thread_start(&tid, thread_worker,(void *)iface))
    {
        write_log_error("creat thread error: %s\n", strerror(errno));
    }
    else 
        printf("create thread done.\n");

    pthread_mutex_unlock(&mutex); //解锁

    //阻塞接收客户端连接接受发短信
    run_server(LISTEN_PORT,comport);

    pthread_mutex_destroy(&mutex); //释放锁

}


























































