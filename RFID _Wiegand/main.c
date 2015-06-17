

/* �����:               
 * ����� � �������      
 * ��� �������:         Atmega88_alarm.c
 * ��� ��:			    Atmega88�, Flash 8 Kbytes, SRAM 1024 �bytes, EEPROM 512 bytes.
 * Vcc                  2,7V - 5,5V.
 * �������� �������:    F_CPU 7372800 ���.
 * ���� �������� �����: 01.05.2015 13:29:31
 * ������ ��:           ATMEL STUDIO VERSION 6.2.1153 
 * FUSES ��:            HIGH 0xD4, LOW 0xFD;
						������������ �� ����.
*/

#if 1//�������� �����
#include "main.h"
#include "init_mcu.h"
#include "bits_macros.h"
#include "keys.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
//#include <stdlib.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#endif

#if 1//����������������
	#define DATA0 PC5
	#define DATA1 PC4
	#define PIN_WIG_26 PINC

	#define PORT_LED		PORTB
	#define LED0			PB1
	#define LED1			PB2
	#define LED2			PB3

	#define PORT_LED_GREEN	PORTC
	#define LED_GREEN		PC3
	
	#define DELAY_ALARM		6000 /*�������� ����� ���������� �� ������������*/
	
	#define MOUTION_DET		PINC
	#define INPUT			PC2
	
	#define SIREN			PORTD
	#define OUT_PUT			PORTD
	#define OUT_0			PD0
	#define OUT_1			PD1
	#define OUT_2			PD2
	#define OUT_3			PD3
	#define OUT_4			PD4
	#define OUT_5			PD5
	#define OUT_6			PD6
	
	#define IN_PUT          PINC
	#define POGREB			PC1
	#define TOILET			PC0
	
	#define DEL				20
#endif

uint8_t CheckKey,Tim0Count0;
uint8_t Zone;//����� ����
uint16_t Key;//����� �����
uint8_t Tim0Count,PcintVar,ExitTimer,CountBit,DetectorFlag,DetectorCount;
uint16_t CountAlarm,SirenCount;
uint8_t EEMEM StartAlarm;

ISR(PCINT1_vect)//������� ���������� 
{
	PcintVar=1;
	if (BitIsSet(PIN_WIG_26, DATA0) && BitIsSet(PIN_WIG_26, DATA1))
	{
		return;
	}
	CountBit++;
	if (BitIsClear(PIN_WIG_26, DATA1))
	{
		switch (CountBit)
		{
			case 1:break;
			case 2: SetBit(Zone,7);break;
			case 3: SetBit(Zone,6);break;
			case 4: SetBit(Zone,5);break;
			case 5: SetBit(Zone,4);break;
			case 6: SetBit(Zone,3);break;
			case 7: SetBit(Zone,2);break;
			case 8: SetBit(Zone,1);break;
			case 9: SetBit(Zone,0);break;
			case 10: SetBit(Key,15);break;
			case 11: SetBit(Key,14);break;
			case 12: SetBit(Key,13);break;
			case 13: SetBit(Key,12);break;
			case 14: SetBit(Key,11);break;
			case 15: SetBit(Key,10);break;
			case 16: SetBit(Key,9);break;
			case 17: SetBit(Key,8);break;
			case 18: SetBit(Key,7);break;
			case 19: SetBit(Key,6);break;
			case 20: SetBit(Key,5);break;
			case 21: SetBit(Key,4);break;
			case 22: SetBit(Key,3);break;
			case 23: SetBit(Key,2);break;
			case 24: SetBit(Key,1);break;
			case 25: SetBit(Key,0);break;
			case 26:break;	
			default: CountBit=0;break;
		}
		
	}
	
	if (CountBit==26)
	{
		CountBit=0;
		CheckKey=1;
		PcintVar=0;
		ExitTimer=0;
	}
}

ISR(TIMER0_COMPA_vect)//���������� ��� � 10 ���� ����� ���
{
	Tim0Count++;
	Tim0Count0++;
}

