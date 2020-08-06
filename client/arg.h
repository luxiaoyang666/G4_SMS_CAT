/********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  arc.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 14时38分36秒"
 *                 
 ********************************************************************************/
#ifndef _ARG_ANALYSIS_H_
#define _ARG_ANALYSIS_H_ 

#include "client_main.h"


int arg_analysis(int argc,char **argv,char **server_ip,int *server_port,int *loglevel);
void print_usage(const char *progname);

#endif
