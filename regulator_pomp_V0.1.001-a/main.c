/*
 * Delay_line.c
 *
 * Created: 02.02.2014 14:00:29
 *  Author: Администратор
 */ 

#include "main.h"

//---------------------------------------------------------------------------------------
#define ADC_VREF_TYPE 0x00
//****************************************************************************************
// ADC interrupt service routine
//****************************************************************************************
ISR (ADC_vect)
{
	//---------------------------------------------------------------------------------------
	// Read the AD conversion result
	adc_data=ADCW;
	if (adc_data<50)
	{
		//---------------------------------------------------------------------------------------
		adc_data=50;
		//---------------------------------------------------------------------------------------
	};
	_delay_us(10);
	// Start the AD conversion
	ADCSRA|=0x40;
	//---------------------------------------------------------------------------------------
	return;
};

int main(void)
{
	unsigned int t=0x0000;
	//---------------------------------------------------------------------------------------
	init_periphery ();
	//---------------------------------------------------------------------------------------
	//Global enable interrupts
	sei();
	//---------------------------------------------------------------------------------------
    while(1)
    {
        //TODO:: Please write your application code 
		//---------------------------------------------------------------------------------------
		IMP_SET_M1
		_delay_ms(50);
		IMP_CLR_M1
		//---------------------------------------------------------------------------------------
		for (t=adc_data;t>1;t--)
		{
			//---------------------------------------------------------------------------------------
			_delay_ms(1);
			//---------------------------------------------------------------------------------------
		};
		//---------------------------------------------------------------------------------------
    };
};