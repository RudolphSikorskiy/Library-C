#include "SoftUART.h"
#define BufLEN 80

uint8_t n=0;						// ������ ������
char instr[BufLEN];				// ����� ������
uint8_t Ok[] = "OK!";				// ����� ������
char* SN =		"????";
char* PPB =		"????";
char* TEMP =	"????";
char* HYDR =	"????";
int trigger = 0;
float mg = 0;
int ppb =0;
int tmp =0;

//--------------------------------------------------------------------------------------------//

ISR(INT0_vect)
{
	GICR&=~(1<<6);						//��������� ���������� �� INT0
	MCUCR&=~(1<<1);						//��������� ���������� �� ������������ ������ ������� �� INT0  MLN/BTREIT/2
	_delay_us(MLN/BTREIT/2);
	if (!CheckBit(PIND,RX_PIN))			//n=PIND&(1<<RX_PIN);
	{
		uint8_t x = SOFT_UART_read();
		instr[n] = x;
		//USART_Transmit(x);
		n++;
		
		if(n>BufLEN) n=0;					//�������� ����������� �������
	}
	
	//-----------------------------------------------------------------------------------------------------//
	
	
	
	//-----------------------------------------------------------------------------------------------------//
	
	GICR|=(1<<6);						//��������� ���������� �� INT0
	MCUCR|=(1<<1);						//���������� �� ������������ ������ ������� �� INT0
}

//--------------------------------------------------------------------------------------------//

void SOFT_UART_byte( char a)			// �������� �����
{
	SOFT_UART_bit(0x00);//start bit
	for (int i = 0; i < 8; i++)
	{
		if ((a >> i) & 0x01)
		{
			SOFT_UART_bit(0x01);//data bit
		}
		else
		{
			SOFT_UART_bit(0x00);//data bit
		}
	}
	SOFT_UART_bit(0x01);//stop bit
}

//--------------------------------------------------------------------------------------------//

void SOFT_UART_init(void)					// ������������� ����������� �����
{
	DDRD |=(1<<TX_PIN);
	PORTD |=(1<<TX_PIN);
	DDRD &= ~(1<<RX_PIN);
	GICR|=(1<<6);   //��������� ���������� �� INT0
	MCUCR|=(1<<1); //���������� �� ������������ ������ ������� �� INT0

}

//--------------------------------------------------------------------------------------------//

void SOFT_UART_bit(char b)			//�������� ����
{
	if (b == 0x00)
	{
		PORTD &= ~(1<<TX_PIN);
	}
	_delay_us(MLN/BTREIT);
	PORTD |= (1<<TX_PIN);
}

//--------------------------------------------------------------------------------------------//

void SOFT_UART_send( char *str)		//�������� �����
{
	unsigned char i=0;
	while (str[i])
	{
		SOFT_UART_byte(str[i++]);
	}
}

//--------------------------------------------------------------------------------------------//

unsigned char SOFT_UART_read(void)			// ����� ������
{
	char i;
	unsigned char ch=0;
	for(i=0;i<8;i++)
	{
		_delay_us(MLN/BTREIT);
		if(CheckBit(PIND,RX_PIN)) ch|= 1<<i;
	}
	return ch;


}

//--------------------------------------------------------------------------------------------//

void ReturnInSTR(void)
{
	SOFT_UART_byte(' ');					// �������� ������� ������
	
	
//-----------------------------------------------------------------------------------------------------//

char *pch = strtok (instr," ,"); //�� ������ ��������� ������� ����������� (������, �������, �����)
while (trigger != 4) //���� ���� ������� pch !== NULL � ������ ��������� ������ 4
{
	
	switch ( trigger )
	{
		case 0:
		SN = pch;
		pch = strtok (NULL, " ,");
		trigger++;
		break;
		case 1:
		PPB = pch;
		pch = strtok (NULL, " ,");
		trigger++;
		break;
		case 2:
		TEMP = pch;
		pch = strtok (NULL, " ,");
		trigger++;
		break;
		case 3:
		HYDR = pch;
		pch = strtok (NULL, " ,");
		trigger++;
		break;
		
		
		default: break;
		
	}
	
}
trigger = 0;


//-----------------------------------------------------------------------------------------------------//	
	USART_Transmit_str(SN);
	USART_Transmit('\r');
	USART_Transmit_str(PPB);
	USART_Transmit('\r');
	USART_Transmit_str(TEMP);
	USART_Transmit('\r');
	USART_Transmit_str(HYDR);
	USART_Transmit('\r');
	
	/*if(n)
	{
		instr[n]=0;
		SOFT_UART_send(instr);
		//UART_byte(n);
		instr[0]=0;
		n=0;
	}*/
	
	//USART_Transmit_str(SN);
	
	/*for(int i = 0; i < BufLEN ;i++ )
	{
		instr[i] = 0;
	}*/
	n=0;
	
}

//--------------------------------------------------------------------------------------------//