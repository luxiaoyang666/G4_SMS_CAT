/*********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  print_usage.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(17/07/20)
 *         Author:  wangruijie <1046299465@qq.com>
 *      ChangeLog:  1, Release initial version on "17/07/20 04:16:59"
 *                 
 ********************************************************************************/
#include "cmd_arg_analysis.h"


/*
 * 功能：参数解析
 * 参数：argc参数个数；
 *       argv指向参数的指针；
 *       comport指向串口结构体指针；
 *       LISTEN_PORT监听端口；
 * 成功调用返回0，失败返回-1；
 */

int arg_analysis(int argc,char **argv,ComportAttr *comport,int *LISTEN_PORT)
{   
    int             opt;

	struct option            long_options[]=
    {                     
        {"port", required_argument, NULL, 'p'},
        {"baudrate", required_argument, NULL,'b'},
        {"databits", required_argument, NULL,'d'},
        {"check", required_argument, NULL, 'c'},
        {"stopbits", required_argument, NULL, 's'},
        {"name", required_argument, NULL, 'n'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };


    while((opt = getopt_long(argc,argv,"p:b:d:c:s:n:h",long_options,NULL))!=-1)
    {
        switch(opt)  
        {            
            case 'p':
                *LISTEN_PORT = atoi(optarg);
                break;
                     
            case 'b':
                comport->BaudRate = atoi(optarg);
                break;

            case 'd':
                comport->DataBits = atoi(optarg);
                break;

            case 'c':
                comport->Parity = optarg[0];
                break;

            case 's':
                comport->StopBits = atoi(optarg);
                break;

            case 'n':
                strncpy(comport->SerialName,optarg,SERIALNAME_LEN);
                break;
            case 'h':
                print_usage(argv[0]);
                return EXIT_SUCCESS;

            default:
                break;
        }
    }

    if(!LISTEN_PORT)
    {
        printf("Pleast indicate the Listen_Port");
		return -1;
    }

    /* 没有传入串口名 */
    if(strlen(comport->SerialName) == 0)
    {
        print_usage(argv[0]);
        return -1;
    } 

	return 0;
}


void print_usage(char *progname)
{
	printf("%s usage:\n",progname);
    printf("SMS Sending System v1.0.2(Mon 13 Jul 05:08:24 BST 2020)\n");
    printf("\nUsage:./sms [-p Port] [-b BaudRate] [-d Databits] [-c Parity] [-s StopBits] [-n SerialName]\n\n");
	printf("\t-p   sepcify server listen port.\n");
    printf("\t-b   Set BaudRate\n");
    printf("\t-d   Set Databits\n");
    printf("\t-c   Set Parity,0 for no parity,1 for Odd parity,2 for Evev parity\n");
    printf("\t-s   Set StopBits\n");
    printf("\t-n   Set the name of the serial port you want to use\n");
    printf("\nCtrl + c to exit the program\n");
    printf("\n\tIf you do not specify parameters,The default parameters of the program are as follows:\n\n");
    printf("\tBaudRate: 1115200\n\tDatabits: 8bits\n\tParity:   no parity\n\tStopBits: 1bits\n"); 

}

