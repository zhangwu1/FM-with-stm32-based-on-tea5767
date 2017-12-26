#include "i2c.h"
#include "Delay.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define THALF           2
#define THIGH           2 * THALF 
#define ER_NODEVICE     0x0FF
#define ER_NOACK        0x0FE
#define NO_ER           0
#define I2CWRITE        0
#define I2CREAD         1

void I2C_StartCondition(void);
void I2C_StopCondition(void);
void I2C_SendByte(uint8_t Data);
uint8_t I2C_SendAddress(uint8_t Address, uint8_t flag_rw);
uint8_t I2C_TestAck(void);
uint8_t I2C_ReceiveByte(void);
void I2C_SendAck(void);

/****I2C端口配置****/
void I2C_Config(void) {

	
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(SDA_RCC_PERIPH | SCL_RCC_PERIPH, ENABLE);  /* 打开GPIOB时钟*/

    GPIO_InitStructure.GPIO_Pin = SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	  /* 设置SDA(PB11)为开漏输出 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SDA_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;	   /* 设置SCL(PB10)为开漏输出 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SCL_PORT, &GPIO_InitStructure);
}

/*****主机产生I2C起始条件*****/
void I2C_StartCondition(void) {

    SET_SCL_HIGH;
    SET_SDA_HIGH;
    delay_us(THALF);
    SET_SDA_LOW;
    delay_us(THALF);
}

/****主机产生I2C停止条件****/
void I2C_StopCondition(void) {

    SET_SCL_LOW;
    delay_us(THALF);
    SET_SDA_LOW;
    delay_us(THALF);
    SET_SCL_HIGH;
    delay_us(THALF);
    SET_SDA_HIGH;
    delay_us(THALF);
}


/*****主机向从机发送数据*****/
void I2C_SendByte(uint8_t Data) {

    uint8_t i;

    for(i = 0; i < 8; i++){
        SET_SCL_LOW;
        delay_us(THALF);
        if(Data & 0x80)         //Send MSB first
            SET_SDA_HIGH;
        else
            SET_SDA_LOW;
        delay_us(THALF);
        SET_SCL_HIGH;
        delay_us(THIGH);
        Data = Data << 1;       //Send from MSB to LSB
    }

}


/***主机发送寻址字节SLA(7位器件地址 + 1位数据传送方向位(r/w))***/
uint8_t I2C_SendAddress(uint8_t Address, uint8_t flag_rw) {

    uint8_t  flag_ack = 0;
    uint8_t  counter = 0;

    if(flag_rw == I2CWRITE)
        I2C_SendByte(Address & 0x0FE);
    else
        I2C_SendByte(Address | 0x01);
    //在第9个时钟周期检测ACK信号
    SET_SCL_LOW;
    delay_us(THALF);
    SET_SDA_HIGH;
    delay_us(THALF);
    SET_SCL_HIGH;

    while(counter < THIGH) {
        if(GET_SDA_PIN == 0)
            flag_ack = 1;
        delay_us(1);
        counter++;
    }
    if(flag_ack != 1) 
        return ER_NODEVICE;
    else 
        return NO_ER;
}


/**** 检测应答信号****/
uint8_t I2C_TestAck(void) {

    uint8_t  flag_ack = 0;
    uint8_t  counter = 0;

    //在第9个时钟周期检测ACK信号
    SET_SCL_LOW;
    delay_us(THALF);
    SET_SDA_HIGH;
    delay_us(THALF);
    SET_SCL_HIGH;
    
    while(counter < THIGH) {
        if(GET_SDA_PIN == 0)
            flag_ack = 1;
        delay_us(1);
        counter++;
    }

    if(flag_ack != 1)
        return ER_NOACK;
    else
        return NO_ER;
}


/*****主机接收从机发送过来的数据*****/
uint8_t I2C_ReceiveByte(void) {

    uint8_t i;
    uint8_t data;

    for(i = 0; i < 8; i++){
        SET_SCL_LOW;
        delay_us(THALF);
        SET_SDA_HIGH;
        delay_us(THALF);
        SET_SCL_HIGH;
        delay_us(THALF);
        data = data << 1;       //Receive from MSB to LSB
        if(GET_SDA_PIN)         //Receive begin from MSB
            data |= 0x01;
        else
            data &= 0xFE;
        delay_us(THALF);
    }
    return data;
}


/*****发送应答信号*****/
void I2C_SendAck(void) {

    //在第9个时钟周期发送ACK信号
    SET_SCL_LOW;
    delay_us(THALF);
    SET_SDA_LOW;
    delay_us(THALF);
    SET_SCL_HIGH;
    delay_us(THIGH);
}




uint8_t I2C_Read(uint8_t Address, uint8_t * pbuffer, uint8_t num) {

    uint8_t i;

    I2C_StartCondition();
    if(I2C_SendAddress(Address, I2CREAD) == ER_NODEVICE)
        return 0;
   
    for(i = 0; i < num; i++) {
        *(pbuffer + i) = I2C_ReceiveByte();
        I2C_SendAck();
    }
    
    I2C_StopCondition();
    return num;
}



uint8_t I2C_Write(uint8_t Address, const uint8_t * pbuffer, uint8_t num) {

    uint8_t i;

    I2C_StartCondition();
    if(I2C_SendAddress(Address, I2CWRITE) == ER_NODEVICE)
        return 0;
  
    for(i = 0; i < num; i++) {
        I2C_SendByte(*(pbuffer + i));
        if(I2C_TestAck() == ER_NOACK)
            return i;
    }
    
    I2C_StopCondition();
    return num;
}