int main(void)
{
	mcu_init_ports();
	mcu_init_ext_int();
	mcu_init_timer0();
	if (eeprom_read_byte(& StartAlarm)==0)
	{
		SetBit(PORT_LED_GREEN,LED_GREEN);
	}
	sei();
	
    while(1)
    {
		
		#if 1 //���� ������ ��� � 100 ����.
		if (Tim0Count0>=10)
		{
			Tim0Count0=0;
			
			#if 1//�������� ���� � �������
			
			static uint8_t PogrebLight;
			if (BitIsClear(IN_PUT, POGREB) && PogrebLight!=DEL)//���� ������ ������ �����, �� ���� �������� �� 2 ����
			{
				PogrebLight++;
			}
			
			if (BitIsSet(IN_PUT, POGREB) && PogrebLight<DEL)
			{
				PogrebLight=0;
			}
			
			static uint8_t PogrebFlag;
			if (BitIsClear(IN_PUT, POGREB) && PogrebFlag==0)
			{
				InvBit(OUT_PUT, OUT_4);//���� � �������
				PogrebFlag=1;
			}
			else if(BitIsSet(IN_PUT, POGREB) && PogrebFlag)
			{
				PogrebFlag=0;
			}
			
			static uint16_t PogrebDelay;
			if (BitIsSet(OUT_PUT, OUT_4))
			{
				PogrebDelay++;
				if (PogrebDelay==9000 && PogrebLight!=DEL)//15 ���
				{
					ClearBit(OUT_PUT, OUT_4);//���� � �������
				}
				else if(PogrebDelay==0xFFFF) //~110��� 
				{
					ClearBit(OUT_PUT, OUT_4);//���� � �������
				}
			}
			else
			{
				PogrebDelay=0;
				PogrebLight=0;
			}
			#endif
			
			#if 1//�������� ���� � �������
			static uint8_t ToiletFlag;
			if (BitIsClear(IN_PUT, TOILET) && ToiletFlag==0)
			{
				InvBit(OUT_PUT, OUT_3);//���� � �������
				ToiletFlag=1;
			}
			else if(BitIsSet(IN_PUT, TOILET) && ToiletFlag)
			{
				ToiletFlag=0;
			}
			
			static uint16_t ToiletDelay;
			if (BitIsSet(OUT_PUT, OUT_3))
			{
				ToiletDelay++;
				if (ToiletDelay==36000)
				{
					ClearBit(OUT_PUT, OUT_3);//���� � �������
				}
			}
			else
			{
				ToiletDelay=0;
			}
			#endif
		}
		#endif
		
		#if 1//���������� ���������� �0 ���� ������ ��� � 10 ����
		if (Tim0Count>=1)
		{
			Tim0Count=0;
			
			#if 1//��������� ������ ������ ��� ���������� ������ c ������
			if (PcintVar==1)
			{
				ExitTimer++;
				if (ExitTimer>=10)
				{
					PcintVar=0;
					ExitTimer=0;
					CountBit=0;
					Zone=0;
					Key=0;
				}
			}
			#endif
			
			#if 1//�������� ����� ���������� �� ������������.
			if (BitIsClear(PORT_LED_GREEN,LED_GREEN) && CountAlarm!=6001)
			{
				CountAlarm++;
			}
			else if(BitIsSet(PORT_LED_GREEN,LED_GREEN))
			{
				CountAlarm=0;
				ClearBit(SIREN, OUT_6);
				ClearBit(SIREN, OUT_5);
				if (eeprom_read_byte(& StartAlarm))
				{
					eeprom_update_byte(& StartAlarm,0);
				}
			}
			#endif
			
			#if 1//����� �������� � ������� � ��������� ��������
			if (DetectorFlag)
			{
				DetectorCount++;
			} 
			else
			{
				DetectorCount=0;
			}
			
			if (BitIsSet(SIREN, OUT_6))
			{
				SirenCount++;
				if (SirenCount>12000)//2 ������
				{
					SirenCount=0;
					ClearBit(SIREN, OUT_6);
					ClearBit(SIREN, OUT_5);
				}
			} 
			
			#endif
			
			#if 1//������ ������ ������ �� �����
			static uint8_t Blink;
			Blink++;
			if (Blink==20)
			{
				Blink=0;
				InvBit(PORT_LED, LED1);
			}
			#endif
		}
		#endif
		
		#if 1//�������� ��������� ���� �� ����.
        if (CheckKey==1)
        {
			CheckKey=0;
			uint8_t Led=check_key(Zone,Key);
			if (Led==1)
			{
				InvBit(PORT_LED_GREEN,LED_GREEN);	
			}
			CountBit=0;
			Zone=0;
			Key=0;
        }
		#endif
		
		#if 1//��������� �� ������������
		if (CountAlarm==DELAY_ALARM)
		{
			CountAlarm=6001;
			eeprom_update_byte(& StartAlarm,1);
		}
		#endif
		
		#if 1//������������ ������� ��������
		if (eeprom_read_byte(& StartAlarm) && BitIsSet(MOUTION_DET, INPUT) && CountAlarm==6001)
		{
			DetectorFlag=1;
			SirenCount=0;
		}
		else
		{
			DetectorFlag=0;
		}
		
		if (DetectorCount>50)//0.5 ���
		{
			SetBit(SIREN, OUT_6);//�������� ������ ���� ������� ����������� ����� ��� �� 1 ���
			SetBit(SIREN, OUT_5);
		}
		#endif
    }
}



