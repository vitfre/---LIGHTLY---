#include <tiny2313.h>
#include <delay.h>

//****************************************************************************************
#define                                pls PIND.6
#define                                mns PIND.5

unsigned char dn=0;
unsigned int dig_shn;
unsigned int led_num=99;

//Таблица цифр для семисегментника
unsigned char led_table[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};

void dig_show() 
{ //Здесь отображаем разряды
    PORTD|=0xf; //Не показываем ни чего
    if (dn==0) 
    {
        dig_shn=led_num;     //Если первый разряд обновляем переменную
    }; 
    PORTB=led_table[dig_shn%10]; //Извлекаем разряд
    if (dn==2) 
    {
        PORTB|=0x80;             //Если третий разряд кажем точку
    }; 
    dig_shn/=10; //Сдвигаем разряд вправо
    PORTD&=~(1<<dn); //Показываем разряд
    dn++;
    if (dn>3) 
    {
        dn=0;
    };
}

interrupt [TIM0_OVF] void timer0_ovf_isr(void) { //Прерывание переполнения таймера 0
dig_show();
}

void main(void) 
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port A initialization
// Func2=In Func1=In Func0=In 
// State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port D initialization
// Func6=In Func5=In Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State6=P State5=P State4=1 State3=0 State2=0 State1=0 State0=0 
PORTD=0x70;
DDRD=0x1F;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 62,500 kHz
// Mode: Normal top=0xFF
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x03;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
GIMSK=0x00;
MCUCR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x02;

// Universal Serial Interface initialization
// Mode: Disabled
// Clock source: Register & Counter=no clk.
// USI Counter Overflow Interrupt: Off
USICR=0x00;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
DIDR=0x00;

// Global enable interrupts
#asm("sei")
    while (1) 
    {  
    if (mns==0) 
    {
        led_num--;   //якщо кнопка нажата то -1
        while (mns==0) 
        {
            delay_ms(10);
        }
    };
    if (pls==0) 
    {
        led_num++;   //якщо кнопка нажата то -1
        while (pls==0) 
        {
            delay_ms(10);
        }
    };
    //led_num=12; 
    delay_ms(10);
    }

} 