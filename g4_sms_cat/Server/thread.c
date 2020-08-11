/*********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  thread.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2020年07月26日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月26日 09时01分23秒"
 *                 
 ********************************************************************************/
#include "thread.h"
#include "ppp.h"

int thread_start(pthread_t * thread_id, WORKWER_BODY* thread_workbody, void * thread_arg)
{

    pthread_attr_t      thread_attr;

    if(pthread_attr_init(&thread_attr))  //初始化线程属性 thread_attr
    {
        printf("pthread_attr_init() failure:%s\n", strerror(errno));
        goto CleadUp;
    }

    if(pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED)) //设置可分离的状态
    {
        printf("pthread_attr_detachstate() failure:%s\n", strerror(errno));
        goto CleadUp;
    }

    if(pthread_create(thread_id, &thread_attr, thread_workbody, thread_arg)) //创建子线程
    {
        printf("pthread_create() failure:%s\n", strerror(errno));
        goto CleadUp;
    }

    return 0;

    //g_signal.threads++;
CleadUp:
    pthread_attr_destroy(&thread_attr); //摧毁线程属性，释放占用资源
    return -1;
}

void *ppp_thread_worker( void *ctx)
{
    char       *iface = NULL;
    if(NULL == ctx)
    {
        printf("Invalid input arguements in %s()\n", __FUNCTION__);
        pthread_exit(NULL);
    }
    iface = (char *)ctx;
    while(1)
    {
        if (nic_ping_test())
        {
            printf("ppp error: %s\n", strerror(errno));
        }

        sleep(10);
    }
}

