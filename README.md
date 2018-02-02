
<<<<<<< HEAD
Njtech University

Project name: Digital Radio with STM32f103vet6

Project introduction: 

Team member: 
Liu si kun:       LCD program
Zheng zu chuang:  logic of project
Mao yun:          relate progrem of radio

Hardware:
STM32f103vet6 (based on Firebull board)
TEA5767 chip (digital radio chip iic communicate)

Software:
STM32 Firmware library 3.0
Keil Mdk 5


2017/12/24
**revised by Liu si kun** 
**********************************************************
create a template that contains api for LCD,touch screen;
write a introduction of the project
test apis
**********************************************************

//确认触控屏校准参数
Display calibration parameters:
xfac:0.136240   yfac:-0.178799  xoff:0.000000  yoff:0.000000
xfac:0.132363   yfac:-0.175659  xoff:0.000000  yoff:0.000000
xfac:0.133067   yfac:-0.183126  xoff:0.000000  yoff:0.000000 
xfac:0.130890   yfac:-0.177440  xoff:0.000000  yoff:0.000000 
xfac:0.133244   yfac:-0.172414  xoff:0.000000  yoff:0.000000 

**end**








2017/12/26
**revised by Liu si kun**
************************************************************
write a report that shows uses of GPIOS and interrupts
add spi apis
************************************************************

UASRT1
#define  DEBUG_USART_TX_GPIO_PORT       GPIOA   
#define  DEBUG_USART_TX_GPIO_PIN        GPIO_Pin_9
#define  DEBUG_USART_RX_GPIO_PORT       GPIOA
#define  DEBUG_USART_RX_GPIO_PIN        GPIO_Pin_10

#define  DEBUG_USART_IRQ                USART1_IRQn
#define  DEBUG_USART_IRQHandler         USART1_IRQHandler

LCD
//-----------------LCD端口定义---------------- 
//#define	LCD_LED PCout(10) //LCD背光    		 PC10
#define	LCD_CS	PDout(12)  //片选端口  	     PD12
#define	LCD_RS	PDout(13)  //数据/命令       PD13	   
#define	LCD_WR	PDout(14)  //写数据			 PD14
#define	LCD_RD	PDout(15)  //读数据			 PD15
								    
//PB0~15,作为数据线
#define DATAOUT(x) GPIOE->ODR=x; //数据输出	
#define DATAIN     GPIOE->IDR;   //数据输入   

Touch(spi)
//下面是SPI相关GPIO初始化//pa5,7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //通用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//下面是SPI相关GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//Configure PC6 pin: TP_CS pin 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	//Configure PC4 pin: TP_INT pin 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	//上拉输入
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
EXTI4_IRQHandler()//PC4

IIC
#define SDA_PORT        GPIOB
#define SDA_PIN         GPIO_Pin_7

#define SCL_PORT        GPIOB
#define SCL_PIN         GPIO_Pin_6

**end**




=======
Digital-Radio-STM32F103Vet6
using tea5767
>>>>>>> 78d5222acacebadcf71dfab7012e1d5ca2fa8dec
