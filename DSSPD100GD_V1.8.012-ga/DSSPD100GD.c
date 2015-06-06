/*
 * DSSPD100GD.c
 *
 * Created: 08.11.2013 8:08:35
 *  Author: �������������
 */ 

#include "DSSPD100GD.h"

//****************************************************************************************
//���������� �� ������������ ������� 1
//****************************************************************************************
ISR (TIMER1_OVF_vect)
{
	//=================================================================
	// Reinitialize Timer1 value
	TCNT1H=0xBDC >> 8;
	TCNT1L=0xBDC & 0xff;
	//=================================================================
	uart_write(press>>8);
	uart_write(press);
	//=================================================================
	return;
};

//****************************************************************************************
//���������� �� ������� �����
//****************************************************************************************
ISR (INT0_vect)
{
	signed char b=0,c=0,d=0;
	//=================================================================
	for (c=0; (DIN==0) & (c<35); c++)
	{
		_delay_us(1);
	};
	for (d=0; (DIN==1) & (d<35); d++)
	{
		_delay_us(1);
	};
	//=================================================================
	if ((c>3)&(d>3))
	{
		//=================================================================
		for (b=15; b>=8; b--)
		{
			//=================================================================
			for (c=0; (DIN==0) & (c<35); c++)
			{
				_delay_us(1);
			};
			for (d=0; (DIN==1) & (d<35); d++)
			{
				_delay_us(1);
			};
			//=================================================================
			if (c<d)
			{
				SetBit(data,b);
			}
			else
			{
				ClrBit(data,b);
			};
			//=================================================================
		};
		//=================================================================
		for (c=0; (DIN==0) & (c<35); c++)
		{
			_delay_us(1);
		};
		for (d=0; (DIN==1) & (d<35); d++)
		{
			_delay_us(1);
		};
		//=================================================================
		for (c=0; (DIN==0) & (c<35); c++)
		{
			_delay_us(1);
		};
		for (d=0; (DIN==1) & (d<35); d++)
		{
			_delay_us(1);
		};
		//=================================================================
		if ((c>3)&(d>3))
		{
			for (b=7; b>=0; b--)
			{
				//=================================================================
				for (c=0; (DIN==0) & (c<35); c++)
				{
					_delay_us(1);
				};
				for (d=0; (DIN==1) & (d<35); d++)
				{
					_delay_us(1);
				};
				//=================================================================
				if (c<d)
				{
					SetBit(data,b);
				}
				else
				{
					ClrBit(data,b);
				};
				//=================================================================
			};
			//=================================================================
			for (c=0; (DIN==0) & (c<35); c++)
			{
				_delay_us(1);
			};
			for (d=0; (DIN==1) & (d<35); d++)
			{
				_delay_us(1);
			};
			//=================================================================
			if (MODE==0)
			{
			} 
			else
			{
				data = data-nool;
			};
			//=================================================================
			if (FILTR==0)
			{
				press = filter(data); //Գ������
			}
			else
			{
				press = data;	//�� ��������
			};
			//=================================================================
		} 
		else
		{
		};
		//=================================================================
	} 
	else
	{
	};
	return;
};

int main(void)
{
	init_mcu();
	init_LCD();
	uart_init();
	//=================================================================
	// Global enable interrupts
	sei();
	kaibr();
	//=================================================================
    while(1)
    {
        //TODO:: Please write your application code
		if (MODE==0)
		{
			Main_menu (0x00,press);
		}
		else
		{
			Main_menu (0x01,press);
		};
		press=0;
		_delay_ms(50);
    };
};