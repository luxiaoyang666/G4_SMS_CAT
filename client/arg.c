/*********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  arg.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 14时37分23秒"
 *                 
 ********************************************************************************/

#include "arg.h"

/*
 * 功能：参数解析
 * 参数：argc参数个数；
 *       argv指向参数的指针；
 *       server_IP服务器IP；
 *       server_port服务器端口；
 * 成功调用返回0，失败返回-1；
 */

int arg_analysis(int argc,char **argv,char **server_ip,int *server_port,int *loglevel)
{
    int             opt;//getopt_long函数返回值
    int             domain_mark = 0;//域名解析

    struct option   long_options[] = {
        {"ip",1,NULL,'i'},
        {"port",1,NULL,'p'},
        {"loglevel",0,NULL,'l'},
        {"help",0,NULL,'h'},
        {0,0,0,0}
    };

	while((opt = getopt_long(argc,argv,"i:p:l:d:h",long_options,NULL)) > 0)
    {
        switch(opt)
        {
            case 'l':
                *loglevel = atoi(optarg);
                break;
            case 'i':
                *server_ip = optarg;
                break;
            case 'd':
                //*server_ip = DNS(optarg);
                domain_mark = 1;
                break;
            case 'p':
                *server_port = atoi(optarg);
                break;
            case 'h':
                printf("%s usages:\n",argv[0]);
                printf("-I(ip):server ip\n");
				printf("-p(port):server port\n");
                printf("-l(loglevel):log debug level\n");
    			printf("-d(domain):domain name prase\n");
    			printf("-h(help):help information\n");
				break;
			default:
				break;
        }
    }

	//如果没有指定服务器的IP和端口返回-1

	if(!(*server_ip)||(!server_port && !domain_mark))
    {
        printf("Please indicate the IP and port of the server");
        return -1;
    }

	return 0;
}

void print_usage(const char *progname)
{
    printf("Usage: %s [OPTION]...\n", progname);
    printf("This program used to connect to server \n");

    printf("\nMandatory arguments to long options are mandatory for short options too:\n");
    printf(" -p[port    ]  Specify host server address and port, foramt as \"8889\"\n");
    printf(" -i[ip] into ipaddr, foramt as \"127.0.0.1\"\n");
    printf(" -h[help    ]  Display this help information\n");
    printf("\n");

    return;
}


