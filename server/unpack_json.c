/*********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  unpack_json.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(12/07/20)
 *         Author:  wangruijie <1046299465@qq.com>
 *      ChangeLog:  1, Release initial version on "12/07/20 14:50:13"
 *                 
 ********************************************************************************/
#include"cJSON.h"
#include"Msg_4G_server.h"

int pack_json(char *data,char *json_buf)
{
    cJSON          *json;


    //从缓冲区中解析出JSON结构
    json= cJSON_Parse(data);

    //将传入的JSON结构转化为字符串 并打印
    strcpy(json_buf, cJSON_Print(json));

    //将JSON结构所占用的数据空间释放
    //free(json_buf);
    cJSON_Delete(json);

    return 1;
}


int unpack_json(char *buf, char *rbuf)
{

    cJSON *tnode = NULL;
    cJSON *json = cJSON_Parse(buf);
    cJSON *node = NULL;

    node = cJSON_GetObjectItem(json,"Mobile");
    if(node == NULL)
    {
        printf("Mobile node == NULL\n");
        return -1;
    }

    if(1 != cJSON_HasObjectItem(json,"Mobile"))
    {
        printf("not found Mobile node\n");
        return -1;
    }

    cJSON_ArrayForEach(tnode,node)
    {
        if(tnode->type == cJSON_String)
        {
            printf("The mobile is:%s\n",tnode->valuestring);
            strcpy(rbuf, tnode->valuestring);
        }
        else
        {
            printf("node's type is not string\n");
        }
    }

    node = cJSON_GetObjectItem(json,"中文短信");
    if(node == NULL)
    {
        printf("中文短信 node is NULL\n");
        return -2;
    }

    if(1 != cJSON_HasObjectItem(json,"中文短信"))
	{
        printf("not found 中文短信 node\n");
        return -3;
    }

    cJSON_ArrayForEach(tnode,node)
    {
        if(tnode->type == cJSON_String)
        {
            printf("The 中文短信 is:%s\n",tnode->valuestring);
        }
        else
        {
            printf("node's type is not string\n");
            return -4;
        }
    }

    node = cJSON_GetObjectItem(json,"English_SMS");
    if(node == NULL)
    {
        printf("English_SMS node is NULL\n");
        return -5;
    }

    if(1 != cJSON_HasObjectItem(json,"English_SMS"))
    {
        printf("not found English_SMS node\n");
        return -6;
    }

    cJSON_ArrayForEach(tnode,node)
    {
        if(tnode->type == cJSON_String)
        {
            printf("The English_SMS is:%s\n",tnode->valuestring);
        }
        else
        {
            printf("node's type is not string\n");
            return -4;
        }
	}

    return 1;
}
