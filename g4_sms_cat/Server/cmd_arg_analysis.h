/********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  arg.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(2020年07月26日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月26日 15时24分16秒"
 *                 
 ********************************************************************************/
#ifndef _ARG_ANALYSIS_H_
#define _ARG_ANALYSIS_H_ 

#include "g4_sms_cat_main.h"
#include "comport.h"



/* 参数解析 */
int arg_analysis(int argc,char **argv,ComportAttr *comport,int *LISTEN_PORT);

/* 打印用户手册 */
void print_usage(char *progname);

#endif
