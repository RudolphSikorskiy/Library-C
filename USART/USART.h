#ifndef USART_H_
#define USART_H_

#include "main.h"

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
void USART_Transmit_str(char str1[]);



#endif /* USART_H_ */