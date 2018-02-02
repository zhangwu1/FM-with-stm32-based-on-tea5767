#ifndef _BSP_TEA5767_H
#define _BSP_TEA5767_H

#include "i2c.h"

#define TEA5767_SLAVE_ADDRESS    0xC0

#define FM_FREQ_INIT	87500000	

#define FM_FREQ_MIN		87500000	
#define FM_FREQ_MAX		108000000	
#define FREQ_STEP			100000		/* 0.1MHz = 100000KHz */
#define FM_ADC_LEVEL ADC_LEVEL_7		/* ����ֹͣ�ȼ�����Ϊ7 */

#define HLSI 0//��λע��
#define MS 0//������
#define BL 0//us/eurpel band
#define XTAL 1
#define PLLREF 0//fref 32.768Khz
enum
{
	MUTE_OFF = 0,
	MUTE_ON = 1
};

enum
{
	SEARCH_OFF = 0,
	SEARCH_ON = 1
};

enum
{
	SEARCH_DOWN = 0,
	SEARCH_UP = 1
};
/* ������Ƶ�ʵ��ź��������� */
enum
{
	ADC_LEVEL_5 = 1,
	ADC_LEVEL_7 = 2,
	ADC_LEVEL_10 = 3
};
//Ŀǰ״̬
enum
{
	standby=0,
	loading=1,
	saving=2,
	searching=3
};

/* ����һ��TEA5767�ṹ�� */
typedef struct
{
	uint8_t ucReady;				/* ׼���ñ�־��1��һ��Ƶ�����ѵ�����һ����ʽ�Ѿ����ϣ�0û��Ƶ�����ѵ� */
	uint8_t ucBandLimit;			/* ���μ��ޱ�־�� 1�ﵽƵ������ */
	uint16_t usPll;					/* ��ǰ�ѵ�Ƶ�ʵ�PLLֵ */
	uint8_t ucStereo;				/* ��������־λ��1����������  0���������� */
	uint8_t ucIFCount;				/* ��Ƶ�������������ȷ��гʱֵ��31H��3EH֮�� */
	uint8_t ucAdcLevel;				/* ADC������𣬼��ź������ļ��� */
	uint32_t ulFreq;				/* Ƶ�� */
	uint8_t Fr_searched;      /*�������ѵ�Ƶ��*/
	uint8_t cur_statue;          /*Ŀǰ״�� */
}TEA5767_T;

uint8_t tea5767_Set(uint32_t _Freq, uint8_t _ucMuteEn, uint8_t _ucSerchEn, uint8_t _ucSearchUp, uint8_t _ucAdcLevel);
uint8_t tea5767_ReadStatus(TEA5767_T *_tStatus);

#endif
