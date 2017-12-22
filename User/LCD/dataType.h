/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**                                      
**                                 http://www.embedtools.com
**
**------File Info-----------------------------------------------------------------------------------------
** File name:               dataType.h
** Latest modified Date:    2008-07-24
** Latest Version:          1.0
** Descriptions:            ���峣�õ��������ͼ���������ֵ  Designed for ARM (32bit processor)
**
**--------------------------------------------------------------------------------------------------------
** Created by:              ��չ��
** Created date:            2008-07-24
** Version:                 1.0
** Descriptions:            
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/


#ifndef __GENERAL_DATA_TYPE_H
#define __GENERAL_DATA_TYPE_H
/*********************************************************************************************************
** ������������޹ص���������
*********************************************************************************************************/
#ifndef INT8U
#define INT8U  unsigned char                                            /* �޷���8λ���ͱ���            */
#endif
#ifndef INT8S
#define INT8S  signed char                                              /* �з���8λ���ͱ���            */
#endif
#ifndef INT16U
#define INT16U unsigned short                                           /* �޷���16λ���ͱ���           */
#endif
#ifndef INT16S
#define INT16S signed short                                             /* �з���16λ���ͱ���           */
#endif
#ifndef INT32U
#define INT32U unsigned long                                             /* �޷���32λ���ͱ���           */
#endif
#ifndef INT32S
#define INT32S signed long                                               /* �з���32λ���ͱ���           */
#endif
#ifndef FP32
#define FP32   float                                                    /* �����ȸ�������32λ���ȣ�     */
#endif
#ifndef FP64
#define FP64   double                                                   /* ˫���ȸ�������64λ���ȣ�     */
#endif
#ifndef BOOLEAN
#define BOOLEAN unsigned char                                           /* ��������                     */
#endif
#ifndef boolean
#define boolean BOOLEAN                                                 /* ��������                     */
#endif
#ifndef uchar
#define uchar   unsigned char
#endif
#ifndef uint
#define uint    unsigned int 
#endif

/*********************************************************************************************************
** ���峣�÷���ֵ
*********************************************************************************************************/
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#endif
