/********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  sql.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 19时20分26秒"
 *                 
 ********************************************************************************/

#ifndef SQL_H_
#define SQL_H_ 

#include "client_main.h"
#include "sqlite3.h"
#include "data.h"


int sql_open(sqlite3 **db);
int sql_insert(sqlite3 *db,msg_pack_t msg_pack);
int sql_close(sqlite3 *db);
int delete_data(sqlite3 *db,int id,int cmd);
int get_counts(sqlite3 *db);
int get_data(sqlite3 *db,msg_pack_t *p);

#endif
