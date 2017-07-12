#include "twi.h"

void I2C_Init (void)
{
	USART_Transmit_str("I2C_Init\n\r");
	TWBR=0x48;//скорость передачи (при 8 мгц получается 100 кгц, что и необходимо для общения с ds1307)
}


void I2C_StartCondition(void)
{
	//USART_Transmit_str("I2C_StartCondition\n\r");
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
}

void I2C_StopCondition(void)
{
	//USART_Transmit_str("I2C_StopCondition\n\r");
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void MyAlarm(int var)
{
	USART_Transmit_str("I2C_SendByte\n\r");
}


void I2C_SendByte(unsigned char c)
{
	//int t=0;
	//USART_Transmit_str("I2C_SendByte\n\r");
	TWDR = c;//запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу байта
	while (!(TWCR & (1<<TWINT)))//подождем пока установится TWIN
	{
		
	}
	
}

void I2C_SendByteByADDR(unsigned char c,unsigned char addr)
{
	//USART_Transmit_str("I2C_SendByteByADDR\n\r");
	I2C_StartCondition(); // Отправим условие START
	I2C_SendByte(addr); // Отправим в шину адрес устройства + бит чтения-записи
	I2C_SendByte(c);// Отправим байт данных
	I2C_StopCondition();// Отправим условие STOP
}

unsigned char I2C_ReadByte(void)
{
	
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}

unsigned char I2C_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}