

#include <avr/pgmspace.h>
#include <stdint.h>

 typedef struct 
{
	 uint8_t  zone;		//Зона
	 uint16_t key;		//Номер ключа
}keys;//объявим тип данных keys

 const keys PROGMEM key[]=
 {	
	{81, 27801},		
	{82, 5526 },		
	{82, 6120 },
	{81, 27890},		
	{183,46000},
	{184,3592 },
	{81, 42867},		
	{230,58451},
	{183,46770},	
	{81, 28142},		
	{0,0}
};

uint8_t check_key(uint8_t in_zone, uint16_t in_key)//функция проверки считанного ключа с базой данных
{	
	uint16_t i = 0;
	while ((pgm_read_byte(&key[i].zone) != 0) || (pgm_read_word(&key[i].key) != 0))
	{
		if ((pgm_read_byte(&key[i].zone) == in_zone) && (pgm_read_word(&key[i].key) == in_key))
		{
			return 1;//ключ найден в базе
		}
		i++;
	}
	
	return 0;//ключа нет в базе
}

