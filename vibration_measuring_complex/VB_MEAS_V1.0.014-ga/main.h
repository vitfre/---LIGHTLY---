/*
 * main.h
 *
 * Created: 11.04.2014 19:51:42
 *  Author: Администратор
 */ 


#ifndef LD_H_
#define LD_H_

#include <avr/io.h>

//---------------------------------------------------------------------------------------
#define F_CPU 4000000UL // or whatever may be your frequency
//---------------------------------------------------------------------------------------
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/io.h>
//---------------------------------------------------------------------------------------
#include "bit_macros.h"
#include "init_mcu.h"
#include "buttons.h"
#include "sensors.h"
#include "usart_debug\buart_1.h"

#include "menu.h"
#include "song.h"
#include "lcd.h"
//---------------------------------------------------------------------------------------
void(* resetFunc) (void) = 0; // Reset MC function
//---------------------------------------------------------------------------------------
#endif /* LD_H_ */