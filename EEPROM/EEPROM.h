/*
 * EEPROM.h
 *
 * Created: 02.05.2017 9:23:22
 *  Author: N
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "main.h"

void EEPROM_write			(unsigned int uiAddress, unsigned char ucData);		// write byte
void EEPROM_write_word		(unsigned int uiAddress, uint16_t ucData);			// write 2xbyte
void EEPROM_write_dword		(unsigned int uiAddress, uint32_t ucData);			// write 4õ-bite size
void EEPROM_write_string	(unsigned int uiAddress, char str1[]);				// write string

unsigned char	EEPROM_read			(unsigned int uiAddress);							// read byte
uint16_t		EEPROM_read_word	(unsigned int uiAddress);							// read 2xbyte
uint32_t		EEPROM_read_dword	(unsigned int uiAddress);							// read 4õ-bite size
const char*		EEPROM_read_string	(unsigned int uiAddress, unsigned int sz);			// read string
#endif /* EEPROM_H_ */