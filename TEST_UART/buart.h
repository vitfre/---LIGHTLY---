/*
 * buart.h
 *
 * Created: 03.11.2013 21:32:40
 *  Author: User
 */ 

#ifndef BUART_H_
#define BUART_H_
//---------------------------------------------------------------------------------------
#define F_CPU 16000000UL // or whatever may be your frequency
//---------------------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/interrupt.h>
//---------------------------------------------------------------------------------------
#define UART_RATE		9600//142800
#define UART_BUFSIZE	16
#define UART_BUFEND		(UART_BUFSIZE-1)
//---------------------------------------------------------------------------------------
uint8_t uart_rxrd, uart_rxwr;
uint8_t uart_rx[UART_BUFSIZE];
uint8_t uart_txrd, uart_txwr;
uint8_t uart_tx[UART_BUFSIZE];
//---------------------------------------------------------------------------------------
void uart_init();
uint8_t uart_rx_count();
uint8_t uart_read();
void uart_write(uint8_t byte);
//---------------------------------------------------------------------------------------
#endif /* BUART_H_ */