/*********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  sql.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 19时01分08秒"
 *                 
 ********************************************************************************/
#include "sql.h"

#define DATABASE "database"

#define TABLE "temp"

static int get_counts_callback(void *date,int argc,char **argv,char **ColName);
static int get_data_callback(void *ptr, int argc, char **argv, char **ColName);

/*
 * 功能：若数据库不存在则创建数据库；
 *       若表不存在则创建表
 * 参数：db数据库操作的句柄
 * 成功返回0，失败返回-1
 *
*/
int sql_open(sqlite3 **db)
{
    char    *errmsg;
    if(sqlite3_open(DATABASE,db) != SQLITE_OK)
    {
        write_log_error("sqlite3 open failed :%s\n", sqlite3_errmsg(*db));
        return -1;
    }

    write_log_info("create database success.\n");

   if(sqlite3_exec(*db,"create table if not exists "TABLE" (id INTEGER PRIMARY KEY AUTOINCREMENT,phone text,message text);",NULL,NULL,&errmsg)!=SQLITE_OK)
	{
		write_log_error("Create failed:%s\n",errmsg);
        return -1;
	} 

	write_log_info("open table "TABLE" successfully!\n");

	return 0;
}

/*
 * 功能：插入数据到数据库
 * 参数：db数据库操作句柄
 *       date日期
 *       time时间
 *       sn序列号
 *       temp温度
 * 成功返回0，失败返回-1
*/

int sql_insert(sqlite3 *db,msg_pack_t msg_pack)
{
    char      *errmsg;
    char      sql[128];

    if(!db)
    {
        write_log_error("database not exist!\n");
        return -1;
    }

    memset(sql,0,sizeof(sql));

    if(snprintf(sql, sizeof(sql), "insert into "TABLE" values(null,'%s','%s');",msg_pack.phone,msg_pack.message)<0)
	{
		write_log_error("sprintf error:%s\n",strerror(errno));
		return -1;
	}
	
	write_log_info("sql: [%s]\n",sql);

	if((sqlite3_exec(db,sql,NULL,NULL,&errmsg)) != SQLITE_OK)
	{ 
		write_log_error("insert data into database failed:%s\n",errmsg);
		return -1;
	}

	write_log_info("insert data successfully\n");

	return 0; 
}

/*
 * 功能：关闭数据库
 * 参数：db数据库操作句柄
 * 返回值：成功返回0，失败返回-1；
*/

int sql_close(sqlite3 *db)
{
    if(sqlite3_close(db) != SQLITE_OK)
    {
        write_log_error("database close failed:%s\n",sqlite3_errmsg(db));
        return -1;
    }

    return 0;
}

/*
 * 功能：删除记录
 * 参数：db数据库操作句柄
 * 		 cmd:0删除指定行，1删除前n行
 *		 n:仅当cmd为1时为删除前n行
 * 返回：成功返回0，失败返回-1
*/
int delete_data(sqlite3 *db,int n,int cmd)
{
    int         rc = -1;
    char        *msg = 0;
    char        sql[100];

    if(cmd)
        sprintf(sql,"delete from "TABLE" where id in(select id from "TABLE" limit %d);",n);                   
    else 
        sprintf(sql,"DELETE from "TABLE" where id=%d;",n);
    rc = sqlite3_exec(db, sql, NULL, NULL, &msg);
    if( rc != SQLITE_OK)
    {
        write_log_error("SQL error:%s\n", msg);
        sqlite3_free(msg);
        return -1;
    }
    else 
        write_log_info("delete data successfully\n");
    return 0;
}

/*
 * 功能: 查询数据库中记录总数
 * 参数: db:数据库操作句柄
 *       num:表中记录总条数
 * 返回：成功返回记录条数，失败返回-1
*/

int get_counts(sqlite3 *db)
{
    char        *sql;
    char        *msg = 0;
    int         rc = -1;
    int         num = 0;

    sql = "SELECT count(*) from "TABLE"";

    rc = sqlite3_exec(db, sql, get_counts_callback, (void*)&num, &msg);
    if( rc != SQLITE_OK)
    {
        write_log_error("get data_counts from databass error:%s", msg);
        sqlite3_free(msg);
        return -1;
    }
	else
	{
        if(num == 0)
        {
            sql = "UPDATE sqlite_sequence SET seq=0 WHERE name = '"TABLE"';";
            rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
            if(rc != SQLITE_OK)
                write_log_error("sql error\n"); 
        }
		write_log_info("get data_counts from databass successfully\n");
    }
	return num;
}
/* 
 * 功能:获取数据库中记录总数
*/
static int get_counts_callback(void *data,int argc,char **argv,char **ColName)
{
    int *count = (int *)data;
    if(argv[0] != NULL)
    {
        *count = atoi(argv[0]);
    }
    else 
        *count = 0;
    return 0;
}

/* 
 * 功能：从数据表中取出一条数据
 * 参数：db数据库操作句柄
 *       p指向返回数据的指针
 * 返回值：成功返回0，失败返回-1*/
int get_data(sqlite3 *db,msg_pack_t *p)
{
    char    *sql;
    char    *msg = 0;
    int     rc = -1;
    sql = "select * from "TABLE" LIMIT 1;";

    rc = sqlite3_exec(db, sql, get_data_callback,(void *)p, &msg);
    if(rc != SQLITE_OK)
    {
        write_log_error("get data from databass error:%s", msg);
        sqlite3_free(msg);
        return -1;
    }
    else
        write_log_info("get data from databass successfully\n");
    return 0;
}

/* 功能：获取记录的回调函数*/
static int get_data_callback(void *ptr, int argc, char **argv, char **ColName)
{
    int i = 0;
    msg_pack_t *msg_pack = (msg_pack_t *)ptr;
    for(i=0; i<argc; i++)
    {
        if(!strcmp("id",ColName[i]))
        {
            msg_pack->id = atoi(argv[i]);
        }
        else if(!strcmp("phone", ColName[i]))
        {
            strcpy(msg_pack->phone,argv[i]);
        }
        else if(!strcmp("message",ColName[i]))
        {
            strcpy(msg_pack->message,argv[i]);
        }
    }
	printf("\n");
	return 0;
}

