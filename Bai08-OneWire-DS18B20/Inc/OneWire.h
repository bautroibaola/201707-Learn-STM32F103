//Hung
#ifndef __ONE_WIRE_H
#define __ONE_WIRE_H

#include "main.h"
#include "stm32f1xx_hal.h"

// Dinh danh phan cung
#define ONEWIRE_DQ  			GPIO_PIN_9
#define ONEWIRE_DQ_PORT   GPIOB

//Khai bao ham nguyen mau
void delay_init(void);
void delay_us(unsigned int us); //ham tao tre theo micro second
void oneWirePinConfig(char pinMode); //Ham config chan DQ la ra (output) hay vao (input)

void oneWireReset(void); // Ham khoi tao lai Bus
void oneWireWrite0(void); //Ham ghi gia tri '0'
void oneWireWrite1(void); //Ham ghi gia tri '1'
void oneWireWriteByte(unsigned char data); //Ham ghi vao mot byte


char oneWireReadBit(void); //Ham doc gia tri cua tung bit
unsigned char oneWireReadByte(void); //Ham doc gia tri cua byte


#endif /* __ONE_WIRE_H */
