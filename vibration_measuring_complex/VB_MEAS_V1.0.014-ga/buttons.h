/*
 * buttons.h
 *
 * Created: 12.04.2014 23:04:14
 *  Author: �������������
 */ 

#ifndef	BUTTONS_H_
#define	BUTTONS_H_
//---------------------------------------------------------------------------------------
#define norm
//#define lin
//---------------------------------------------------------------------------------------
#include <avr/io.h>
//---------------------------------------------------------------------------------------
#include "bit_macros.h"
//---------------------------------------------------------------------------------------
#define MASK_BUTTONS 			(1<<OOK)|(1<<UP)|(1<<DOWN)|(1<<RIGHT)|(1<<LEFT)
//---------------------------------------------------------------------------------------
//����, � �������� ���������� ������
#define PORT_BUTTON 			PORTC
#define PIN_BUTTON 				PINC
#define DDRX_BUTTON 			DDRC
//---------------------------------------------------------------------------------------
//������ �������, � ������� ���������� ������
#define OOK 					0UL
#define UP 						1UL
#define DOWN					2UL
#define RIGHT 					3UL
#define LEFT 					4UL
//---------------------------------------------------------------------------------------
//����, ������� ����� ������������ � �����
#define KEY_NULL      			0UL
#define KEY_OK					1UL
#define KEY_CANCEL     			2UL
#define KEY_EXIT	   			3UL
#define KEY_RIGHT      			4UL
#define KEY_LEFT      			5UL
//---------------------------------------------------------------------------------------
//������� ������ ������ ������ ������ ������������
#define THRESHOLD				20UL
#define THRESHOLD2				250UL
//---------------------------------------------------------------------------------------
volatile unsigned char pressedKey = 0;
unsigned char comp = 0;
/**************************************************************************
*   Function name : BUT_Init
*   Returns :       ���
*   Parameters :    ���
*   Purpose :       ������������� ������ �����/������
*                   ���������� ������ � ������ main`a
****************************************************************************/
void BUT_Init(void)
{
	DDRX_BUTTON &= ~(MASK_BUTTONS);
	PORT_BUTTON |= MASK_BUTTONS;
};
/**************************************************************************
*   Function name : BUT_Debrief
*   Returns :       ���
*   Parameters :    ���
*   Purpose :       ���������� ������. ���������� ������ �� ����������
*                   ���� ������ ������ � ������� THRESHOLD ����������,
*                   �� ����� ������������ � �����
****************************************************************************/
void BUT_Debrief(void)
{
	unsigned char key;

	//���������������� ����� ������� ��
	if (BitVal(PIN_BUTTON, OOK)==0)
	key = KEY_OK;
	else if (BitVal(PIN_BUTTON, UP)==0)
	key = KEY_CANCEL;
	else if (BitVal(PIN_BUTTON, DOWN)==0)
	key = KEY_EXIT;
	else if (BitVal(PIN_BUTTON, RIGHT)==0)
	key = KEY_RIGHT;
	else if (BitVal(PIN_BUTTON, LEFT)==0)
	key = KEY_LEFT;
	else {
		key = KEY_NULL;
	};
	
	
	#ifdef norm
		//---------------------------------------------------------------------------------------
		//���� �� ��������� ���������� ���-�� ����
		if (key!=0)
		{
			//� ���� ������ ������������ �����
			//�������� �� ����� � �����
			if (comp == THRESHOLD)
			{
				comp = THRESHOLD+10;
				pressedKey = key;
				return;
			}
			else if (comp < (THRESHOLD+5))
			{
				comp++;
			};
		}
		else
		{
			comp=0;
		};
		//---------------------------------------------------------------------------------------
	#endif
	#ifdef lin
		//---------------------------------------------------------------------------------------
		//���� �� ��������� ���������� ���-�� ����
		if (key!=0)
		{
			//� ���� ������ ������������ ����� �����
			//�� ����� ����� �� ����� � �����
			if (comp > THRESHOLD2)
			{
				comp = THRESHOLD2 - 40;
				pressedKey = key;
				return;
			}
			else
			{
				comp++;
			};
			//� ���� ������ ������������ �����
			//�������� �� ����� � �����
			if (comp == THRESHOLD)
			{
				pressedKey = key;
				return;
			};
		}
		else
		{
			comp=0;
		};
		//---------------------------------------------------------------------------------------
	#endif
};
/**************************************************************************
*   Function name : BUT_GetKey
*   Returns :       ����� ������� ������
*   Parameters :    ���
*   Purpose :       ���������� ���������� ���������� ������
*                   ��� ���� ����� ���������
*                   ���������� ������ � main`e � ����� while
*
****************************************************************************/
unsigned char BUT_GetKey(void)
{
	unsigned char key = pressedKey;
	pressedKey = KEY_NULL;
	return key;
};
/**************************************************************************
*   Function name : BUT_SetKey
*   Returns :       ���
*   Parameters :    ����� ������
*   Purpose :       ���������� � ��������� ����� ��������
*                   ��������� ������ ��� �������� ������� ������
****************************************************************************/
void BUT_SetKey(unsigned char key)
{
	pressedKey = key;
};
#endif //BUTTONS_H_
