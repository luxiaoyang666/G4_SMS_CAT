/*********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  server.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(14/07/20)
 *         Author:  LuXiaoyang <920916829@qq.com>
 *      ChangeLog:  1, Release initial version on "14/07/20 09:05:12"
 *                 
 ********************************************************************************/
#include "g4_sms_cat_main.h"



/* 解析配置文件 */
static inline int parse_conf(gsmd_ctx_t *gsmd_ctx);

/* 初始化gsmd_ctx */
static inline int gsm_ctx_init(gsmd_ctx_t *gsmd_ctx);

int main(int argc, char **argv) 
{
    int                     rv = -1; 
    int                     listen_fd,  client_fd = -1; 
    struct sockaddr_in      serv_addr; 
    struct sockaddr_in      cli_addr;
    socklen_t               cliaddr_len; 
    int                     LISTEN_PORT;
    static int              loglevel = DEBUG;
    gsmd_ctx_t              gsmd_ctx;
    pthread_t               tid;
    pthread_mutex_t         mutex;
    pthread_mutexattr_t     attr;


    memset(&gsmd_ctx,0,sizeof(gsmd_ctx_t));
    if(gsm_ctx_init(&gsmd_ctx) < 0)
    {
        return -1;
    }

    //参数解析
    arg_analysis(argc,argv,gsmd_ctx.comport[1],&LISTEN_PORT);

    /* 加载配置文件 */
    rv = parse_conf(&gsmd_ctx);
    if(rv < 0)
    {
        printf("Parse conf failed\n");
        return -2;
    }


    //初始化日志
    log_init(loglevel);


    /*   pthread_mutex_lock(pthread_mutex_t *mutex);
     *   阻塞锁          
     *  */               

    /* PPP线程是否使能 */
    if (!strcmp("enable",gsmd_ctx.conf.ppp_enable))
    {
       if (thread_start(&tid, ppp_thread_worker,(void *)gsmd_ctx.conf.ping_network_card))
    	{	          
        	write_log_error("creat thread error: %s\n", strerror(errno));
    	}          
    	else                           
        	printf("create thread done.\n"); 
    }

    /* 阻塞接收客户端连接接受发短信 */
	if (!strcmp("enable",gsmd_ctx.conf.sms_enable))
	{
    	run_server(LISTEN_PORT,gsmd_ctx.comport[1]);
	}

    pthread_mutex_destroy(&gsmd_ctx.comport[1]->mutex); //释放锁

    gsmd_ctx_free(&gsmd_ctx);


    return 0;
	
}

static inline int gsm_ctx_init(gsmd_ctx_t *gsmd_ctx)
{

    if(!gsmd_ctx)
    {
        printf("Invalid argument\n");
        return -1;
    }

    gsmd_ctx->comport[0] = (ComportAttr *)malloc(sizeof(ComportAttr));
    gsmd_ctx->comport[1] = (ComportAttr *)malloc(sizeof(ComportAttr));

    memset(gsmd_ctx->comport[0],0,sizeof(ComportAttr));
    memset(gsmd_ctx->comport[1],0,sizeof(ComportAttr));


    return 0;

}

/* 解析配置文件 */
static inline int parse_conf(gsmd_ctx_t *gsmd_ctx)
{

    dictionary              *ini   =  NULL;

    if(!gsmd_ctx)
    {        
        printf("Invalid argument\n");
        return -1;
    }

    ini = iniparser_load(INI_PATH);  //加载配置文件
    if(ini == NULL)
    {
        printf("iniparser_load error!\n");
        return -1;
    }

    /* 获取串口名称 */
    strcpy(gsmd_ctx->comport[0]->SerialName,iniparser_getstring(ini,"PPP:serial",NULL));
    strcpy(gsmd_ctx->comport[1]->SerialName,iniparser_getstring(ini,"SMS:serial",NULL));

    /* 获取使能情况 */
    strcpy(gsmd_ctx->conf.ppp_enable,iniparser_getstring(ini,"PPP:enable",NULL));
    strcpy(gsmd_ctx->conf.sms_enable,iniparser_getstring(ini,"SMS:enable",NULL));

    /* 获取测试网卡 */
    strcpy(gsmd_ctx->conf.ping_network_card,iniparser_getstring(ini,"PPP:interfaces",NULL));

    /* 若命令行未指定端口，则使用配置文件端口 */
    if(!gsmd_ctx->conf.sms_port)
    {
        /* 获取指定端口 */
        strcpy(gsmd_ctx->conf.sms_port,iniparser_getstring(ini,"SMS:port",NULL));
    }


    /* 关闭配置文件操作句柄 */
    iniparser_freedict(ini);

    return 0;
}

