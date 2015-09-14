#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

#define BUT_PORTX  PORTB
#define BUT_DDRX   DDRB
#define BUT_PINX   PINB
#define BUT_NUM    1

enum but_state {BUT_NO_PRESS, BUT_PRESSED, BUT_RELEASE, BUT_LONG_PRESS};
typedef enum but_state but_state_t;

void BUT_Init(void);
but_state_t BUT_Debrief(void);

#endif //BUTTON_H