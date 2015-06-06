/*
 * init_mcu.h
 *
 * Created: 03.10.2013 16:10:53
 *  Author: vmk
 */

#ifndef INIT_MCU_H_
#define INIT_MCU_H_
//---------------------------------------------------------------------------------------
#define F_CPU 8000000UL // or whatever may be your frequency
//---------------------------------------------------------------------------------------
#define ADC_VREF_TYPE 0x00
//---------------------------------------------------------------------------------------
#include <avr/io.h>
//***************************************************************************************
static void init_periphery (void)
{
	//---------------------------------------------------------------------------------------
	// Crystal Oscillator division factor: 2
	//#pragma optsize-
	CLKPR=0x80;
	CLKPR=0x00;
	//#ifdef _OPTIMIZE_SIZE_
	//#pragma optsize+
	//#endif
	//---------------------------------------------------------------------------------------
	
	// Input/Output Ports initialization
	// Port B initialization
	// Func5=Out Func4=Out Func3=Out Func2=In Func1=Out Func0=Out
	// State5=0 State4=0 State3=0 State2=T State1=0 State0=0
	PORTB=0x00;
	DDRB=0x3B;

	// Timer/Counter 0 initialization
	// Clock source: System Clock
	// Clock value: Timer 0 Stopped
	// Mode: Normal top=0xFF
	// OC0A output: Disconnected
	// OC0B output: Disconnected
	TCCR0A=0x00;
	TCCR0B=0x00;
	TCNT0=0x00;
	OCR0A=0x00;
	OCR0B=0x00;

	// Timer/Counter 1 initialization
	// Clock source: System Clock
	// Clock value: Timer1 Stopped
	// Mode: Normal top=0xFF
	// OC1A output: Disconnected
	// OC1B output: Disconnected
	// Timer1 Overflow Interrupt: Off
	// Compare A Match Interrupt: Off
	// Compare B Match Interrupt: Off
	PLLCSR=0x00;

	TCCR1=0x00;
	GTCCR=0x00;
	TCNT1=0x00;
	OCR1A=0x00;
	OCR1B=0x00;
	OCR1C=0x00;

	// External Interrupt(s) initialization
	// INT0: Off
	GIMSK=0x00;
	MCUCR=0x00;

	// Timer(s)/Counter(s) Interrupt(s) initialization
	TIMSK=0x00;

	// Universal Serial Interface initialization
	// Mode: Disabled
	// Clock source: Register & Counter=no clk.
	// USI Counter Overflow Interrupt: Off
	USICR=0x00;

	// Analog Comparator initialization
	// Analog Comparator: Off
	ACSR=0x80;
	ADCSRB=0x00;
	DIDR0=0x00;

	// ADC initialization
	// ADC Clock frequency: 62,500 kHz
	// ADC Voltage Reference: AVCC pin
	// ADC Bipolar Input Mode: Off
	// ADC Reverse Input Polarity: Off
	// ADC Auto Trigger Source: Free Running
	// Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
	DIDR0&=0x03;
	DIDR0|=0x00;
	ADMUX=0x01 | (ADC_VREF_TYPE & 0xff);
	ADCSRA=0xEF;
	ADCSRB&=0x58;

	_delay_ms(100);													//Settle pause
};
//***************************************************************************************
//***************************************************************************************
//***************************************************************************************
#endif /* INIT_MCU_H_ */