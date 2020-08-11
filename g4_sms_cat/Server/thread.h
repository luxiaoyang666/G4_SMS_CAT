/********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  thread.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(2020年07月26日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月26日 09时04分15秒"
 *                 
 ********************************************************************************/
#ifndef  _THREAD_H_
#define  _THREAD_H_

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>


typedef void *(WORKWER_BODY) (void *thread_arg); //定义函数指针
int   thread_start(pthread_t * thread_id, WORKWER_BODY* thread_workbody, void * thread_arg);

/* ppp拨号线程 */
void  *ppp_thread_worker( void *ctx);


#endif

