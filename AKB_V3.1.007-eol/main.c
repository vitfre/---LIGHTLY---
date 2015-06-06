/*
 * AKB.c
 *
 * Created: 06.12.2012 11:46:32
 *  Author: vmk
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
//---------------------------------------------------------------------------------------
#define SetBit(x,y)		(x|=(1<<y))
#define ClrBit(x,y)		(x&=~(1<<y))
#define BitVal(x,y)		(((x)>>(y))&1)
#define BitFlp(x,y)		((x)^(1<<(y)))
//---------------------------------------------------------------------------------------
#define PWR_L_ON			BitVal(PORTB,3)	//Моніторинг живлення
#define PWR_V_ON			SetBit(PORTB,3)	//Увімкнули живлення
#define PWR_V_OFF			ClrBit(PORTB,3)	//Вимкнули живлення
//---------------------------------------------------------------------------------------
#define MAIN_L_ON			BitVal(PORTB,4)	//Моніторинг реле
#define MAIN_REL_ON			SetBit(PORTB,4)	//Увімкнули реле
#define MAIN_REL_OFF		ClrBit(PORTB,4)	//Вимкнули реле
//---------------------------------------------------------------------------------------
#define PARK				BitVal(PINB,0)	//Кнопка
#define BUTTON				BitVal(PINB,2)	//Кнопка
#define V_BORT				BitVal(PINB,1)	//Моніторинг двигуна
//---------------------------------------------------------------------------------------
#define ADC_VREF_TYPE 0x90
//---------------------------------------------------------------------------------------
unsigned int samples[16]={0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,};
//****************************************************************************************
//Функция зазадержек
//****************************************************************************************
static void pause (unsigned long int i)
{
	for (;i>0;i--)
	{
	};
};
//****************************************************************************************
//Функция измерения напряжения
//****************************************************************************************
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=(adc_input & 0x0f) | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
pause(10);//delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
};
//****************************************************************************************
//Функция фильтра
//****************************************************************************************
unsigned int filter (unsigned int del)
{
signed char cnt = 0;
unsigned long int sum = 0;
	for(cnt = 1;cnt<=15;cnt++)
	{
		samples[cnt - 1] = samples[cnt];
	};
	samples[15] = del;
	for(cnt = 15;cnt>=0;cnt--)
	{
		sum = sum + samples[cnt];
	};
del = sum/16;
return del;
};
//****************************************************************************************
//Функция настроек контроллера
//****************************************************************************************
static void retuning (void)	 			
{ 
// Input/Output Ports initialization
// Port B initialization
// Func5=In Func4=Out Func3=Out Func2=In Func1=In Func0=In 
// State5=T State4=0 State3=0 State2=P State1=T State0=P 
PORTB=0x05;
DDRB=0x18;//PB0,PB1,PB2 as input//PB5 as An input//PB3,PB4 as output

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
// Interrupt on any change on pins PCINT0-5: Off
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
// ADC Clock frequency: 64,000 kHz
// ADC Voltage Reference: 2.56V, AREF discon.
// ADC Bipolar Input Mode: Off
// ADC Reverse Input Polarity: Off
// ADC Auto Trigger Source: ADC Stopped
// Digital input buffers on ADC0: Off, ADC1: On, ADC2: On, ADC3: On
DIDR0&=0x03;
DIDR0|=0x20;
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x81;
ADCSRB&=0x5F;


GIMSK=(1<<INT0);
MCUCR=(0<<ISC00)|(1<<ISC01);											//Interrupt on falling edge on PB2

	pause(4000);														//Settle pause 1000мc
	sei();																//Interrupt enable
};
//****************************************************************************************
//Функция измерения напряжения
//****************************************************************************************
static void pause_10m (void)
{
	unsigned char i = 0;
	for (i = 35;((i > 0) & (V_BORT == 0));i--)
	{
		pause(65534);
	};
};
//****************************************************************************************
//Функция зазадержек + мониторинг напряжений
//****************************************************************************************
static unsigned int pause_10m_mon (void)
{
	unsigned char i = 0;
	unsigned int u = 0;
	for (i = 33;(i > 0) & (V_BORT == 0);i--)							// 10мин задержка
	{
		pause(65534);
		u = read_adc(0);												// Меряем
		u = filter (u);													// Фильтруем
	};
	//---------------------------------------------------------------------------------------
	if (u < 864)
	{
		//---------------------------------------------------------------------------------------
		if (MAIN_L_ON == 1)
		{
			MAIN_REL_OFF;												// Всё плохо
			PWR_V_OFF;													// Вырубаем всё
		}
		else
		{
			MAIN_REL_ON;												// Не всё плохо заряжаемся
		};
		//---------------------------------------------------------------------------------------													
	}
	else if (u < 900)
	{
		MAIN_REL_ON;													// Заряжаемся
	}
	else if (u > 900)
	{
		MAIN_REL_OFF;													// Не заряжаемся
	};
	//---------------------------------------------------------------------------------------
	return u;
};
//****************************************************************************************
//Функция переключений режимов
//****************************************************************************************
static void set_mode(unsigned char mod)
{
	switch(mod)
	{
		case 0:
		{
					MAIN_REL_ON;
					PWR_V_ON;
		};break;
		case 1:
		{
					MAIN_REL_OFF;
		};break;
	};
	pause(1000);					//250мc
};

//****************************************************************************************
//Преривание TIM1 переполнения
//****************************************************************************************
ISR (TIM1_OVF_vect)
{ 

	return;
};
//****************************************************************************************
//Преривание ADC
//****************************************************************************************
ISR (ADC_vect)
{ 
ADMUX=0x00;//ADMUX=ADC_VREF_TYPE & 0xff;
/*unsigned int adc_data;
// Read the AD conversion result
adc_data=ADCW;
//---------------------------------------------------------------------------------------
	if ((adc_data<770)&(mode==3))
	{
		mode=0;
		set_mode();
	} 
	else
	{
		
	}*/
	return;
};
//****************************************************************************************
//Преривание нажатие кнопки
//****************************************************************************************
ISR (INT0_vect)
{
	pause(100);
	//---------------------------------------------------------------------------------------															//Settle pause 25мc
	if (BUTTON == 0)
	{
		if (PWR_L_ON == 1)
		{
			PWR_V_OFF;													// При выключеном двигателе вырубается всё
		}
		else
		{
			PWR_V_ON;
		};
	};
	//---------------------------------------------------------------------------------------
	while(BUTTON == 0){pause(10);};
	return;
};
//****************************************************************************************
//Главная программа
//****************************************************************************************
int main(void)
{
	static unsigned int t = 0;
	//---------------------------------------------------------------------------------------
	retuning ();
	//---------------------------------------------------------------------------------------
    while(1)
    {
		if (V_BORT == 0)
		{
			set_mode(1);
			while(V_BORT == 0)
			{
				pause_10m_mon();										// 10мин задержка + монитор
	//---------------------------------------------------------------------------------------
				if (PARK == 0)
				{
					t = t + 10;											// 300мин пишем
				}
				else
				{
					t++;												// 3000мин пишем
				};
	//---------------------------------------------------------------------------------------
				if (t < 300)											// 300мин/3000мин пишем
				{
					pause(10);											//Settle pause
				}
				else
				{
					MAIN_REL_OFF;
					PWR_V_OFF;											//Вырубаем всё
				};
			};															//while(V_BORT == 0)
		}																//if (V_BORT == 0)
		else
		{
			t = 0;														//
			set_mode(0);
			while(V_BORT == 1){pause(10);};								//while(V_BORT == 1)
			pause_10m();												// 10мин задержка
		};																//if (V_BORT == 1)
		pause(10);														//Settle pause
    };																	//while(1)
};																		//int main(void)
