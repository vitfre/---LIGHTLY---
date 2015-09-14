/*
 * Stroboskop.c
 *
 * Created: 15.06.2013 17:30:32
 *  Author: Pashgan
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "button.h"
#include "led.h"
#include "buzzer.h"

#define F_CPU 9600000UL
#include <util/delay.h>

#define TIM_PERIOD_MS    10UL
#define TIM_PRE          1024UL 
#define TIM_OCR_VALUE    ((TIM_PERIOD_MS*F_CPU)/(TIM_PRE*1000)-1) 

#define REG_NORMAL 0
#define REG_STROBO 1
#define LED_PROG_MASK  0x07

#define CONTR_PINX      PINB
#define CONTR_PIN       2

but_state_t button;
volatile uint8_t tim0_comp_flag;
uint8_t strob_regime;
uint8_t count_led_prog;

uint8_t strob_regime_eep EEMEM = 0;
uint8_t count_led_prog_eep EEMEM = 0;

extern uint8_t count_rep;
extern uint8_t buz_state;
extern uint8_t pin;

int main(void)
{
	/*LED_Init();
	BUZ_Init();*/
	DDRB  = (1<<LED1)|(1<<LED2)|(1<<BUZ_PIN)|(0<<BUT_NUM)|(0<<CONTR_PIN); 
	PORTB = (0<<LED1)|(0<<LED2)|(0<<BUZ_PIN)|(1<<BUT_NUM)|(0<<CONTR_PIN);

    /*моргаем светодиодами перед запуском устройства*/
    for(uint8_t i = 0; i < 4; i++){
	   LED_Toggle();
	   _delay_ms(150);
	}	
	
	
    /*загружаем начальные установки:
	 - режим
	 - последняя прога*/

	strob_regime = eeprom_read_byte(&strob_regime_eep);
	_delay_ms(500);
	count_led_prog = eeprom_read_byte(&count_led_prog_eep);
	
	if (strob_regime == REG_STROBO){
	   LED_Start(count_led_prog);
	}
	else{
		LED_On();
	}
	
    //button = BUT_NO_PRESS;
	//BUT_Init();

	/*инициализация таймера Т0. период 10мс.*/
	TCCR0A = (1<<WGM01)|(0<<WGM00);
	TCCR0B = (0<<WGM02)|(1<<CS02)|(0<<CS01)|(1<<CS00);
	OCR0A  = TIM_OCR_VALUE;
	TIMSK0 = (1<<OCIE0A);
	//tim0_comp_flag = 0;
	
	sei();
    while(1)
    {
	   if (tim0_comp_flag){
		   tim0_comp_flag = 0;
               
				   /*при появлении упр. сигнала, запускаем первый режим*/
				   if (strob_regime == REG_NORMAL){
					  if ((CONTR_PINX & (1<<CONTR_PIN))){
						 LED_Start(0);	  
					  }
					  else{
						  if (count_rep > 0){
						     LED_Stop();
						  }
					  }
				   }
			   
				   button = BUT_Debrief();

				   /*если нажатие длительное, то перекл. в другой режим*/
				   if (button == BUT_LONG_PRESS){
					   if (strob_regime){
						   strob_regime = REG_NORMAL;
						   LED_Stop();
						   BUZ_Start(0, 75);
					   }
					   else{
						   strob_regime = REG_STROBO;
						   LED_Start(count_led_prog);
						   BUZ_Start(count_led_prog, 18);
					   }
					   eeprom_write_byte(&strob_regime_eep, strob_regime);
				   }
		   
				   /*если короткое нажатие и режим стробоскопа, перекл. программу*/
				   if (button == BUT_RELEASE){
					   if (strob_regime == REG_STROBO){
						   /*cчетчик программ*/
						   count_led_prog++;
						   if (count_led_prog == LED_PROG_NUM){
							   count_led_prog = 0;
						   }
						   LED_Start(count_led_prog);
						   BUZ_Start(count_led_prog, 18);
						   eeprom_write_byte(&count_led_prog_eep, count_led_prog);
					   }
				   }

				   LED_Contr();
				   BUZ_Contr();
			   
	   }
    }
	return 0;
}

ISR(TIM0_COMPA_vect)
{
   tim0_comp_flag = 1;
}