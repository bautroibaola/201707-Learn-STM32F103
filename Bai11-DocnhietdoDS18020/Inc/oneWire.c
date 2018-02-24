#include "main.h"
#include "stm32f1xx_hal.h"
#include "oneWire.h"
#include "delay.h"
//Thu vien cho DS1802
unsigned char devicePresent = NOPRESENT; //Day la bien kiem tra xem co thiet bi gan vao bus chua

void oneWire_setOutput(void){
	
	GPIO_InitTypeDef GPIO_InitStruct;
	/*Configure GPIO pin : PB9 */
  GPIO_InitStruct.Pin = DQ;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DQ_PORT, &GPIO_InitStruct);
	
	DQ_WRITE_HIGH;
}


void oneWire_setInput(void){
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = DQ;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DQ_PORT, &GPIO_InitStruct);
	
}


void oneWire_reset(void){
	oneWire_setOutput();
	DQ_WRITE_LOW;
	delay_us(480);
	oneWire_setInput();
	delay_us(70);
	devicePresent = oneWire_ReadBit();
	if (devicePresent == PRESENT){
		// Lam viec gi do o day
	} else{
		//Lam viec gi do o day
	}
	delay_us(410);
	
	
}

//Ghi du lieu
void oneWire_WriteBit0(void){
	
	oneWire_setOutput();
	DQ_WRITE_LOW;
	delay_us(60);
	oneWire_setInput();//Nha bus 
	delay_us(10);
	
}


void oneWire_WriteBit1(void){
	
	oneWire_setOutput();
	DQ_WRITE_LOW;
	delay_us(6);
	oneWire_setInput();//Nha bus 
	delay_us(64);
	
}


void oneWire_WriteByte(unsigned char data){
	
	unsigned char temp, i;
	for(i=0; i< 8; i++){
		temp = data;
		data = data >> 1;
		if (temp & 0x01) oneWire_WriteBit1();
		else oneWire_WriteBit0();
	}
	
}


unsigned char oneWire_ReadBit(void){
	
	unsigned char data;
	oneWire_setOutput();
	DQ_WRITE_LOW;
	delay_us(6);
	
	oneWire_setInput();//Nha bus 
	delay_us(9);
	
	data = DQ_READ;
	delay(55);
	return data;
	
}


unsigned char onwWire_ReadByte(void){
	unsigned char data, temp, i;
	for (i = 0; i < 8; i++){
		temp = oneWire_ReadBit();
		if (temp) data = data | (1 << i);
	}
	return data;
	
}

