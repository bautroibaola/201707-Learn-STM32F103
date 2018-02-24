#ifndef __DS1307_H
#define __DS1307_H

#include "main.h"
#include "stm32f1xx_hal.h"

//Dinh danh phan cung
#define MENU 	GPIO_PIN_11
#define UP  	GPIO_PIN_3
#define DOWN 	GPIO_PIN_4
#define DONE 	GPIO_PIN_5

#define MENU_PORT 	GPIOA
#define UP_PORT 		GPIOB
#define DOWN_PORT 	GPIOB
#define DONE_PORT 	GPIOB

#define DS1307_ADDR 0x68 //Dia chi cua ds1307
#define DS1307_ADDR_W (DS1307_ADDR << 1) | 0x00 //Ca byte DS1307_ADDR dich trai 1 don gi + voi 0x00
#define DS1307_ADDR_R (DS1307_ADDR << 1) | 0x01 //

void i2cInit(void); //Khoi tao giao tiep I2C
void keypadInit(void); //Khoi tao IO cho ban phim cai dat gio

char bcd2dec(char bcd); //Ham chuyen tu ma BCD sang THAP PHAN
char dec2bcd(char dec); //Ham chuyen ma THAP PHAN san BCD

void rtcWriteTime(char hrs, char min, char sec); // Ham cai dat gio phut giay
void rtcWriteDate(char day, char date, char mth, char yrs); //Ham cai dat thu ngay thang nam

void rtcReadTime(char *hrs, char *min, char *sec); //Ham doc gio phut giay
void rtcReadDate(char *day, char *date, char *mth, char *yrs); // Ham doc thu ngay thang nam

void keySetTime(void); //Ham set thoi gian bang phim nhan



#endif /* __DS1307_H */

