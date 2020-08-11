/*********************************************************************************
 *      Copyright:  (C) 2020 Xiao yang IoT System Studio
 *                  All rights reserved.
 *
 *       Filename:  claddend.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/23/2020)
 *         Author:  Lu Xiaoyang <920916829@qq.com>
 *      ChangeLog:  1, Release initial version on "03/23/2020 02:14:27 AM"
 *                 
 ********************************************************************************/
#include "usrinfo_list.h"


void InsertNode(CLType **head,UserInfo nodeData)   //尾插法
{
    CLType   *node;
    CLType   *htemp;

    if((node = (CLType *)malloc(sizeof(CLType))) == NULL)
    {
        perror("malloc failure");
        return;
    }

    else 
    {
        node->nodeData = nodeData;
        node->nextNode = NULL;

        if(*head == NULL)
        {
            *head = node;
            return;
        }

        htemp = *head;

        while(htemp->nextNode != NULL)
        {
            htemp = htemp->nextNode;
        }

        htemp->nextNode = node;

        return;
        
    }
}

void InitList(CLType **head)
{
    UserInfo  user1;
    UserInfo  user2;
    UserInfo  user3;
    UserInfo  user4;
    UserInfo  user5;

    memset(&user1,0,sizeof(UserInfo));
    memset(&user2,0,sizeof(UserInfo));
    memset(&user3,0,sizeof(UserInfo));
    memset(&user4,0,sizeof(UserInfo));
    memset(&user5,0,sizeof(UserInfo));

 
    strcpy(user1.login_name,"root");
    strcpy(user1.login_passwd,"12345");

    strcpy(user2.login_name,"lxy");
    strcpy(user2.login_passwd,"12345");

    strcpy(user3.login_name,"lxl");
    strcpy(user3.login_passwd,"12345");

    strcpy(user4.login_name,"wrj");
    strcpy(user4.login_passwd,"12345");

    strcpy(user5.login_name,"gwx");
    strcpy(user5.login_passwd,"12345");

    user1.client_fd = -1;
    user1.authority = 1;
    user2.client_fd = -1;
    user2.authority = 0;
    user3.client_fd = -1;
    user3.authority = 0;
    user4.client_fd = -1;
    user4.authority = 0;
    user5.client_fd = -1;
    user5.authority = 0;


    InsertNode(head,user1);
    InsertNode(head,user2);
    InsertNode(head,user3);
    InsertNode(head,user4);
    InsertNode(head,user5);

}
    
CLType *FindNode(CLType *head,char *username)   //按关键字查找结点
{
    CLType *htemp = head;

    while(htemp)
    {
        if(strcmp(htemp->nodeData.login_name,username) == 0) //查找关键字
        {
            return htemp;
        }

        htemp = htemp->nextNode;     //处理下一个结点
    }

    return NULL;
}
/* 
int login_check(CLType *head,char *input_name,char *input_passwd,char *phone_number,int input_fd)   //按关键字查找结点
{
    CLType  *htemp = head;

    while(htemp)
    {
        if(strcmp(input_name,htemp->nodeData.login_name) == 0)
        {
            if(strcmp(input_passwd,htemp->nodeData.login_passwd) == 0)
            {
                printf("Login verification succeeded\n");
                strcpy(htemp->nodeData.target_number,phone_number);
                htemp->nodeData.client_fd = input_fd;
                return 0;
            }
            else 
            {
                printf("Wrong password\n");
                return -1;
            }
        }

        htemp = htemp -> nextNode;
    }

    printf("Unrecognized login name\n");

    return -2;
}
*/

void print_list(CLType *head)
{
    CLType   *htemp = head;

    while(htemp)
    {
        printf("login_name:%s  login_passwd:%s  target_number:%s  client_fd:%d\n",htemp->nodeData.login_name,htemp->nodeData.login_passwd,htemp->nodeData.target_number,htemp->nodeData.client_fd);

        htemp = htemp -> nextNode;
    }
}

