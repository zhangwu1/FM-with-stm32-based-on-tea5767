#ifndef __I2C_H
#define __I2C_H

#include "stm32f10x.h"

//SDA(PB11)?SCL(PB10)
#define SDA_PORT        GPIOB 
#define SDA_RCC_PERIPH  RCC_APB2Periph_GPIOB
#define SDA_PIN         GPIO_Pin_7
#define SET_SDA_LOW     GPIO_ResetBits(SDA_PORT, SDA_PIN)
#define SET_SDA_HIGH    GPIO_SetBits(SDA_PORT, SDA_PIN)
#define GET_SDA_PIN     GPIO_ReadInputDataBit(SDA_PORT, SDA_PIN)

#define SCL_PORT        GPIOB 
#define SCL_RCC_PERIPH  RCC_APB2Periph_GPIOB
#define SCL_PIN         GPIO_Pin_6
#define SET_SCL_LOW     GPIO_ResetBits(SCL_PORT, SCL_PIN)
#define SET_SCL_HIGH    GPIO_SetBits(SCL_PORT, SCL_PIN)
#define GET_SCL_PIN     GPIO_ReadInputDataBit(SCL_PORT, SCL_PIN)


void I2C_Config(void);

uint8_t I2C_Read(uint8_t Address, uint8_t * pbuffer, uint8_t num);
uint8_t I2C_Write(uint8_t Address, const uint8_t * pbuffer, uint8_t num);

void I2C_StartCondition(void);
void I2C_StopCondition(void);
void I2C_SendByte(uint8_t Data);
uint8_t I2C_SendAddress(uint8_t Address, uint8_t flag_rw);
uint8_t I2C_TestAck(void);
uint8_t I2C_ReceiveByte(void);
void I2C_SendAck(void);


#endif
