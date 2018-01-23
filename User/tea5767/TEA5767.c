#include "stm32f10x.h"
#include "i2c.h"
#include "TEA5767.h"

/******������TEA5767оƬ����д������������1����ַ�ֽں�5�������ֽ�******/
static uint8_t tea5767_Write(const uint8_t *_ucaBuf, uint8_t _count)
{

	if (I2C_Write(TEA5767_SLAVE_ADDRESS, _ucaBuf, _count) == _count) {
		return _count;
	}
	else {
		return 0;
	}
}


/******������TEA5767оƬ���ж�����******/
static uint8_t tea5767_Read(uint8_t *_ucaBuf, uint8_t _count)
{
  
	if (I2C_Read(TEA5767_SLAVE_ADDRESS, _ucaBuf, _count) == _count) {
		return _count;
	}
	else {
		return 0;
	}
}


static uint16_t CaclPLL(uint32_t _freq)
{
	return (uint16_t)(((_freq - 225000) * 4) / 32768);
}


static uint32_t CaclFreq(uint16_t _pll)
{
	return ((uint32_t)_pll * 32768) / 4 + 225000;
}


/****��ʼ��TEA5767****/
uint8_t tea5767_Set(uint32_t _Freq, uint8_t _ucMuteEn, uint8_t _ucSerchEn, uint8_t _ucSearchUp, uint8_t _ucAdcLevel)
{
	uint8_t buf[5];
	uint16_t pll;

    /* ����/ŷ��(87.5-108M), �ձ�(76-91MHz) */
	pll = CaclPLL(_Freq);

	/*
		��1���Ĵ�����
		MUTE (bit7) = 0
		SM(bit6) = 0
	*/
	buf[0] = ((pll >> 8) & 0x3F);
	if (_ucMuteEn == MUTE_ON)
	{
		buf[0] |= (1 << 7);
	}
	if (_ucSerchEn == 1)
	{
		buf[0] |= (1 << 6);
	}
		
	/*
		��2���Ĵ�����PLL�ĵ�8λ
	*/
	buf[1] = pll;

	/*
	    ��3���Ĵ���
		SUD(bit7) = 1, ��������
		SSL(bit6 bit5) = 7  ����ֹͣ����
			00 ���������õȼ�
			01 �ͼ���ADC ��� = 5
			10 �м���ADC ��� = 7
			11 �߼���ADC ��� = 10
			
		HLSI(BIT4) = 0, �ͱߴ���Ƶע��
		MS (BIT3) = 0, ѡ��������
		MR (BIT2) = 0, Rͨ��������
		ML (BIT1) = 0, Lͨ��������
		SWP1��bit0) = 0 : ����ɱ�̶˿�
	*/
	if ((_ucAdcLevel < 1) || (_ucAdcLevel > 2))
	{
		_ucAdcLevel = 2;
	} 
	buf[2] = (2 << 5);
	if (_ucSearchUp == SEARCH_UP)
	{
		buf[2] |= (1 << 7);
	}

	/*
		��4���Ĵ���
		SWP2��bit7) = 0 : ����ɱ�̶˿�
		STBY��bit6) = 0 : ѡ��Ǵ���ģʽ
		BL (bit5) = 0, ѡ������/ŷ��Ƶ��
		XTAL(bit4) = 1�� ѡ��32768Hz����
		SMUTE(bit3) = 0, ��������ر�
		HCC(bit2) = 0, ���п��ƹ�
		SNC(bit1) = 1, ���������빦�ܴ�
		SI(bit0) = 1, swport������Ϊ������־
	*/
	buf[3] = (1 << 4) | (1 << 1) | (1 << 0);

	/*
		��5���Ĵ���
		PLLREF(BIT7) = 0, PLL��6.5MHz�ο�Ƶ�ʹر�
		DTC(bit6) = 1, ȥ����ʱ�䳣��75uS
	*/
	buf[4] = (1 << 6);

	if (tea5767_Write(buf, 5) == 5) {
		return 1;
	}
	else {
		return 0;
	}
}

/*****��ȡTEA5767оƬ��״̬*****/
uint8_t tea5767_ReadStatus(TEA5767_T *_tStatus)
{
	uint8_t buf[5];
	uint8_t ret = 0;

	if (tea5767_Read(buf, 5) == 5) {
		ret = 1;
		
		_tStatus->ucReady = (buf[0] >> 7) & 0x01;
		_tStatus->ucBandLimit = (buf[0] >> 6) & 0x01;
		_tStatus->usPll = ((buf[0] & 0x3f) << 8) + buf[1];		//PLLֵ
		_tStatus->ucStereo =  (buf[2] >> 7) & 0x01;
		_tStatus->ucIFCount = buf[2] & 0x7F;
		_tStatus->ucAdcLevel = (buf[3] >> 4) & 0x0F;

		_tStatus->ulFreq = CaclFreq(_tStatus->usPll);
	}

	return ret;
}
