/*********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  conn_read.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2020年07月31日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月31日 16时47分59秒"
 *                 
 ********************************************************************************/
#include "Msg_4G_server.h"

int stop_flag = 0;

void sighandler(int sig_num)
{
    if(sig_num == SIGINT)
    {
        stop_flag = 1;
    }

}

/* 
 * 功能：验证客户端的登录信息并发送短信
 * 参数：
 * 返回值：成功返回0，失败返回-1
 *
 */
int check_sms(struct bufferevent *bev,void *arg,ComportAttr *comport)
{
    char            rbuf[BUFFER_SIZE];
    char            buf[BUFFER_SIZE];
    char            json_buf[1024];
    char            *data = buf;
    static int      num = 3;
    int             rv = -1;
	int 			fd_com = -1;
	sqlite3                 *db; 
    CLType          *head = NULL;
    CLType          *temp_ptr = NULL; 
    msg_pack_t      msg_pack;

    //链表初始化
    InitList(&head);

    rv = readcb(bev,arg,rbuf);
    if(rv < 0)
        return -1;
    
    //检测链表中有无加密后的匹配数据
    while(num)
    {
		rv = login_check(head,rbuf);
    	if(rv < 0)
    	{    
        	printf("Wrong user name or password\n");
    	}
        else
            break;
		num--;	     
    }    
	if(num==0)
    {
        printf("Verification failed, program exit\n");
        return -1;
    }
    //初始化数据库
    if(sql_open(&db) < 0)
    {
        write_log_error("Failed to initialize database\n");
        return 0;
    } 
    //初始化串口
 	rv = comport_init(comport);
    if(rv < 0)
    {
        printf("comport_init failure\n");
        return rv;
    }
	fd_com = comport_open(comport);
    if(fd_com < 0)
    {
        printf("comport_open failure\n");
        return rv;
    }
	fflush(stdin); //刷新缓冲区
	signal(SIGINT, sighandler) ;
    printf("Device open successfully\n");
	
    while(!stop_flag)
    {
        //检查sim卡状态
        rv = check_sim_allready(comport);
        if(rv < 0)
        {
            printf("There is something wrong with SIM card:%d\n",rv);
            return rv;
        }
        //查询sim卡中有无发送给连接客户端短信
        temp_ptr = FindNode(head,rbuf);
        if(temp_ptr == NULL)
        {
            printf("Query failed\n");
        }
        else
        {
            rv = get_module_sms(comport,buf,sizeof(buf),temp_ptr->nodeData.target_number);
            if(rv == 0)
                printf("There is no SMS in the module or no SMS for the target_number\n");
            else if(rv < 0)
                printf("No matching SMS content\n");
            else{
				rv = pack_json(data,json_buf);
                if(rv < 0)
                {
                     printf("pack json failure:%s\n", strerror(errno));
                     return rv;
                }
				if( write(temp_ptr->nodeData.client_fd, json_buf, strlen(json_buf)) < 0 )
               	{
               	     printf("Write data to client failure: %s\n", strerror(errno));
                     return rv;
                }
				else
                {
                     rv = delete_sms(comport,temp_ptr->nodeData.target_number);
                     if(rv < 0)
                     {
                         printf("Failed to delete SIM card SMS\n");
                     }
                }
                memset(json_buf, 0, sizeof(json_buf));
            }

            memset(rbuf, 0, sizeof(rbuf));
            //接收发送短信内容  
            rv = readcb(bev,arg,rbuf);
            if(rv < 0)
              return -1;

            rv = pdu_sms_send(comport,msg_pack.message,msg_pack.phone);
            if(rv < 0)
            {
                printf("Failed to send SMS, save to database\n");
				rv = sql_insert(db,msg_pack);
            }
			strcpy(temp_ptr->nodeData.target_number,msg_pack.phone);
        }
    }
    sql_close(db);
	close(temp_ptr->nodeData.client_fd);

}

/* **************************************************************
 * 函数名：readcb
 * 功能：读取客户端的数据
 * 参数：bev，arg
 * 返回值：
 * **************************************************************/
int readcb(struct bufferevent *bev,void *arg,char *rbuf)
{
    char             buf[BUFFER_SIZE];
    //char             rbuf[BUFFER_SIZE];
    size_t           n;

    n = bufferevent_read(bev, buf, BUFFER_SIZE - 1);
    if(n <= 0)
    {
        printf("Failed to read data from client\n");
        return -1;
    }
    buf[n] = '\0';
    unpack_json(buf, rbuf);

    return 0;
}


