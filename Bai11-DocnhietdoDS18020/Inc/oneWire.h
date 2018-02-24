#ifndef __ONEWIRE_H
#define __ONEWIRE_H
//Thu vien cho DS1802
#include "main.h"
#include "stm32f1xx_hal.h"

//Dinh nghia co thiet bi gan vao bus hay khong?
#define PRESENT 0
#define NOPRESENT 1

//Dinh nghia chan data one-wire
#define DQ 				GPIO_PIN_9
#define DQ_PORT 	GPIOB

//Xuat du lieu tai chan DQ
#define DQ_WRITE_HIGH  	HAL_GPIO_WritePin(DQ_PORT, DQ, GPIO_PIN_SET)
#define DQ_WRITE_LOW 		HAL_GPIO_WritePin(DQ_PORT, DQ, GPIO_PIN_RESET)

//Nhan du lieu tai chan DQ
#define DQ_READ  	HAL_GPIO_ReadPin(DQ_PORT, DQ)

void oneWire_setOutput(void);
void oneWire_setInput(void);

//Ghi du lieu
void oneWire_reset(void);

void oneWire_WriteBit0(void);
void oneWire_WriteBit1(void);
void oneWire_WriteByte(unsigned char data);

unsigned char oneWire_ReadBit(void);
unsigned char onwWire_ReadByte(void);

  
#endif /* __ONEWIRE_H */

