
#include "main.h"
#include <avr/io.h>

//������������� ����������������

void mcu_init_ports(void)		/*�������� ������*/
{
	/*
	ddr(x) - ������ ��� ����� �����:
	1 - �����
	0 - ����

	port(x) - �������� �������� �����:
	1 - �������� ��������
	0 - �������� ���������
	�������� 0 ��� �� ������������� ����� � 0 ��� ��������� ���-��, ���� 
	����� ��������������� �������, � 1 �������� ����� ������������ ������ �������*/

	DDRC  = 0b00001000;       //���� 0 ������ ����
	PORTC = 0b11110111;       //���� 1 �������� ��������

	DDRB  = 0b00001110;
	PORTB = 0b11110001;

	DDRD  = 0b01111111;
	PORTD = 0b10000000;

}
void mcu_init_timer0(void)		/*��������� ������� TCNT0*/
{
	/*
	TIFR0 - ������� ������ ����������
			OCF0B - ���� ���������� �������� ��������� OCR0B
			OCF0A - ���� ���������� �������� ��������� OCR0A
			TOV0  - ���� ���������� �������� �������� TCNT0
	TCNT0 - ��������������� ������� ������� �������
	OCR0A - ��������������� ������� ��������� A
	OCR0B - ��������������� ������� ��������� B*/

	//GTCCR=(0<<TSM)|(0<<PSRSYNC);
	/*GTCCR - ���������� ������������� �������
			TSM - ��� ������ ���. 1 ��������������� ��� ������������
			��������. ������ ������������� �������������� ������� ���. 0.
			����� ������ TSM ���� PSRSYNC � PSRASY ��������� ������������
			���� ��� ���� ���������� ���. 1. � ������� �������� �������� 
			������������.
			PSRSYNC - ��� ������ ���. 1 ������������ �������� �0 � �1
			����� ��������. ����� ������ ��� ��������� �������� � 0.*/
	
	TCCR0A=(0<<COM0A1)|(0<<COM0A0)|(0<<COM0B1)|(0<<COM0B0)|(1<<WGM01)|(0<<WGM00);  	
	/*
	TCCR0A - ������� A ���������� �������� ���������

			COM0A0 - ��� ��� ���� ��������� ������� ������ ������ OC0A 
			COM0A1 - ��� ��� ���� ��������� ������� ������ ������ OC0A 
		
			COM0B0 - ��� ��� ���� ��������� ������� ������ ������ OC0B
			COM0B1 - ��� ��� ���� ��������� ������� ������ ������ OC0B
		
			WGM01  - ����� ������ ������ ������� �������� 
			WGM00  - ����� ������ ������ ������� �������� 

	Mode      WGM02      WGM01      WGM00  Timer/Counter          TOP    Update of     TOV Flag
										   Mode of                        OCRx at      Set on
										   Operation 
	--------------------------------------------------------------------------------------------
	  0			0		   0		  0     Normal                0xFF    Immediate     MAX
	  1         0          0          1     PWM, Phase Correct    0xFF    TOP           BOTTOM
	  2         0          1          0     CTC                   OCRA    Immediate     MAX
	  3         0          1          1     Fast PWM              0xFF    BOTTOM        MAX
	  4         1          0          0     Reserved
	  5         1          0          1     PWM, Phase Correct    OCRA    TOP           BOTTOM
	  6         1          1          0     Reserved
	  7         1          1          1     Fast PWM              OCRA    BOTTOM        TOP*/

	OCR0A=0x47;
	TCCR0B=(0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|(1<<CS02)|(0<<CS01)|(1<<CS00);	
	/*
	TCCR0B - ������� B ���������� �������� ���������
			 FOC0A - �������������� ��������� ��������� ������ OC0A 
			 ������ ��� ������� Normal � CTC
			 FOC0B - �������������� ��������� ��������� ������ OCR0B
			 ������ ��� ������� Normal � CTC
			 WGM02  - ����� ������ ������ ������� �������� 
			 CS02 - ��������� ������������
			 CS01 - ��������� ������������
			 CS00 - ��������� ������������
	000-������ ����, 001-1, 010-8, 011 - 64, 100 - 256, 101 - 1024*/

	TIMSK0=(1<<OCIE0A)|(0<<OCIE0B)|(0<<TOIE0); 
	/*
	TIMSK0 - ��������� ���������� ����������
			 OCIE0A - �� ���������� �������� ���������� � ��������� ����� OCR0A 
			 OCIE0B - �� ���������� �������� ���������� � ��������� ����� OCR0B
			 TOIE0  - �� ������������ �������� �������� TCNT0 */
}
void mcu_init_timer1(void)		/*��������� ������� TCNT1*/
{
	/*	ICR1  - 16-�� ������  ������� �������
	OCR1B - 16-�� ������  ������� ���������
	OCR1A - 16-�� ������  ������� ���������
	TCNT1 - 16-�� ������ ������� ������� �������
	TIFR1  - ������� ������ ����������
			ICF1  - ���� ���������� �������� ������� ICR1
			OCF1A - ���� ���������� �������� ��������� OCR1A
			OCF1B - ���� ���������� �������� ��������� OCR1�
			TOV1  - ���� ���������� �������� �������� TCNT1*/

	//GTCCR=(0<<TSM)|(0<<PSRSYNC);
	/*GTCCR - ���������� ������������� �������
			TSM - ��� ������ ���. 1 ��������������� ��� ������������
			��������. ������ ������������� �������������� ������� ���. 0.
			����� ������ TSM ���� PSRSYNC � PSRASY ��������� ������������
			���� ��� ���� ���������� ���. 1. � ������� �������� �������� 
			������������.
			PSRSYNC - ��� ������ ���. 1 ������������ �������� �0 � �1
			����� ��������. ����� ������ ��� ��������� �������� � 0.*/	 
			
	TCCR1A= (0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(0<<WGM11)|(0<<WGM10);  
	/*TCCR1A - ������� � ���������� �������� ���������

		COM1A1 - ��� ��� ���� ��������� ������� ������ ������ OC1A      
		COM1A0 - ��� ��� ���� ��������� ������� ������ ������ OC1A   
	   
		COM1B1 - ��� ��� ���� ��������� ������� ������ ������ OC1�      
		COM1B0 - ��� ��� ���� ��������� ������� ������ ������ OC1� 
	
		WGM11...WGM10 - ����� ������ ������ ������� ��������  */

	TCCR1B=(0<<ICNC1)|(0<<ICES1)|(0<<WGM13)|(0<<WGM12)|(0<<CS12)|(0<<CS11)|(0<<CS10);
	/* TCCR1B - �������� B ���������� �������� ���������

		   ICNC1 - ���������� ������ �������������� �� ����� �������.         
		   ICES1 � ����� ��������� ������ ������� �������.
	
		   WGM13...WGM12 - ����� ������ ������ ������� ��������    
	        
		   CS12...CS10 - ��������� ������������.
	    
	000 - ����, 001-1, 010-8, 011-64, 100-256, 101-1024, 110-������� ������������ UP  
														 111-������� ������������ DOWN


	Mode     WGM13   WGM12   WGM11    WGM10  Timer/Counter                        Mode of TOP  Update of    TOV1 Flag 
					 (CTC1)  (PWM11) (PWM10)  Operation                                         OCR1x        Set on
 
	 0         0       0        0       0      Normal                               0xFFFF     Immediate     MAX
	 1         0       0        0       1      PWM, Phase Correct, 8-bit            0x00FF     TOP           BOTTOM
	 2         0       0        1       0      PWM, Phase Correct, 9-bit            0x01FF     TOP           BOTTOM
	 3         0       0        1       1      PWM, Phase Correct, 10-bit           0x03FF     TOP           BOTTOM
	 4         0       1        0       0      CTC                                  OCR1A      Immediate     MAX
	 5         0       1        0       1      Fast PWM, 8-bit                      0x00FF     BOTTOM        TOP
	 6         0       1        1       0      Fast PWM, 9-bit                      0x01FF     BOTTOM        TOP
	 7         0       1        1       1      Fast PWM, 10-bit                     0x03FF     BOTTOM        TOP
	 8         1       0        0       0      PWM, Phase and Frequency Correct     ICR1       BOTTOM        BOTTOM
	 9         1       0        0       1      PWM, Phase and Frequency Correct     OCR1A      BOTTOM        BOTTOM
	 10        1       0        1       0      PWM, Phase Correct                   ICR1       TOP           BOTTOM
	 11        1       0        1       1      PWM, Phase Correct                   OCR1A      TOP           BOTTOM
	 12        1       1        0       0      CTC                                  ICR1       Immediate     MAX
	 13        1       1        0       1      (Reserved)                           �          �             �
	 14        1       1        1       0      Fast PWM ���������� (2...16)         ICR1       BOTTOM        TOP
	 15        1       1        1       1      Fast PWM ���������� (2...16)         OCR1A      BOTTOM        TOP*/

	TCCR1C=(0<<FOC1A)|(0<<FOC1B);
	/*
	FOC1A - �������������� ��������� ��������� ������ OC1A 
	������ ��� ������� Normal � CTC
	FOC1B - �������������� ��������� ��������� ������ OC1B
	������ ��� ������� Normal � CTC*/

	TIMSK1=(0<<OCIE1A)|(0<<OCIE1B)|(0<<TOIE1)|(0<<ICIE1);		
	/*
	TIMSK1 - ��������� ���������� ����������
		TOIE1  - �� ������������ �������� �������� TCNT1                   
		OCIE1B - �� ���������� �������� ���������� � ��������� ����� OCR1B
		OCIE1A - �� ���������� �������� ���������� � ��������� ����� OCR1A 
		ICIE1  - �� ������� �������� ICR1*/ 
}
void mcu_init_timer2(void)		/*��������� ������� TCNT2*/ 
{
	/*
OCR2A - ��������������� ������� ��������� A
OCR2B - ��������������� ������� ��������� B
TCNT2 - ��������������� ������� ������� �������
TIFR2 - ������� ������ ����������
		OCF2B - ���� ���������� �������� ��������� OCR2B      
		OCF2A - ���� ���������� �������� ��������� OCR2A          
		TOV2  - ���� ���������� �������� �������� TCNT2*/	
	
	//GTCCR=(0<<TSM)|(0<<PSRASY);
	/*GTCCR - ���������� ������������� �������
			TSM - ��� ������ ���. 1 ��������������� ��� ������������
			��������. ������ ������������� �������������� ������� ���. 0.
			����� ������ TSM ���� PSRSYNC � PSRASY ��������� ������������
			���� ��� ���� ���������� ���. 1. � ������� �������� �������� 
			������������.
			PSRASY - ��� ������ ���. 1 ������������ ������� �2
			����� �������. ����� ������ ��� ��������� �������� � 0.*/		
					
	TCCR2A=(0<<COM2A1)|(0<<COM2A0)|(0<<COM2B1)|(0<<COM2B0)|(0<<WGM21)|(0<<WGM20);
	/*
	TCCR2A - ������� � ���������� �������� ���������

		COM2A1 - ��� ��� ���� ��������� ������� ������ ������ OC1A      
		COM2A0 - ��� ��� ���� ��������� ������� ������ ������ OC1A   
	   
		COM2B1 - ��� ��� ���� ��������� ������� ������ ������ OC1�      
		COM2B0 - ��� ��� ���� ��������� ������� ������ ������ OC1� 
	
		WGM22...WGM20 - ����� ������ ������ ������� ��������*/

	TCCR2B=(0<<FOC2A)|(0<<FOC2B)|(0<<WGM22)|(1<<CS22)|(0<<CS21)|(0<<CS20);
	/*
	TCCR2B - ������� B ���������� �������� ���������
			FOC2A - �������������� ��������� ��������� ������ OC2A 
			������ ��� ������� Normal � CTC
			FOC2B - �������������� ��������� ��������� ������ OC2B
			������ ��� ������� Normal � CTC
			WGM22...WGM20 - ����� ������ ������ ������� ��������
			CS22...CS20   - ��������� ������������.
	000 - ����, 001-0, 010-8, 011 - 32, 100 - 64, 101 - 128, 110 - 256, 111 - 1024
	16000 ������ ��� 2 ����. 16000/64=250 ��������� � ������� ���������.*/
	OCR2A=250;

	ASSR=(0<<EXCLK)|(0<<AS2)|(0<<TCN2UB)|(0<<OCR2AUB)|(0<<OCR2BUB)|(0<<TCR2AUB)|(0<<TCR2BUB); 
	/*EXCLK  - ��� ���.1 ������ ����������� ������ �� ����� TOSC1. ��� ������ ���� ����������
	   �� ��������� ���� AS2. ��������� ������� ��������� ����� �������� ������, ����� ���� 
	   ��� ����� ����.    
	 AS2      - ��������� ������� � ������������ ������ �� �������� ������.  
	 TCN2UB   - ���� ��������  TCNT2   
	 OCR2AUB  - ���� ��������  OCR2A    
	 OCR2BUB  - ���� ��������  OCR2B   
	 TCR2AUB  - ���� ��������  TCCR2A    
	 TCR2BUB  - ���� ��������  TCCR2B*/
 
	/*��� ��������� ���� ����� ���� ���������� ��� AS2 �������� ASSR - � ���, ������ �������� � �����������
	������. �� ���� ��� ���� ���� ������� ��� ������ ����� ���������� � ���� �����. ���� � ���, ��� ��� ������
	�� ������ ������ ��� ���������� �������� ������� �������� ������������������ �� ������ �� ������. � ��
	��������� � �������� ��������� ����� ������ ��� ��������� �������� ������� ������� ��� ��� ������������
	��������.
	�.�., ��������, ������������� �� �������� TCNT2, ������ �� ����� 32��� ��������� ��� ��� ���� ���������
	�� �����, � ���� �������� ��� �������� � ����� ���� ��� �� ������� � � ���������� � TCNT2 ��������� �������
	�����. ����� ����� �� ��������� ������ ���������������. �.�. ��� �� �������, ��� ������� ������ � TCNT2,
	�� �� ����� ���� ��� �������� �� ��������� ������� � � ������� ������� ������ ����� ��� ����� ����������
	����������.
	����� ��������������� �������� ��������� OCR2 � ������� ������������ TCCR2
	��� ������ ������ ��� �������� � ������ ��� ����� � ������������� �������? �� ����� ������ - �� ������ �
	�������� ASSR. ��� ���� TCN2UB, OCR2UB � TCR2UB - ������ �������� �� ���� �������. ����� ��, ��������,
	���������� �������� � TCNT2 �� TCNUB ���������� 1, � ��� ������ ���� ����� �� �������������� ��������
	���� ������� � �������� ������� ������� TCNT2 � ������ ��� ������, �� ���� ���� ��������� ������������.
	����� �������, � ����������� ������, ��� ������ � �������� TCNT2, OCR2 � TCCR2 ������� ����� ���������
	����� TCN2UB, OCR2UB � TCR2UB � ������ ��������� ������ ���� ��� ����� ����. ����� ��������� ����� ����
	���������������.*/
 
	TIMSK2=(0<<OCIE2B)|(1<<OCIE2A)|(0<<TOIE2);
	/*
	TIMSK2 - ��������� ���������� ����������
			TOIE2  - �� ������������ �������� �������� TCNT2                   
			OCIE2B - �� ���������� �������� ���������� � ��������� ����� OCR2B
			OCIE2A - �� ���������� �������� ���������� � ��������� ����� OCR2A*/ 
}
void mcu_init_adc(void)			/*��������� ���*/    
{
	//ADC - 16 �� ������ ������� ������ ������ � ������ ������ ���

	ADCSRA=(1<<ADEN)|(1<<ADSC)|(0<<ADATE)|(0<<ADIF)|(0<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);   
	/*
	ADEN - �������� ���         
	ADSC - ��������� ������ ��������������(������ �������, ���� �� ���).����� ���� ��� 
			���� = 0. �������������� ���������.       
	ADATE- ���. 0 ��������� ����������� ��������������          
	ADIF - ���� ���������� �� ��������� ��������������
	ADIE - ���������� ���������� �� ��������� ��������������        
	ADPS2...ADPS1...ADPS0 - ���������� ������� ������ ���� ��� ���������� �� 50-200 ���.   
	8000���/64 = 125��� � �������� ���������.
        
	ADPS2 ADPS1 ADPS0 Division Factor
	  0     0     0        2
	  0     0     1        2
	  0     1     0        4
	  0     1     1        8
	  1     0     0        16
	  1     0     1        32
	  1     1     0        64
	  1     1     1        128*/

	//ADCSRB=(0<<ACME)|(0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0); 
	/*
	ACME -  ������ ���������� ����������.
	ADTS2 ADTS1 ADTS0  �������� ���������� �������      
	  0		0	 0      ����� ������������ ��������������
	  0		0    1		���������� �� ����������� �����������
	  0		1    0		������� ���������� INT0
	  0		1    1		����. �� ������� ���������� � ������� �0
	  1		0    0		����. �� ������������ �0
	  1		0    1		����. �� ������� "����������" � ������� �1
	  1		1    0		����. �� ������������ �1
	  1		1    1		����. �� ������� "������" �1
	��� ��������� �������� ������� ������. ��� �� ������ ����������.*/

	ADMUX=(0<<REFS1)|(1<<REFS0)|(1<<ADLAR)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);
	/*
	REFS1...REFS0 - ����� ��������� �������� ����������      
 
	REFS1       REFS0   �������� �������� ����������
	 0           0      ������� ���, �����. � ������ AREF, �����. ��� ��������.
	 0           1      �� ���������� �������
	 1           0      ������
	 1           1      �����. ��� ����������� 1.1 V
     
	ADLAR - ���� ���. 1 �� ������������ �� ������ ���� ���� 0 �� �� �������.

	MUX3..0 ����� �������� ������ 
	 0000		ADC0
	 0001		ADC1
	 0010		ADC2
	 0011		ADC3
	 0100		ADC4
	 0101		ADC5
	 0110		ADC6
	 0111		ADC7
	 1110       1.1V (VBG)���������� � ��� ���������� �������� �������� 
				���������� �� 1.1 ������.(��� ����������) 
	 1111       0V (GND) ������ ����� ��� ������� �� �����, (��� ��������� �����)*/

	DIDR0=(0<<ADC5D)|(1<<ADC4D)|(0<<ADC3D)|(0<<ADC2D)|(1<<ADC1D)|(1<<ADC0D);   
	//���������� ������� ���. ����� �������� ���. 1 �����. ����� ��������.
}
void mcu_init_an_comp(void)		/*���������� ����������*/
{
	ACSR=(1<<ACD)|(0<<ACBG)|(0<<ACO)|(0<<ACI)|(0<<ACIE)|(0<<ACIC)|(0<<ACIS1)|(0<<ACIS0);
	/*
	ACD - ��������� ����������� 0-�������, 1-��������
	ACBG - ����������� � �����. ����� (AIN0) ���������� ��� 0-�� ��������� 1-���������
	ACO - ���� AIN0>AIN1, ����� ACO = 1.
	ACI - ���� ����������
	ACIE - ���������� ����������
	ACIC - �����. � ����� ������� �1

	������� �������� ����������         
	ACIS1  ACIS0 
	 0       0      ����� ��������� ACO
	 0       1      ������
	 1       0      � 1 �� 0
	 1       1      � 0 �� 1
	 ���� U �� AIN1 < ��� �� AIN0 ����� ����� ����������� ACO ����� ����� 1 
	 � ��������.*/ 
}
void mcu_init_ext_int(void)		/*��������� ������� ���������� INT0, INT1*/
{
	EIMSK=(0<<INT1)|(0<<INT0);
	//INT1 ���������� �� ���������� � INT1
	//INT0 ���������� �� ���������� � INT0

	EICRA=(0<<ISC11)|(0<<ISC10)|(0<<ISC01)|(0<<ISC00);
	/*
	ISC11  ISC10 - ��������� ���������� INT1 
	  0      0     �� ������� ������
	  0      1     ��� ����� ���������� ���������
	  1      0     �� ���������� ������ �� ������
	  1      1     �� ������������ ������ �� ������

	ISC01   ISC00 - ��������� ���������� INT0
	  0      0     �� ������� ������
	  0      1     ��� ����� ���������� ���������
	  1      0     �� ���������� ������ �� ������
	  1      1     �� ������������ ������ �� ������*/
	
	PCICR=(0<<PCIE2)|(1<<PCIE1)|(0<<PCIE0);
	/*
	PCIE2 - ���������� ���������� �� ��������� ��������� ������� 2� ������. ���� � ����
			���� �������� ���. 1 � ���� I=1, �� ����������� ������� ���������� �� ���������
			��������� ������� PCINT23...16 ��. � ������������� ���������� �������� �����
			��������� ������� �� ����� ������.         
	PCIE1 - ���������� ���������� �� ��������� ��������� ������� 2� ������. ���� � ����
			���� �������� ���. 1 � ���� I=1, �� ����������� ������� ���������� �� ���������
			��������� ������� PCINT14...8 ��. � ������������� ���������� �������� �����
			��������� ������� �� ����� ������.         
	PCIE0 -  ���������� ���������� �� ��������� ��������� ������� 2� ������. ���� � ����
			���� �������� ���. 1 � ���� I=1, �� ����������� ������� ���������� �� ���������
			��������� ������� PCINT7...0 ��. � ������������� ���������� �������� �����
			��������� ������� �� ����� ������. */

	PCMSK0=(0<<PCINT7)|(0<<PCINT6)|(0<<PCINT5)|(0<<PCINT4)|(0<<PCINT3)|(0<<PCINT2)|(0<<PCINT1)|(0<<PCINT0);  
	PCMSK1=(0<<PCINT14)|(1<<PCINT13)|(1<<PCINT12)|(0<<PCINT11)|(0<<PCINT10)|(0<<PCINT9)|(0<<PCINT8); 
	PCMSK2=(0<<PCINT23)|(0<<PCINT22)|(0<<PCINT21)|(0<<PCINT20)|(0<<PCINT19)|(0<<PCINT18)|(0<<PCINT17)|(0<<PCINT16); 
	/*
	PCMSK0 - ���������� ������� ��������� ���������� PCI0. ���� �����-���� ��� ���������� � 1, 
			 �� ��������� ��������� ���������������� ������ ������� ��������� ���������.
	PCMSK1 - ���������� ������� ��������� ���������� PCI1. ���� �����-���� ��� ���������� � 1, 
			 �� ��������� ��������� ���������������� ������ ������� ��������� ���������.
	PCMSK2 - ���������� ������� ��������� ���������� PCI2. ���� �����-���� ��� ���������� � 1, 
			 �� ��������� ��������� ���������������� ������ ������� ��������� ���������.*/


	//EIFR=(0<<INTF1)|(0<<INTF0); //������� ������ ������� ���������
	//PCIFR=(0<<PCIF2)|(0<<PCIF1)|(0<<PCIF0); 
	/*
	PCIF2 - ���� ���������� �� ��������� ��������� ������� 2� ������. ���� � ����������
			������� �� ����� �� ������� PCINT23...16 ������������� ������ �� ����������
			, �� ���� ��� ���. � 1. ���� ��������� ��������� ��� ������� ������������ 
			��������� ���������� ��� ����������, ������� � ���� ���. 1.          
	PCIF1 - ���� ���������� �� ��������� ��������� ������� 2� ������. ���� � ����������
			������� �� ����� �� ������� PCINT15...8 ������������� ������ �� ����������
			, �� ���� ��� ���. � 1. ���� ��������� ��������� ��� ������� ������������ 
			��������� ���������� ��� ����������, ������� � ���� ���. 1.            
	PCIF0 - ���� ���������� �� ��������� ��������� ������� 2� ������. ���� � ����������
			������� �� ����� �� ������� PCINT7...0 ������������� ������ �� ����������
			, �� ���� ��� ���. � 1. ���� ��������� ��������� ��� ������� ������������ 
			��������� ���������� ��� ����������, ������� � ���� ���. 1.*/ 
}	
void mcu_init_wdt(void)			/*��������� ����������� �������*/
{
	WDTCSR=(0<<WDIF)|(0<<WDIE)|(0<<WDP3)|(0<<WDCE)|(0<<WDE)|(0<<WDP2)|(0<<WDP1)|(0<<WDP0); 
	/*
	WDIF - ���� ���������� �� ����������� �������.
	WDIE - ���������� ���������� �� ����������� �������.                  
	WDCE - ���������� ��������� ������������ ����������� �������.
	WDE  - ���������� ������ �� ����-���� ����������� �������.
	_________________
	FUSE      
	WDTON   WDE  WDIE         �����           �������� �� ����-����
	  1		 0	  0         ����������          ��� ��������
	  1      0	  1			����� ����������    ����������
	  1      1    0			����� ������        �����
	  1      1    1			����� ����������    ���������� ����� �����������
							� ������			� ����� ������.
	  0      x    x         ����� ������        �����
	_________________

	����������� ������� ������������ ����������� �������.
	WDP3  WDP2   WDP1   WDP0 
	  0     0     0      0      2K (2048) cycles 16 ms
	  0     0     0      1      4K (4096) cycles 32 ms
	  0     0     1      0      8K (8192) cycles 64 ms
	  0     0     1      1      16K (16384) cycles 0.125 s
	  0     1     0      0      32K (32768) cycles 0.25 s
	  0     1     0      1      64K (65536) cycles 0.5 s
	  0     1     1      0      128K (131072) cycles 1.0 s
	  0     1     1      1      256K (262144) cycles 2.0 s
	  1     0     0      0      512K (524288) cycles 4.0 s
	  1     0     0      1      1024K (1048576) cycles 8.0 s


	*/

}
				





