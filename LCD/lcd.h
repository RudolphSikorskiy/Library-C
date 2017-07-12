#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define E1	PORTD|=0b00001000
#define E0	PORTD&=0b11110111
#define RS1	PORTD|=0b00000100
#define RS0 PORTD&=0b11111011

void LCD_ini(void);
void clearlcd(void);
void sendchar(unsigned char c);
void setpos(unsigned char x, unsigned y);
void str_lcd(char str1[]);





#endif /* LCD_H_ */