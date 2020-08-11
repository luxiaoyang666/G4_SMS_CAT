/*********************************************************************************
 *      Copyright:  (C) 2020 LuXiaoyang<920916829@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  MD5.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(30/07/20)
 *         Author:  LuXiaoyang <920916829@qq.com>
 *      ChangeLog:  1, Release initial version on "30/07/20 09:34:32"
 *                 
 ********************************************************************************/
#include "MD5.h"


/* MD5加密 */
void md5_encryption(const char *unencrypted_buf,int unencrypted_buf_len,char *encrypted_buf,int encrypted_buf_size)
{

    MD5_CTX               Md5Ctx;
  

    MD5_Init(&Md5Ctx);  //初始化

    MD5_Update(&Md5Ctx, (unsigned char *)encrypted_buf, unencrypted_buf_len); //md5加密

    /* 获取加密后的密文 */
    MD5_Final(encrypted_buf, &Md5Ctx);

}

/* 登录验证 */
int login_check(CLType *head,char *client_ciphertext)
{

    char            unencrypted_temp_buf[256] = {0};
    char            encrypted_temp_buf[256] = {0};

    CLType         *htemp = head;

    while(htemp)
    {
        memset(unencrypted_temp_buf,0,sizeof(unencrypted_temp_buf));
        memset(encrypted_temp_buf,0,sizeof(encrypted_temp_buf));

        strncpy(unencrypted_temp_buf,htemp->nodeData.login_name,sizeof(unencrypted_temp_buf));
        strncat(unencrypted_temp_buf,htemp->nodeData.login_passwd,sizeof(unencrypted_temp_buf) - strlen(unencrypted_temp_buf));

        md5_encryption(unencrypted_temp_buf,strlen(unencrypted_temp_buf),encrypted_temp_buf,sizeof(encrypted_temp_buf));

        if(!strcmp(encrypted_temp_buf,client_ciphertext))
        {
            printf("Verified successfully!\n");
            return 0;
        }

        else 
            htemp = htemp -> nextNode;
    }

    printf("verification failed!\n");

    return -1;
}



