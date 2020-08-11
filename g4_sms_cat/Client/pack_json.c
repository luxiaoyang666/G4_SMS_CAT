/*********************************************************************************
 *      Copyright:  (C) 2020 Juan
 *                  All rights reserved.
 *
 *       Filename:  JSON.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(12/07/20)
 *         Author:  wangruijie <1046299465@qq.com>
 *      ChangeLog:  1, Release initial version on "12/07/20 04:11:31"
 *                 
 ********************************************************************************/
#include<stdio.h>
#include<string.h>
#include"cJSON.h"
#include<stdlib.h>
#include"g4_sms_cat_main.h"

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

