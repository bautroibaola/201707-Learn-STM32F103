#include "OneWire.h"

#define SYSCLK HAL_RCC_GetHCLKFreq() //8000000 //Tan so cho dau vao he thong (Chinh la gia tri HCLK khi cau hinh STM32CubeMX)
static unsigned int tick=0;

void delay_init(void){
	SysTick ->CTRL &=0xfffffffb;
	tick = SYSCLK/8;
}

void delay_us(unsigned int us){ //ham tao tre theo micro second

//	SysTick -> CTRL&=0xfffffffb;
//	tick = SYSCLK/8; //ra micro second
	uint32_t temp;
	SysTick -> LOAD = us*tick;
	SysTick -> VAL = 0x00;
	SysTick -> CTRL = 0x01; //On SYSTICK timer len;
	do {
		temp = SysTick -> CTRL;
	}
	while( (temp &0x01) && ((temp &(1<<16)) == 0));
	SysTick -> CTRL = 0x00; //Off SYTICK
	SysTick -> VAL = 0x00;
	
}

void oneWirePinConfig(char pinMode){ //Ham config chan DQ la ra (output) hay vao (input)

}

void oneWireReset(void){ // Ham khoi tao lai Bus

}
void oneWireWrite0(void) //Ham ghi gia tri '0'
{
}
void oneWireWrite1(void){ //Ham ghi gia tri '1'
	
}

void oneWireWriteByte(unsigned char data){ //Ham ghi vao mot byte
}


char oneWireReadBit(void){ //Ham doc gia tri cua tung bit
	return 0;
}
unsigned char oneWireReadByte(void){ //Ham doc gia tri cua byte
	return 0;
}
