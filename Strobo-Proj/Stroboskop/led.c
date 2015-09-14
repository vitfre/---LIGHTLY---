
#include "led.h"

#define LED1_ON  (1<<LED1)
#define LED2_ON  (1<<LED2)
#define LED1_OFF  0
#define LED2_OFF  0
#define REPEAT    0xff
#define NULL      (uint8_t*)0

#define AMOUNT_LED_PROG 8

static uint8_t num_prog = 0;
static uint8_t led_index = 0;
static uint8_t led_state = 0;
static uint16_t count = 0;
static const uint8_t* pLedProg;

uint8_t count_rep = 0;

const uint8_t led_pr2[] PROGMEM =
{
	LED1_ON |LED2_OFF, 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF |LED2_ON, 5,
	LED1_OFF|LED2_OFF , 5,
	REPEAT
};

const uint8_t led_pr1[] PROGMEM =
{
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	REPEAT
};

const  uint8_t led_pr3[] PROGMEM =
{
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF  , 5,
	LED1_OFF|LED2_OFF , 5,
	
	LED1_OFF|LED2_ON , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	
	REPEAT
};


const uint8_t led_pr4[] PROGMEM =
{
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 25,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	REPEAT
};

const uint8_t led_pr5[] PROGMEM =
{
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 25,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_OFF|LED2_ON  , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_OFF , 5,
	LED1_OFF|LED2_OFF , 25,
	REPEAT
};

const uint8_t led_pr6[] PROGMEM =
{
	LED1_ON |LED2_OFF , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_ON |LED2_OFF , 4,
	LED1_OFF|LED2_OFF , 12,
	LED1_ON |LED2_OFF , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_ON |LED2_OFF , 4,
	LED1_OFF|LED2_OFF , 12,
	LED1_ON |LED2_OFF  , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_ON |LED2_OFF  , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_ON |LED2_ON  , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_ON |LED2_ON  , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_OFF|LED2_ON , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_OFF|LED2_ON , 4,
	LED1_OFF|LED2_OFF , 12,
	LED1_OFF|LED2_ON  , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_OFF|LED2_ON  , 4,
	LED1_OFF|LED2_OFF , 12,
	LED1_OFF |LED2_ON  , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_OFF |LED2_ON  , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_ON |LED2_ON  , 4,
	LED1_OFF|LED2_OFF , 4,
	LED1_ON |LED2_ON  , 4,
	LED1_OFF|LED2_OFF , 4,


	REPEAT
};

const uint8_t led_pr7[] PROGMEM =
{
	LED1_ON |LED2_ON, 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_ON, 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_ON, 5,
	LED1_OFF|LED2_OFF , 5,
	LED1_ON |LED2_ON, 5,
	LED1_OFF|LED2_OFF , 25,

	REPEAT
};


/*const uint8_t led_empty[] PROGMEM =
{
	LED1_OFF |LED2_OFF , 10,
	REPEAT
};*/

const uint8_t* const led_prog[] PROGMEM = 
{
	led_pr1,
	led_pr2, 
	led_pr3,
	led_pr4,
	led_pr5,
    led_pr6,
	led_pr7,
};



void LED_Start(uint8_t num)
{
	//if (num < LED_PROG_NUM){
	   if((num == num_prog) && (led_state)){
		   return;
	   }
	   num_prog = num; 
	   pLedProg = (uint8_t *)pgm_read_word(&led_prog[num]);
       led_index = 0;
       count = 0;
	   count_rep = 0;
       led_state = 1;
	//}
}

void LED_Stop(void)
{
   led_state = 0;
   LED_PORTX |= (1<<LED1)|(1<<LED2);
}

void LED_Contr(void)
{   
	uint8_t tmp;
	uint8_t port;
	
	if (led_state)	{
		if (!count) {
			
			tmp = pgm_read_byte(&pLedProg[led_index++]);
			if (tmp == REPEAT){
				if (count_rep < 255) {
					count_rep++;
				}
				led_index = 0;
				tmp = pgm_read_byte(&pLedProg[led_index++]);
			}
			
			port = LED_PORTX & (~((1<<LED1)|(1<<LED2)));
			port |= tmp;
			LED_PORTX = port;
		
			count = (pgm_read_byte(&pLedProg[led_index++]) - 1);
		}
		else{
		   count--;
		}
		
	}
}

