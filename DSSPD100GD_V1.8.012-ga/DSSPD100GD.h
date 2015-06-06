/*
 * DSSPD100GD.h
 *
 * Created: 08.11.2013 8:51:51
 *  Author: Администратор
 */ 

#ifndef DSSPD100GD_H_
#define DSSPD100GD_H_
//---------------------------------------------------------------------------------------
#define F_CPU 8000000UL // or whatever may be your frequency
//---------------------------------------------------------------------------------------
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "menu.h"
#include "kaibr.h"
#include "buart.h"
#include "filter.h"
#include "init_mcu.h"
//---------------------------------------------------------------------------------------
#define MODE					(((PIND)>>(7))&1)
#define FILTR					(((PIND)>>(6))&1)
#define DIN						(((PIND)>>(2))&1)
//---------------------------------------------------------------------------------------
signed int nool=0,press=0,old_press=0,data=0;
//---------------------------------------------------------------------------------------

#endif /* DSSPD100GD_H_ */