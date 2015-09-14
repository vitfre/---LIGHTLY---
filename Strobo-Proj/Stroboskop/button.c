#include "button.h"

#define BUT_THRESHOLD      5
#define BUT_LONG_THRESHOLD 150
#define BUT_COUNT_MAX      170

but_state_t but_state;

void BUT_Init(void)
{
	/*BUT_PORTX |= (1<<BUT_NUM);
	BUT_DDRX &= ~(1<<BUT_NUM); 
	but_state = BUT_NO_PRESS;*/
}


but_state_t BUT_Debrief(void)
{
	static but_state_t buf = BUT_NO_PRESS;
	static uint8_t count = 0;
	
	but_state_t but_state = BUT_NO_PRESS;
		
	if (!(BUT_PINX & (1<<BUT_NUM))){
	   if (count < BUT_COUNT_MAX) {
		   count++;
		   if (count > BUT_THRESHOLD){
			   buf = BUT_PRESSED;
			   if (count > BUT_LONG_THRESHOLD){
				   buf = BUT_LONG_PRESS;
				   count = BUT_COUNT_MAX + 10;
			   }
			   but_state = buf;
	       }
	   }
	}
	else{
	   count = 0;
	   if (buf == BUT_PRESSED){
	      but_state = BUT_RELEASE;
	   }
       buf = BUT_NO_PRESS;	
	}
	
	/*uint8_t tmp = but_state;
	but_state = BUT_NO_PRESS;
	return tmp;	*/
	
	return but_state;
}
