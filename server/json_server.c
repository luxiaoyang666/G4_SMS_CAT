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
#include "json_server.h"
#include "ppp.h"


int main(int argc, char **argv) 
{
    int                     rv = -1; 
    int                     listen_fd,  client_fd = -1; 
    struct sockaddr_in      serv_addr; 
    struct sockaddr_in      cli_addr;
    socklen_t               cliaddr_len; 
    char                    buf[1024]; 
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

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if(listen_fd < 0)
    {
        printf("create socket failure: %s\n", strerror(errno)); 
        return -1;
    }
    printf("socket create fd[%d]\n", listen_fd); 

    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(LISTEN_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if( bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ) 
    {
        printf("create socket failure: %s\n", strerror(errno)); 
        return -2;
    }
    printf("socket[%d] bind on port[%d] for all IP address ok\n", listen_fd, LISTEN_PORT); 

    listen(listen_fd, BACKLOG);

    while(1)
    {
        printf("\nStart waiting and accept new client connect...\n", listen_fd);
        client_fd = accept(listen_fd, (struct sockaddr*)&cli_addr, &cliaddr_len); 
        if(client_fd < 0) 
        {
            printf("accept new socket failure: %s\n", strerror(errno)); 
            return -2;
        }
        printf("Accept new client[%s:%d] with fd [%d]\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), client_fd); 

        memset(buf, 0, sizeof(buf));
        if( (rv=read(client_fd, buf, sizeof(buf))) < 0) 
        {
            printf("Read data from client socket[%d] failure: %s\n", client_fd, strerror(errno)); 
            close(client_fd);
            continue;
        }
        else if( rv == 0 ) 
        {
            printf("client socket[%d] disconnected\n", client_fd); 
            close(client_fd); 
            continue;
        }
        printf("read  data from client[%d] and echo it back:%s\n", client_fd, buf); 

        rv = unpack_json(buf);
        if(rv < 0)
        {
            printf("unpack data failure:%s\n", strerror(errno));
            return -2;
        }

        sleep(1);
    }
    close(listen_fd);
    pthread_mutex_destroy(&mutex); //释放锁

}


























































