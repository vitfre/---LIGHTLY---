#include "buzzer.h"

volatile uint8_t buz_state;
volatile uint8_t pin;
static uint8_t duration, duration_buf;
static uint8_t cycle;


void BUZ_Start(uint8_t num, uint8_t dur)
{
   //pin = 1;	
   BUZ_PORTX |= (1<<BUZ_PIN);
   cycle = (num + 1)<<1;	
   duration_buf = dur;
   duration = dur;
   buz_state = 1;
}


/*void BUZ_Sound(void)
{
	if (buz_state){
			if (pin){
				BUZ_PORTX ^= (1<<BUZ_PIN);
			}
			else{
				BUZ_PORTX &= ~(1<<BUZ_PIN);
			}
	}
}*/

void BUZ_Contr(void)
{
	if (buz_state){
		duration--;
		if (!duration){
		      duration = duration_buf;
		      BUZ_PORTX ^= (1<<BUZ_PIN);
			  //pin ^= 1;
     		  cycle--;
			  if (!cycle){
			     buz_state = 0;
				 BUZ_PORTX &= ~(1<<BUZ_PIN); 
			  }
		   	
		}	
	}
}