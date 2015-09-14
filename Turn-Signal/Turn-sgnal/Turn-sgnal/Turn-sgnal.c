/*
 * Turn_sgnal.c
 *
 * Created: 21.07.2013 3:39:11
 *  Author: Pashgan
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 128000UL
#include <util/delay.h>

/*дополнительные типы данных*/
typedef enum dev_state {
	STATE_EMPTY, 
	STATE_NORMAL, 
	STATE_LEFT_TURN, 
	STATE_RIGHT_TURN, 
	STATE_THANK, 
	STATE_ALARM,
	STATE_LED_ON,
	STATE_LED_OFF	
	} dev_state_t;
	
typedef enum but_state {BUT_NO_PRESS, BUT_PRESSED, BUT_RELEASE, BUT_LONG_PRESS, BUT_RELEASE_LONG} but_state_t;
typedef enum stimer_state {STIM_IDLE, STIM_WORKS, STIM_EXPIRED} stim_state_t;

typedef struct buttons{
	   uint8_t pin;
	   uint16_t count;
	   but_state_t buf;
	} buttons_t;	


#define TIM_PERIOD_MS    2
#define TIM_PRE          8UL
#define TIM_OCR_VALUE    (TIM_PERIOD_MS*(F_CPU/(TIM_PRE*1000))-1)

/*пины микроконтроллера*/
#define BUT_LEFT      2
#define BUT_RIGHT     1
#define BUT_CONTR     0
#define LEFT_SIGNAL   3
#define RIGHT_SIGNAL  4

#define BUT_THRESHOLD      5
#define BUT_LONG_THRESHOLD 500
#define BUT_COUNT_MAX      520


#define LED_OffAll()      PORTB &= ~((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL))

/*#define LED_Off(x)        PORTB &= ~(1<<(x))
#define LED_On(x)         PORTB |= (1<<(x))
#define LED_OnAll()       PORTB |= ((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL))
#define LED_Toggle(x)     PORTB ^= (1<<(x))
#define LED_ToggleAll()   PORTB ^= ((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL))*/

#define PIN_Check(x)      ((PINB & (1<<(x)))) 
#define STIM_Set(x)       do{cli(); soft_timer_state = STIM_WORKS; soft_timer_count = x; sei(); }while(0)
#define STIM_Check(x)      (soft_timer_state == x)
#define STIM_Stop()       do{soft_timer_state = STIM_IDLE; }while(0)

#define LED_BLINK_PERIOD    150

/*количество морганий*/
#define LED_BLINK_ONE          1 
#define LED_BLINK_SHORT_TURN   3
#define LED_BLINK_THANK        3
#define LED_BLINK_INFINITY     255


/*флаг таймера*/
volatile uint8_t tim0_comp_flag = 0;

/*программный таймер*/
volatile uint8_t soft_timer_count = 0;
volatile stim_state_t soft_timer_state = STIM_IDLE;


/*состо€ние кнопок и устройства*/
but_state_t  but_left_state = BUT_NO_PRESS;
but_state_t  but_right_state = BUT_NO_PRESS;
but_state_t  but_contr_state = BUT_NO_PRESS;
dev_state_t  dev_cur_state = STATE_NORMAL;
dev_state_t  led_state = STATE_NORMAL;

/*объ€вл€ем кнопки и инициализируем их*/
buttons_t but_left  = {BUT_LEFT,  0, BUT_NO_PRESS};
buttons_t but_right = {BUT_RIGHT, 0, BUT_NO_PRESS};
buttons_t but_contr = {BUT_CONTR, 0, BUT_NO_PRESS};

but_state_t BUT_Debrief(buttons_t *but)
{
	but_state_t but_state = BUT_NO_PRESS;
	
	//убрал ! чтобы срабатывание было от 1
	if (PIN_Check(but->pin)){
	   if (but->count < BUT_COUNT_MAX) {
	      but->count++;		
	      if (but->count > BUT_THRESHOLD){
		     but->buf = BUT_PRESSED;
		     if (but->count > BUT_LONG_THRESHOLD){
			    but->buf = BUT_LONG_PRESS;
			    but->count = BUT_COUNT_MAX + 10;
			 }
		  }
		  //but_state = but->buf;	
       }
	   but_state = but->buf;
	}
    else{
	   but->count = 0;
	   if (but->buf == BUT_PRESSED){
	      but_state = BUT_RELEASE;
	   }
	   if (but->buf == BUT_LONG_PRESS){
		   but_state = BUT_RELEASE_LONG;
	   }
	   but->buf = BUT_NO_PRESS;
    }
	return but_state;
}

uint8_t signals = 0;
uint8_t cycle = 0;
uint8_t led_enable = 0;


void SetNextState(dev_state_t next_state)
{
	dev_cur_state = next_state;
}


void LED_SetOff(void)
{
	led_enable = 0;
}

void LED_Set(uint8_t leds, uint8_t repeat)
{
   led_enable = 1;
   signals = leds;
   cycle = repeat;	
}

void LED_Func(void)
{
	static uint8_t sign;
	
	switch(led_state){
		case STATE_NORMAL:
		if (led_enable){
			sign = signals;
			if (cycle != LED_BLINK_INFINITY){
			  if (!cycle){
		        led_enable = 0;	  
				break;
              }
			  cycle--;
   		    }
			led_state = STATE_LED_ON;
			PORTB |= sign;
		    soft_timer_state = STIM_WORKS;
		    soft_timer_count = LED_BLINK_PERIOD;	
		}
		break;
		
		case STATE_LED_ON:
		if(STIM_Check(STIM_EXPIRED)){
           led_state = STATE_LED_OFF;
		   PORTB &= ~sign;
		   soft_timer_state = STIM_WORKS;
		   soft_timer_count = LED_BLINK_PERIOD;		   
		}
		break;
		
		case STATE_LED_OFF:
		if(STIM_Check(STIM_EXPIRED)){
           led_state = STATE_NORMAL;
		   LED_OffAll();	   
		}
		break;
		
		default:
		break;
	}
}

