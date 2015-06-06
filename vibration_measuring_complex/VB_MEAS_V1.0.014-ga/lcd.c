/*
 * lcd.c
 *
 * Created: 11.10.2014 20:3:34
 *  Author: Администратор
 */

#include "lcd.h"

//---------------------------------------------------------------------------------------
//***************************************************************************************
//Procedure sending LCD byte
//Input: Byte, Kommand/Symbol data
//***************************************************************************************
void send_lcd_byte(unsigned char lcd_data,unsigned char rs_status)
{
	if(rs_status==lcd_kom)
	{
		ClrBit(lcd_port,lcd_rs);
	}
	else
	{
		SetBit(lcd_port,lcd_rs);
	};
	//****************************************************************************************
    if (BitVal(lcd_data, 7)) 
	{
        SetBit(lcd_port,D7);
    } else {
        ClrBit(lcd_port,D7);
    };
    if (BitVal(lcd_data, 6)) {
        SetBit(lcd_port,D6);
    } else {
        ClrBit(lcd_port,D6);
    };
    if (BitVal(lcd_data, 5)) {
        SetBit(lcd_port_2,D5);
    } else {
        ClrBit(lcd_port_2,D5);
    };
    if (BitVal(lcd_data, 4)) {
        SetBit(lcd_port_2,D4);
    } else {
        ClrBit(lcd_port_2,D4);
    };
    //****************************************************************************************
	_delay_us(50);//_delay_ms(1);
	SetBit(lcd_port,lcd_e);
	_delay_us(50);//_delay_ms(1);
	ClrBit(lcd_port,lcd_e);
	_delay_us(50);//_delay_ms(1);
	//****************************************************************************************
    if (BitVal(lcd_data, 3)) 
	{
        SetBit(lcd_port,D7);
    } else {
        ClrBit(lcd_port,D7);
    };
    if (BitVal(lcd_data, 2)) 
	{
        SetBit(lcd_port,D6);
    } else {
        ClrBit(lcd_port,D6);
    };
    if (BitVal(lcd_data, 1)) 
	{
        SetBit(lcd_port_2,D5);
    } else {
        ClrBit(lcd_port_2,D5);
    };
    if (BitVal(lcd_data, 0)) 
	{
        SetBit(lcd_port_2,D4);
    } else {
        ClrBit(lcd_port_2,D4);
    };
    //****************************************************************************************
	_delay_us(50);//_delay_ms(1);
	SetBit(lcd_port,lcd_e);
	_delay_us(50);//_delay_ms(1);
	ClrBit(lcd_port,lcd_e);
	_delay_us(50);//_delay_ms(1);
};
//***************************************************************************************
//Procedure initialisation LCD
//***************************************************************************************
void init_LCD(void)
{
	_delay_ms(10);
	lcd_ddrx |= (lcd_mask);
	lcd_port &=~ lcd_mask;
	lcd_ddrx_2 |= (lcd_mask_2);
	lcd_port_2 &=~ lcd_mask_2;
	_delay_ms(10);
	SetBit(lcd_port_2,D4);
	SetBit(lcd_port_2,D5);
	_delay_ms(5);
	/*
	SetBit(PORTB,lcd_e);
	_delay_ms(2);
	ClrBit(PORTB,lcd_e);
	_delay_ms(2);
	
	SetBit(PORTB,lcd_e);
	_delay_ms(2);
	ClrBit(PORTB,lcd_e);
	_delay_ms(2);
	
	SetBit(PORTB,lcd_e);
	_delay_ms(2);
	ClrBit(PORTB,lcd_e);
	_delay_ms(2);
	*/
	
	ClrBit(lcd_port_2,D4);
	_delay_ms(2);
	SetBit(lcd_port,lcd_e);
	_delay_ms(2);
	ClrBit(lcd_port,lcd_e);
	_delay_ms(2);
	
	send_lcd_byte(0x28,lcd_kom);					//2 lines, 5*8 pixels, 8bit data
	send_lcd_byte(0x0C,lcd_kom);					//screen enable, 
	send_lcd_byte(0x06,lcd_kom);					//auto shift left enable
	send_lcd_byte(0x01,lcd_kom);
	_delay_ms(20);
};
//***************************************************************************************
//Procedure sending LCD symbol
//Input: Symbol
//***************************************************************************************
void send_lcd_symbol(unsigned char temp_symbol)
{
	send_lcd_byte(temp_symbol,lcd_sym);
};
//***************************************************************************************
//Procedure setting LCD position
//Input: Line(1,2), Position(1..16)
//***************************************************************************************
void set_lcd_position(unsigned char temp_line, unsigned char temp_pos)
{
	switch (temp_line)
	{
		case 0x01 :
			temp_line=0x80+temp_pos-1;
		break;
		case 0x02 :
			temp_line=0xC0+temp_pos-1;
		break;
		case 0x03 :
			temp_line=0x94+temp_pos-1;
		break;
		case 0x04 :
			temp_line=0xd4+temp_pos-1;
		break;
		default :;
	};   //switch (temp_line)
	send_lcd_byte(temp_line,lcd_kom);
};
//***************************************************************************************
//Procedure send symbol string to LCD
//Input: Symbol string
//***************************************************************************************
void send_lcd_string(const char *temp_string)
{
	unsigned char i=0;
	/* for all chars in string */
	while(temp_string[i]!=0)
	{
		/* Send Write Data Start Byte */
		send_lcd_byte(temp_string[i],lcd_sym);
		i++;
	};
 };
