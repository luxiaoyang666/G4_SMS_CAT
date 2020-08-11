/********************************************************************************
 *      Copyright:  (C) 2020 LuXiaoyang<920916829@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  MD5.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(30/07/20)
 *         Author:  LuXiaoyang <920916829@qq.com>
 *      ChangeLog:  1, Release initial version on "30/07/20 08:38:37"
 *                 
 ********************************************************************************/
#ifndef _MD5_H_
#define _MD5_H_ 

#include "g4_sms_cat_main.h"
#include "usrinfo_list.h"
 

/* MD5加密 */
void md5_encryption(const char *unencrypted_buf,int unencrypted_buf_len,char *encrypted_buf,int encrypted_buf_size);

/* 登录验证 */
int login_check(CLType *head,char *client_ciphertext);

#endif
