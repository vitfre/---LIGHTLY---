/*
 * TestUart.h
 *
 * Created: 03.11.2013 21:41:30
 *  Author: User
 */ 


#ifndef HEATSTANSTION_H_
#define HEATSTANSTION_H_
//---------------------------------------------------------------------------------------
#define F_CPU 16000000UL // or whatever may be your frequency
//---------------------------------------------------------------------------------------
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//---------------------------------------------------------------------------------------
#include "buart.h"
#include "buttons.h"

#include "keypad_3x4.h"

#include "seg_7.h"
#include "init_mcu.h"
//---------------------------------------------------------------------------------------
#endif /* HEATSTANSTION_H_ */