#include "lcd.h"

//---------------------------------------------------------------

void sendhalfbyte(unsigned char c)
{
	c<<=4;
	E1;					// ��������� ����� E � 1
	_delay_us(50);
	PORTD&=0b00001111;	// ������� ���������� �� ������ �������
	PORTD|= c;
	E0;					// ��������� ����� E � 0
	_delay_us(50);
	
}

//---------------------------------------------------------------

void sendbyte(unsigned char c,unsigned char mode)
{
	
	if (mode==0)
	{
		RS0;
	}
	else
	{
		RS1;
	}
	unsigned char hc = 0;
	hc = c>>4;
	sendhalfbyte(hc);
	sendhalfbyte(c);
	
}

//---------------------------------------------------------------

void setpos(unsigned char x, unsigned y)
{
	unsigned char xx=x; unsigned yy=y; //������������ ����������� ���������� � ��������, ���� �������� ��������� ����������� � ������.
	char adress;
	if (y==2) //������������ ��������� � 3-� ������ LCD
	{
		yy=0; //������������ ������ ������
		xx=x+20; //��������� � ������ ������ �� ������
	}
	if (y==3) //������������ ��������� � 4-� ������ LCD
	{
		yy=1;
		xx=x+20;
	}
	adress=(0x40*yy+xx)|0b10000000; //adress=(0x40*y+x)|0b10000000
	sendbyte(adress, 0);
}

//---------------------------------------------------------------

void sendchar(unsigned char c)
{
	sendbyte(c,1);
}

//---------------------------------------------------------------

void clearlcd(void)
{
	sendbyte(0b00000001, 0);
	_delay_us(1500);
}

//---------------------------------------------------------------

void LCD_ini()
{
	_delay_ms(15); // ���� 15 ��
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0); // ��������� 4 ������� ������, �������� � 2 ����� (N=1)
	_delay_ms(1);
	sendbyte(0b00001100, 0); // �������� ����������� �� ������� (D=1) ������� �� ��������
	_delay_ms(1);
	sendbyte(0b00000110, 0); // ����� � ������ �� ����
	_delay_ms(1);
	clearlcd();
	
}

//---------------------------------------------------------------

void str_lcd(char str1[])
{
	int_farptr_t n;
	for (n=0;str1[n]!='\0';n++)
	{
		sendchar(str1[n]);
	}
}

//---------------------------------------------------------------