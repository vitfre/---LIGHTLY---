/*
 * menu.c
 *
 * Created: 12.10.2014 14:22:14
 *  Author: Администратор
 */ 

#include "menu.h"

//---------------------------------------------------------------------------------------
char const _cel1_[]			PROGMEM = ">";
char const _cel2_[]			PROGMEM = "<";
char const _cel3_[]			PROGMEM = "=";
char const _cel4_[]			PROGMEM = " ";
//---------------------------------------------------------------------------------------
char const _ITEM_01_[]		PROGMEM = " SENS 01";
char const _ITEM_02_[]		PROGMEM = " SENS 02";
char const _ITEM_03_[]		PROGMEM = " SENS 03";
char const _ITEM_04_[]		PROGMEM = " SENS 04";
char const _ITEM_05_[]		PROGMEM = " SENS 05";
char const _ITEM_06_[]		PROGMEM = " SENS 06";
char const _ITEM_07_[]		PROGMEM = " SENS 07";
char const _ITEM_08_[]		PROGMEM = " SENS 08";
char const _ITEM_09_[]		PROGMEM = " SENS 09";
char const _ITEM_10_[]		PROGMEM = " SENS 10";
char const _ITEM_11_[]		PROGMEM = " SENS 11";
char const _ITEM_12_[]		PROGMEM = " SENS 12";
char const _ITEM_13_[]		PROGMEM = " SENS 13";
char const _ITEM_14_[]		PROGMEM = " SENS 14";
char const _ITEM_15_[]		PROGMEM = " SENS 15";
char const _ITEM_16_[]		PROGMEM = " SENS 16";
char const _ITEM_17_[]		PROGMEM = " SENS 17";
char const _ITEM_18_[]		PROGMEM = " SENS 18";
//---------------------------------------------------------------------------------------
char const _NULL_[]			PROGMEM = "                ";
//****************************************************************************************
void Main_menu (unsigned char parent, unsigned int const *active_sensors)
{
	//---------------------------------------------------------------------------------------
	switch (parent) 
	{
		case 0x00 :
		{
			//---------------------------------------------------------------------------------------

			//---------------------------------------------------------------------------------------
		};
		break;
		
		case 0x01 : 
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_01_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[0]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_02_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[1]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------
		case 0x02 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_01_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[0]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_02_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[1]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------
		case 0x03 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_02_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[1]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_03_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[2]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------
		case 0x04 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_03_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[2]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_04_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[3]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------
		case 0x05 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_04_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[3]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_05_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[4]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------
		case 0x06 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_05_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[4]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_06_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[5]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------	
		case 0x07 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_06_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[5]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_07_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[6]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------
		case 0x08 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_07_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[6]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_08_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[7]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x09 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_08_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[7]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_09_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[8]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x0A :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_09_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[8]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_10_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[9]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x0B :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_10_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[9]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_11_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[10]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x0C :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_11_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[10]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_12_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[11]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x0D :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_12_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[11]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_13_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[12]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x0E :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_13_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[12]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_14_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[13]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x0F :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_14_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[13]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_15_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[14]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x10 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_15_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[14]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_16_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[15]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x11 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_16_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[15]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_17_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[16]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------		
		case 0x12 :
		{
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,2);
			send_lcd_string_P(_ITEM_17_);				// Виводим на дисплей
			set_lcd_position(1,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(1,11);
			detect_string(active_sensors[16]);
			set_lcd_position(2,2);
			send_lcd_string_P(_ITEM_18_);				// Виводим на дисплей
			set_lcd_position(2,10);
			send_lcd_string_P(_cel3_);
			set_lcd_position(2,11);
			detect_string(active_sensors[17]);
			//---------------------------------------------------------------------------------------
			set_lcd_position(1,1);
			send_lcd_string_P(_cel4_);
			set_lcd_position(1,16);
			send_lcd_string_P(_cel4_);
			//---------------------------------------------------------------------------------------
			set_lcd_position(2,1);
			send_lcd_string_P(_cel1_);
			set_lcd_position(2,16);
			send_lcd_string_P(_cel2_);
			//---------------------------------------------------------------------------------------

		};
		break;
		//---------------------------------------------------------------------------------------
		default:
		{
			//---------------------------------------------------------------------------------------
			//---------------------------------------------------------------------------------------
		};	//default: //switch (Com)
	};		//switch (Com)
};			//Main_menu
//*****************************************************************************************
//*****************************************************************************************
//*****************************************************************************************