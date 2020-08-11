/********************************************************************************
 *      Copyright:  (C) 2020 LuXiaoyang<920916829@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  UserInfo_List.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(22/07/20)
 *         Author:  LuXiaoyang <920916829@qq.com>
 *      ChangeLog:  1, Release initial version on "22/07/20 08:55:07"
 *                 
 ********************************************************************************/
#ifndef  _USRINFO_LIST_H_
#define  _USRINFO_LIST_H_



#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct _st_UserInfo
{
    char    login_name[32];
    char    login_passwd[32];
    char    target_number[32];
    int     authority;
    int     client_fd;
}UserInfo;

typedef struct _st_Node
{
    UserInfo          nodeData;
    struct _st_Node   *nextNode;
}CLType;


void InsertNode(CLType **head,UserInfo nodeData);   //尾插法

void InitList(CLType **head);
    
//int login_check(CLType *head,char *input_name,char *input_passwd,char *phone_number,int input_fd);   //按关键字查找结点

CLType *FindNode(CLType *head,char *username);

void print_list(CLType *head);


    

#endif   /*  ----- #ifndef _USRINFO_LIST_H_  ----- */

