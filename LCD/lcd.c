#include "lcd.h"

//---------------------------------------------------------------

void sendhalfbyte(unsigned char c)
{
	c<<=4;
	E1;					// Установка линия E в 1
	_delay_us(50);
	PORTD&=0b00001111;	// стираем информацию на входах дисплея
	PORTD|= c;
	E0;					// Установка линия E в 0
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
	unsigned char xx=x; unsigned yy=y; //Приравниваем объявленные переменные к исходным, дабы избежать искожения изображения в циклах.
	char adress;
	if (y==2) //Обрабатываем обращение к 3-й строке LCD
	{
		yy=0; //Переадрисуем первой строке
		xx=x+20; //Переводим с первой строки на третью
	}
	if (y==3) //Обрабатываем обращение к 4-й строке LCD
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
	_delay_ms(15); // ЖДЕМ 15 МС
	sendhalfbyte(0b00000011);
	_delay_ms(4);
	sendhalfbyte(0b00000011);
	_delay_us(100);
	sendhalfbyte(0b00000011);
	_delay_ms(1);
	sendhalfbyte(0b00000010);
	_delay_ms(1);
	sendbyte(0b00101000, 0); // ВКЛЮЧЕНИЕ 4 БИТНОГО РЕЖИМА, РАБОТАЕМ В 2 ЛИНИИ (N=1)
	_delay_ms(1);
	sendbyte(0b00001100, 0); // ВКЛЮЧАЕМ ИЗОБРАЖЕНИЕ НА ДИСПЛЕЕ (D=1) КУРСОРЫ НЕ ВКЛЮЧАЕМ
	_delay_ms(1);
	sendbyte(0b00000110, 0); // ПИШЕМ С СПРАВА НА ЛЕВО
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