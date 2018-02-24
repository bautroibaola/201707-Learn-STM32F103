#include "hexaKeypad.h"


void hexaKeypadInit(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.Pin = COL1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(COL1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = COL2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(COL2_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = COL3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(COL3_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = COL4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(COL4_PORT, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.Pin = ROW1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(ROW1_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = ROW2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(ROW2_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = ROW3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(ROW3_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = ROW4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(ROW4_PORT, &GPIO_InitStruct);
	
	//Ghi muc cao het, de doc khong bi lan
	ROW1_WR_HIGH;
	ROW2_WR_HIGH;
	ROW3_WR_HIGH;
	ROW4_WR_HIGH;

}


unsigned char hexaKeypadReadKey(void){
	unsigned char key=255;
	
	ROW1_WR_LOW; ROW2_WR_HIGH; ROW3_WR_HIGH; ROW4_WR_HIGH; 
	if (!COL1_RD){
		key = 1;
		while(!COL1_RD); //kiem tra phim van con bam hay ko
	} 
	else if(!COL2_RD){
		key = 2;
		while(!COL2_RD);
	}
	else if(!COL3_RD){
		key = 3;
		while(!COL3_RD);
	}
	else if(!COL4_RD){
		key = 'A';
		while(!COL4_RD);
	}
	
	
	ROW1_WR_HIGH; ROW2_WR_LOW; ROW3_WR_HIGH; ROW4_WR_HIGH; 
	if (!COL1_RD){
		key = 4;
		while(!COL1_RD);
	} 
	else if(!COL2_RD){
		key = 5;
		while(!COL2_RD);
	}
	else if(!COL3_RD){
		key = 6;
		while(!COL3_RD);
	}
	else if(!COL4_RD){
		key = 'B';
		while(!COL4_RD);
	}
	
	
	ROW1_WR_HIGH; ROW2_WR_HIGH; ROW3_WR_LOW; ROW4_WR_HIGH; 
	if (!COL1_RD){
		key = 7;
		while(!COL1_RD);
	} 
	else if(!COL2_RD){
		key = 8;
		while(!COL2_RD);
	}
	else if(!COL3_RD){
		key = 9;
		while(!COL3_RD);
	}
	else if(!COL4_RD){
		key = 'C';
		while(!COL4_RD);
	}
	
	
	ROW1_WR_HIGH; ROW2_WR_HIGH; ROW3_WR_HIGH; ROW4_WR_LOW; 
	if (!COL1_RD){
		key = '*';
		while(!COL1_RD);
	} 
	else if(!COL2_RD){
		key = 0;
		while(!COL2_RD);
	}
	else if(!COL3_RD){
		key = '#';
		while(!COL3_RD);
	}
	else if(!COL4_RD){
		key = 'D';
		while(!COL4_RD);
	}
	
	return key;
	
}
