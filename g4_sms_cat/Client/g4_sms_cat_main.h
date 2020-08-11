/*********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  g4_sms_cat_main.h
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(13/07/20)
 *         Author:  wangruijie <1046299465@qq.com>
 *      ChangeLog:  1, Release initial version on "13/07/20 13:07:53"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <libgen.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>

#include "sqlite3.h"
#include "socket.h"
#include "cmd_arg_analysis.h"
#include "log.h"
#include "sql.h"

#define     BUF_LEN      1024


int pack_json(char *data,char *json_buf);
