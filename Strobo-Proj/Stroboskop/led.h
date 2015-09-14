#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <stdint.h>
#include <avr/pgmspace.h>

#define LED_PORTX PORTB
#define LED_DDRX  DDRB
#define LED1     3
#define LED2     4

#define LED_PROG_NUM 7

#define LED_On()      do{LED_PORTX |= (1<<LED1)|(1<<LED2); }while(0)
#define LED_Off()     do{LED_PORTX &= ~((1<<LED1)|(1<<LED2));}while(0)
#define LED_Toggle()  do{LED_PORTX ^= (1<<LED1)|(1<<LED2); }while(0)
#define LED_Init()    do{LED_DDRX |= (1<<LED1)|(1<<LED2); LED_PORTX &= ~((1<<LED1)|(1<<LED2));}while(0)
	
void LED_Start(uint8_t num);
void LED_Contr(void);
void LED_Stop(void);


#endif //LED_H