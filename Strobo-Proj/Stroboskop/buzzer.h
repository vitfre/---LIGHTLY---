#ifndef BUZZER_H 
#define BUZZER_H

#include <avr/io.h>
#include <stdint.h>

#define BUZ_PORTX   PORTB
#define BUZ_DDRX    DDRB
#define BUZ_PIN     0

#define BUZ_Init()  do{	BUZ_DDRX |= (1<<BUZ_PIN); BUZ_PORTX &= ~(1<<BUZ_PIN); }while(0)

void BUZ_Start(uint8_t num, uint8_t dur);
void BUZ_Contr(void);
//void BUZ_Sound(void);




#endif //BUZZER_H