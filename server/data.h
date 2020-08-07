/********************************************************************************
 *      Copyright:  (C) 2020 lixinlei<596447615@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  data.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(2020年07月19日)
 *         Author:  lixinlei <596447615@qq.com>
 *      ChangeLog:  1, Release initial version on "2020年07月19日 19时31分01秒"
 *                 
 *******************************************************************************/
#ifndef DATA_H_
#define DATA_H_


typedef struct msg_pack_st{
     int      id;
     char     phone[BUFFER_SIZE];
     char     message[BUFFER_SIZE];
}msg_pack_t;

#endif

