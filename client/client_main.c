/*********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  client.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(14/07/20)
 *         Author:  wangruijie <1046299465@qq.com>
 *      ChangeLog:  1, Release initial version on "14/07/20 13:47:24"
 *                 
 ********************************************************************************/
#include "client_main.h"
#include "cJSON.h"
#include "data.h"

int g_stop = 0;
#define MAX_DATA_NUM       10000

void sighandler(int sig_num)
{
    if(sig_num == SIGINT)
    {
        g_stop = 1;
    }
}

int main(int argc, char **argv) 
{
    socket_st               socket_t;
    int                     rv = -1; 
    char                    json_buf[1024]; 
    char                    data_buf[BUF_LEN];
    char                    *data = data_buf;
    sqlite3                 *db;
    char                    *sqlite_name;
    char                    *progname = NULL;
    int                     opt;
    static int              loglevel = DEBUG;
    msg_pack_t				msg_pack;
	static int          	data_num = 0;

    //参数解析
    rv = arg_analysis(argc,argv,&socket_t.server_ip,&socket_t.server_port,&loglevel);
    if(rv < 0)
    {
        printf("arg analysis failed.\n");
        return -1;
    }

    //初始化日志
    log_init(loglevel);
    write_log_info("server IP is %s\n",socket_t.server_ip);
    write_log_info("server port is %d\n",socket_t.server_port);
 
    socket_t.status = DISCONNECTED;

	signal(SIGINT, sighandler);      //安装信号
    
   
    //初始化数据库
	if(sql_open(&db) < 0)
    {
        write_log_error("Failed to initialize database\n");
        return 0;
    }  
    
    memset(json_buf, 0, strlen(json_buf));
    while(!g_stop)
    {
        if(DISCONNECTED == socket_t.status)
        {
			if((rv = socket_init(&socket_t)) <  0)
            {
                printf("Failed to initialize socket\n");
            }
			if((rv = socket_connect(&socket_t)) <  0)
            {
                close(socket_t.fd);
                write_log_error("connect to server [%s:%d] failure :%s\n",socket_t.server_ip, socket_t.server_port,strerror(errno));
				socket_t.status = DISCONNECTED;
                //没连接上服务器，将采样到的数据保存到数据库中
                write_log_info("Store data in database\n");
                rv = sql_insert(db,msg_pack); 
				data_num = get_counts(db);
                if(data_num >= MAX_DATA_NUM)
                {
         	         delete_data(db,data_num,1);
                     data_num = get_counts(db);
                }
				continue;
            }
            socket_t.status = CONNECTED;
			
        }
	    else{
               rv = pack_json(data,json_buf);
        	   if(rv < 0)
        	   {
               		printf("pack json failure:%s\n", strerror(errno));
            		return -1;
        	   }
        	   printf("data:%s\n", json_buf);

        	   if( write(socket_t.fd, json_buf, strlen(json_buf)) < 0 )
        	   {
             		printf("Write data to server [%s:%d] failure: %s\n", socket_t.server_ip, socket_t.server_port, strerror(errno));
            		return -1;
        	   }
        	   memset(json_buf, 0, sizeof(json_buf)); 
        }


    }

	sql_close(db);
	close(socket_t.fd);
}

