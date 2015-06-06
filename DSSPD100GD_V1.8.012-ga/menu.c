/*
 * menu.c
 *
 * Created: 08.11.2013 12:39:55
 *  Author: �������������
 */ 

#include "menu.h"

//****************************************************************************************
void Main_menu (unsigned char Com,signed int data)
{
	unsigned char redirect=0;
	signed int data1=0;
	double psi = data,smaq = data,j=-1;
	//clear_lcd();						// ������ ������� ����� �������
	switch (Com) 
	{
		case 0x00 : 
					set_lcd_position(1,1);				// ���������� ������  
					send_lcd_string("  Output (dec)  ");redirect=0x00;
		break;
		case 0x01 : 
					set_lcd_position(1,1);				// ���������� ������  
					send_lcd_string("psi  = ");
					set_lcd_position(2,1); 
					send_lcd_string("smAq = ");
					redirect=0x01;
		break;
		default:;
	}; //switch (Com)
	
	switch (redirect)
	{
		case 0x00 :
		//==========================
		set_lcd_position(2,1);           // ���������� ������
		send_lcd_string("Val");          // ������� ������ �� �������
		//==========================
		set_lcd_position(2,6);
		data1=data/0x2710;
		detect_string(data1);			// ������� �� �������
		detect_string(data);				// ������� �� �������
		//==========================
		break;
		case 0x01 :
		//==========================
		if (data==0x00)
		{
			psi = 0x00;
			data1 = 0x00;
		}
		else
		{
			if (data<0x00)
			{
				set_lcd_position(1,7);
				send_lcd_string("-");
				psi = j * psi;
				psi = ((psi-1.683)/131.07)*10000;
				data1=psi/0x2710;
			} 
			else
			{
				psi = ((psi-1.683)/131.07)*10000;
				data1=psi/0x2710;
			};
		};
		//==========================
		set_lcd_position(1,8);
		detect_string(data1);			// ������� �� �������
		send_lcd_string(",");
		detect_string(psi);				// ������� �� �������
		//==========================
		//==========================
		if (data==0x00)
		{
			smaq = 0x00;
			data1 = 0x00;
		}
		else
		{
			if (data<0x00)
			{
				set_lcd_position(2,7);
				send_lcd_string("-");
				smaq = j * smaq;
				smaq = ((smaq-1.683)/131.07)*10000;
				smaq = smaq * 70.30889373;
				data1=smaq/0x2710;
			}
			else
			{
				smaq = ((smaq-1.683)/131.07)*10000;
				smaq = smaq * 70.30889373;
				data1=smaq/0x2710;
			};
		};
		set_lcd_position(2,8);
		detect_string(data1);			// ������� �� �������
		send_lcd_string(",");
		detect_string(smaq);				// ������� �� �������
		//==========================
		break;
		default :;
	};   //switch (redirect)
	
};   //Main_menu
//*****************************************************************************************
//*****************************************************************************************
//*****************************************************************************************