int main(void)
{
	/*инициализаци€ порта*/
	DDRB = (0<<BUT_LEFT)|(0<<BUT_RIGHT)|(0<<BUT_CONTR)|(1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL);
	PORTB = (0<<LEFT_SIGNAL)|(0<<RIGHT_SIGNAL);
	//PORTB = (1<<BUT_LEFT)|(1<<BUT_RIGHT)|(1<<BUT_CONTR); //закомментил, так как подт€жка внешн€€
	
	/*инициализаци€ таймера “0. период 10мс.*/
	TCCR0A = (1<<WGM01)|(0<<WGM00);
	TCCR0B = (0<<WGM02)|(0<<CS02)|(1<<CS01)|(0<<CS00);
	OCR0A  = TIM_OCR_VALUE;
	TIMSK0 = (1<<OCIE0A);
		
		
	sei();
	
    while(1)
    {				  	
        if (tim0_comp_flag){
		   tim0_comp_flag = 0;
           
		   /*обработка событий*/
		   switch (dev_cur_state)
		   {
			   case STATE_NORMAL:
			   	  LED_SetOff();
			      if ((but_left_state == BUT_PRESSED)||(but_left_state == BUT_LONG_PRESS))     { LED_Set((1<<LEFT_SIGNAL), LED_BLINK_SHORT_TURN); SetNextState(STATE_LEFT_TURN);} 
			      if ((but_right_state == BUT_PRESSED)||(but_right_state == BUT_LONG_PRESS))   { LED_Set((1<<RIGHT_SIGNAL), LED_BLINK_SHORT_TURN);SetNextState(STATE_RIGHT_TURN);}	      
				  if (but_contr_state == BUT_RELEASE)    { LED_Set((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL), LED_BLINK_THANK); SetNextState(STATE_THANK);}
				  if (but_contr_state == BUT_LONG_PRESS) { LED_Set((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL), LED_BLINK_INFINITY);SetNextState(STATE_ALARM);}	  		  
			      
				  break;
			   
			   case STATE_LEFT_TURN:	
			      if (but_contr_state == BUT_RELEASE) {
				      SetNextState(STATE_THANK);
					  LED_Set((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL), LED_BLINK_THANK);
				  }
				  
				  if (but_contr_state == BUT_LONG_PRESS) { 
					  SetNextState(STATE_ALARM);      
					  LED_Set((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL), LED_BLINK_INFINITY);
				  }
				  
				  if ((but_right_state == BUT_PRESSED)||(but_right_state == BUT_LONG_PRESS))   { LED_Set((1<<RIGHT_SIGNAL), LED_BLINK_SHORT_TURN);SetNextState(STATE_RIGHT_TURN);}	
				  	
				  if (!led_enable){				  
			         if ((but_left_state == BUT_RELEASE)||(but_left_state == BUT_RELEASE_LONG)||(but_left_state == BUT_NO_PRESS)){ 
				        SetNextState(STATE_NORMAL);
				     }
					 else{
					    LED_Set((1<<LEFT_SIGNAL), LED_BLINK_ONE);	 
					 }
				  }
				  break;
			   
			   case STATE_RIGHT_TURN:
			      if (but_contr_state == BUT_RELEASE) {
				      SetNextState(STATE_THANK);
				      LED_Set((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL), LED_BLINK_THANK);
			      }
				  				  
				  if (but_contr_state == BUT_LONG_PRESS) {
					  SetNextState(STATE_ALARM);
					  LED_Set((1<<LEFT_SIGNAL)|(1<<RIGHT_SIGNAL), LED_BLINK_INFINITY);
				  }

                  if ((but_left_state == BUT_PRESSED)||(but_left_state == BUT_LONG_PRESS))     { LED_Set((1<<LEFT_SIGNAL), LED_BLINK_SHORT_TURN); SetNextState(STATE_LEFT_TURN);}
				  
				  
				  if (!led_enable){					  
				     if ((but_right_state == BUT_RELEASE)||(but_right_state == BUT_RELEASE_LONG)||(but_right_state == BUT_NO_PRESS)){ 
					    SetNextState(STATE_NORMAL);
				     } 
					 else{
					    LED_Set((1<<RIGHT_SIGNAL), LED_BLINK_ONE);	 
					 }
				  }
			      break;
				  
			   case STATE_THANK:
			      if (!led_enable){
                     SetNextState(STATE_NORMAL);  
				  }
			      break;
				  
			   case STATE_ALARM:     
				  if ((but_contr_state == BUT_RELEASE)) { 
				     SetNextState(STATE_NORMAL);  
				  }	
			      break;
			   	  	  
			   default:
			      dev_cur_state = STATE_NORMAL;
			      break;	  
		   }
		   
		   LED_Func();
		   
		   /* опрос кнопок */
		   but_left_state = BUT_Debrief(&but_left);
		   but_right_state = BUT_Debrief(&but_right);
		   but_contr_state = BUT_Debrief(&but_contr);
		   
		  				
			
		}
    }
}

/*софтовый таймер и флаг дл€ опроса кнопок*/
ISR(TIM0_COMPA_vect)
{
   if(soft_timer_state == STIM_WORKS){
	   if (soft_timer_count){
	      soft_timer_count--;	   
	   }
	   else{
	      soft_timer_state = STIM_EXPIRED;	   
	   }
   }	
	
	tim0_comp_flag = 1;
}

