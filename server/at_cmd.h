/********************************************************************************
 *      Copyright:  (C) 2020 LuXiaoyang<920916829@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  comport.h
 *    Description:  This head file of sms.c
 *
 *        Version:  1.0.0(09/07/20)
 *         Author:  LuXiaoyang <920916829@qq.com>
 *      ChangeLog:  1, Release initial version on "09/07/20 08:58:33"
 *                 
 ********************************************************************************/
#ifndef  _AT_CMD_H_
#define  _AT_CMD_H_

#include "comport.h"
#include "PDU.h"

#define CENTER_NUM_LEN 14



/* Send AT Commond(comport_send plus) */
int send_at_cmd(ComportAttr *comport,char *atcmd,char *expected_recv,char *rmsg,int msgsize,int timeout);

/* Check if the serial port can communicate */
int atcmd_CheckAt(ComportAttr *comport);

/* Check if the module can recognize the SIM card */
int atcmd_CheckSim(ComportAttr *comport);

/* Check the SIM card registration */
int atcmd_CheckCreg(ComportAttr *comport);

/* Check the SIM card signal strength */
int atcmd_CheckSignal(ComportAttr *comport);

/* check the SIM card Operators */
int atcmd_Operators(ComportAttr *comport);

/* Use the above function to check whether the SIM card is ready to be used */
int check_sim_allready(ComportAttr *comport);

/* Get SMS Center Number of the SIM Card */
int get_sms_center_number(ComportAttr *comport,char *center_number);

/* Send TEXT Message */
int text_sms_send(ComportAttr *comport,char *sms_buf,char *phone_number);

/* Send PDU message */
int pdu_sms_send(ComportAttr *comport,char *sms_buf,char *phone_number);

/*  Get the first SMS from 4g module,then delete it */
int get_module_sms(ComportAttr *comport,char *sms_buf,int sms_buf_len,char *sender_number);

/*  Delete the specified SMS */
int delete_sms(ComportAttr *comport,char *target_nember);

#endif   /*   ----- #ifndef _COMPORT_H_  ----- */

