/*
 * EEPROM.h
 *
 * Created: 02.05.2017 9:23:22
 *  Author: N
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"

void EEPROM_write			(unsigned int uiAddress, unsigned char ucData);			// write dyte
void EEPROM_write_word		(unsigned int uiAddress, uint16_t ucData);			// write 2xbyte
void EEPROM_write_dword		(unsigned int uiAddress, uint32_t ucData);			//����� 4�-������� ��������
void EEPROM_write_string	(unsigned int uiAddress, char str1[]);				//����� ������

unsigned char	EEPROM_read			(unsigned int uiAddress);							// read byte
uint16_t		EEPROM_read_word	(unsigned int uiAddress);							//������ 2�-������� ��������
uint32_t		EEPROM_read_dword	(unsigned int uiAddress);							//������ 4�-������� ��������
const char*		EEPROM_read_string	(unsigned int uiAddress, unsigned int sz);	//������ ������
#endif /* EEPROM_H_ */