//***************************************************************************************
//Procedure send symbol string to LCD from FLASH
//Input: Symbol string
//***************************************************************************************
void send_lcd_string_P(const char *string)
{
	/* for all chars in string */
	while (pgm_read_byte(string)!='\0')
	{
		send_lcd_byte(pgm_read_byte(string),lcd_sym);
		string++;
	};
 };
//***************************************************************************************
//Отправить строку на индикатор  16 символов
//задаются все символы, можно в кодах в виде ('A',0x55)
//***************************************************************************************
void send_lcd_code_string(char s1,char s2,char s3,char s4,char s5,char s6,char s7,char s8,char s9,char s10,char s11,char s12,char s13,char s14,char s15,char s16)
{
	send_lcd_byte(s1,lcd_sym);
	send_lcd_byte(s2,lcd_sym);
	send_lcd_byte(s3,lcd_sym);
	send_lcd_byte(s4,lcd_sym);  
	send_lcd_byte(s5,lcd_sym);
	send_lcd_byte(s6,lcd_sym);
	send_lcd_byte(s7,lcd_sym);
	send_lcd_byte(s8,lcd_sym);
	send_lcd_byte(s9,lcd_sym);
	send_lcd_byte(s10,lcd_sym);
	send_lcd_byte(s11,lcd_sym);
	send_lcd_byte(s12,lcd_sym);
	send_lcd_byte(s13,lcd_sym);
	send_lcd_byte(s14,lcd_sym);
	send_lcd_byte(s15,lcd_sym);
	send_lcd_byte(s16,lcd_sym);          
 };
//***************************************************************************************
//Procedure clearing LCD
//***************************************************************************************
void clear_lcd(void)
{
	send_lcd_byte(0x01,lcd_kom);
	_delay_ms(10);//_delay_ms(300);
};
//***************************************************************************************
//Procedure detecting symbol
//Input: Digit,
//Output: Symbol
//***************************************************************************************
unsigned char detect_symbol(unsigned char temp_det_sym)
{
	switch(temp_det_sym)
	{
		case 0:{return '0';}break;
		case 1:{return '1';}break;
		case 2:{return '2';}break;	
		case 3:{return '3';}break;
		case 4:{return '4';}break;
		case 5:{return '5';}break;
		case 6:{return '6';}break;	
		case 7:{return '7';}break;
		case 8:{return '8';}break;
		case 9:{return '9';}break;
		default:return '0';
	};
};
//***************************************************************************************
//Вывести на индикатор короткую строку из 2-х цифр
//***************************************************************************************
void detect_short_string(unsigned long int temp_volt)
{
	unsigned char j;
	char det_string[3]={0,0,0};
	j=1;
	while(j<=2)
	{
		det_string[j]=detect_symbol(temp_volt%10);
		temp_volt=temp_volt/10;
		j++;
	};
	j=2;
	while(j>=1)
	{
		send_lcd_symbol(det_string[j]);
		j--;
	};	
};
//***************************************************************************************
//Procedure detecting string.
//Input: Digit data 4 symbol,
//Output: 4 symbol on LCD on presetting position
//***************************************************************************************
void detect_string(unsigned long int temp_volt)
{
	unsigned char j;
	char det_string[5]={0,0,0,0,0};
	j=1;
	while(j<=4)
	{
		det_string[j]=detect_symbol(temp_volt%10);
		temp_volt=temp_volt/10;
		j++;
	};
	j=4;
	while(j>=1)
	{
		send_lcd_symbol(det_string[j]);
		j--;
	};	
};
//***************************************************************************************
//***************************************************************************************
//***************************************************************************************