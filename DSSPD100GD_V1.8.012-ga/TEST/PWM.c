#include <tiny25.h>

#include <delay.h>


#define                                sel PINB.0
#define                                pls PINB.3
#define                                mns PINB.4

#define out_put                  PORTB.0  //17 

#define ADC_VREF_TYPE 0x00

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=(adc_input & 0x0f) | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}


// Declare your global variables here


unsigned int PWM0=0,PWM=0,fl=0,fl1=0,temp=0;
eeprom unsigned char PWM_eeprom=100;




//**********************************************************************
void beep (unsigned int squeak)  //Робимо пік
{
unsigned int i=0,t=128;

out_put = 0;
delay_us(62);
out_put = 1;
delay_us(62);


for (i=0;i<8;i++) 
    {
        out_put = 0;
        delay_us(31);
        if (squeak>>8&t)
        {
            out_put = 1;
            delay_us(62);
        }else
        {     
            delay_us(62);
            out_put = 1;
         };
        delay_us(31);
        t=t>>1;
    };
out_put = 0;
delay_us(93);
out_put = 1;
delay_us(31);

out_put = 0;
delay_us(62);
out_put = 1;
delay_us(62);

t=128;
for (i=0;i<8;i++) 
    {
        out_put = 0;
        delay_us(31);
        if (squeak&t)
        {
            out_put = 1;
            delay_us(62);
        }else
        {     
            delay_us(62);
            out_put = 1;
         };
        delay_us(31);
        t=t>>1;
    };
out_put = 0;
delay_us(31);
out_put = 1;
delay_us(93);


};




void main(void)
{
// Declare your local variables here
unsigned int i=0;
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=Out 
// State5=T State4=P State3=P State2=P State1=0 State0=1 
PORTB=0x1D;
DDRB=0x03;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 125,000 kHz
// Mode: Fast PWM top=0xFF
// OC0A output: Disconnected
// OC0B output: Non-Inverted PWM
TCCR0A=0x23;
TCCR0B=0x03;
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
// ADC Clock frequency: 125,000 kHz
// ADC Voltage Reference: AVCC pin
// ADC Bipolar Input Mode: Off
// ADC Reverse Input Polarity: Off
// ADC Auto Trigger Source: ADC Stopped
// Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
DIDR0&=0x03;
DIDR0|=0x00;
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x86;
ADCSRB&=0x5F;



delay_ms(500);


while (1)
      {
      
delay_ms(25);
beep (13107);
i++;
}}