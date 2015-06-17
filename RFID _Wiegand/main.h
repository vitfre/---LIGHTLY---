﻿


#ifndef MAIN_H_
#define MAIN_H_

//#define F_CPU 16000000UL /*Частота кварца микроконтроллера*/
//#define F_CPU 8000000UL
#define F_CPU 7372800UL


#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)



#endif /* MAIN_H_ */

/*=======================================================================
Тип               Размер в байтах		Диапазон значений 
char						1 (8)	от -128 до 127    
short						2 (16)	от -32768 до 32767 
long						4 (32)	от -2 147 483 648 до 2 147 483 647 
unsigned char     			1 (8)	oт 0 до 255    
unsigned short				2 (16)	от 0 до 65535 
unsigned long				4 (32)	от 0 до 4 294 967 295 

Тип	              Размер в байтах	Диапазон значений
char	                  1 (8)	    от -128 до 127
unsigned char	          1 (8)	    от 0 до 255
char	                  1 (8)	    от -128 до 127
int	                      2 (16)	от -32768 до 32767
unsigned int	          2 (16)	от 0 до 65535
signed int	              2 (16)	от -32768 до 32767
short int	              2 (16)	от -32768 до 32767
unsigned short int	      2 (16)	от 0 до 65535
signed short int	      2 (16)	от -32768 до 32767
long int	              4 (32)	от -2147483648 до 2147483647
unsigned long int	      4 (32)	от 0 до 4294967295
signed long int	          4 (32)	от -2147483648 до 2147483647
float	                  4 (32)	от 3.4Е-38 до 3.4Е+38
double	                  8 (64)	от 1.7Е-308 до 1.7Е+308
long double	              10 (80)	от 3.4Е-4932 до 3.4Е+4932


volatile - переменные с этой директивой оптимизатор не имеет права трогать.
=========================================================================
<< - побитный сдвиг влево
1<<6 это 0b01000000 сдвигаем 1 влево на 6 позицию
5<<5 это 0b10100000 сдвигаем 5 влево на 5 позицию
=========================================================================
>> - побитный сдвиг вправо
255;  //0b11111111
255 >> 1; результат 127 или 0b01111111
========================================================================= 
~    - побитная инверсия
94 это 0b01011110
~ 94 станет 161 или 0b10100001
=========================================================================
| - поразрядное ИЛИ
tmp = 155
tmp = tmp | 4; //устанавливаем в единицу второй бит переменной tmp
    155     0b10011011    
|
      4     0b00000100    
   =159     0b10011111
Использовать десятичные числа для установки битов довольно неудобно. 
Гораздо удобнее это делать с помощью операции сдвига влево <<.
tmp = tmp | (1<<4); //устанавливаем в единицу четвертый бит переменной tmp
Читаем справа налево – сдвинуть единицу на четыре разряда влево, 
выполнить операцию ИЛИ между полученным числом и значением переменной tmp, 
результат присвоить переменной tmp.
Установить несколько битов в единицу можно так
tmp = tmp | (1<<7)|(1<<5)|(1<<0);
tmp |= (1<<7)|(1<<5)|(1<<0);
устанавливаем в единицу седьмой, пятый и нулевой биты переменной tmp
=========================================================================
& -побитовое И
tmp = 155     это 0b10011011
tmp = tmp & (~(1<<3)); //обнуляем третий бит 
1<<3              0b00001000
~(1<<3)           0b11110111
tmp & (~(1<<3))   0b10011011 & 0b11110111
результат         0b10010011

tmp = tmp & (~((1<<3)|(1<<5)|(1<<6))); //обнуляем третий, пятый и шестой биты 
или так 
tmp &= (~((1<<3)|(1<<5)|(1<<6)))
=========================================================================
^ -побитовое исключающее ИЛИ
	tmp = 155;0b10011011
    tmp = tmp ^ 8; // инвертируем четвертый бит переменой tmp
    155         0b10011011    
^
    8           0b00001000    
 =  147         0b10010011
tmp = tmp ^ (1<<3); // инвертируем третий бит переменой tmp или так
tmp ^= (1<<4);  //инвертируем четверый бит
Можно инвертировать несколько битов одновременно
tmp ^= ((1<<4)|(1<<2)|(1<<1)); //инвертируем 4,2 и 1 биты
=========================================================================
Как проверить установлен ли бит в переменной? Нужно обнулить все биты, 
кроме проверочного, а потом сравнить полученное значение с нулем 
if ((tmp & (1<<2)) != 0 ){
      // блок будет выполняться, только если установлен
      // второй бит переменной tmp
   }
а здесь наоборот если бит сброшен
    if ((tmp & (1<<2)) == 0 ){
      // блок будет выполняться, только если не установлен
      // второй бит переменной tmp
    }
=========================================================================	
Оператор  Значение
	==		равно
	!=		не равно
	>		больше
	>=		больше или равно
	<		меньше
	<=		меньше или равно
=========================================================================		
*/	     
/*
Знак операции	Назначение операции
( )				Вызов функции
[ ]				Выделение элемента массива
.				Выделение элемента записи
->				Выделение элемента записи
!				Логическое отрицание
~				Побитная инверсия.
-				Изменение знака
++				Увеличение на единицу
--				Уменьшение на единицу
&				Взятие адреса
*				Обращение по адресу
(тип)			Преобразование типа (т.е. (float) a)
sizeof( )		Определение размера в байтах
*				Умножение
/				Деление
%				Определение остатка от деления
+				Сложение
-				Вычитание
<<				Сдвиг влево
>>				Сдвиг вправо
<				Меньше, чем
<=				Меньше или равно
>				Больше, чем
>=				Больше или равно
==				Равно
!=				Не равно
&				Поразрядное логическое "И"
^				Поразрядное исключающее "ИЛИ"
|				Поразрядное логическое "ИЛИ"
&&				Логическое "И"
||				Логическое "ИЛИ"
?:				Условная (тернарная) операция
=				Присваивание
,				Операция запятая_
_________________________________________________
+=, - =, *=,  
%=, <<=,/=,		Составные операции присваивания (например, а *= b(т.е. a = a * b) и т.д.)
>>=,&=,|=,^= 
_________________________________________________					
 */
/*
Директивы условной компиляции
#if 0
#elif 
#else
#endif

*/