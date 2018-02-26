/**
  ******************************************************************************
  * @file       nokia_5110.c
  * @author     duyhungiot.vn
  * @version    V1.0.0
  * @date       28/02/2013
	* @update			20/2/2018
  ******************************************************************************
*/
#include "nokia_5110.h"
#include "main.h"


static const char ASCII[][5] =
{
 {0x00, 0x00, 0x00, 0x00, 0x00} // 20
,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c �
,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ~
,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f DEL
};



void nDelay(volatile long nTime) 
{ 
  int32_t nCount;
  for(nCount = nTime ; nCount > 0; nCount--)
  {}
}

void shiftOut(unsigned char txdata)
{
   unsigned int i;

	 HAL_GPIO_WritePin(LCD_PORT_CLK, LCD_PIN_CLK, GPIO_PIN_RESET); //  clr SCK;
	 HAL_GPIO_WritePin(LCD_PORT_DIN, LCD_PIN_DIN, GPIO_PIN_SET); //  set MOSI;
   for(i = 8; i > 0; i--)
   {
      if((txdata & 0x80) == 0x80)  HAL_GPIO_WritePin(LCD_PORT_DIN, LCD_PIN_DIN, GPIO_PIN_SET);          //  set MOSI;
      else HAL_GPIO_WritePin(LCD_PORT_DIN, LCD_PIN_DIN,GPIO_PIN_RESET);                               //  clr MOSI;
      HAL_GPIO_WritePin(LCD_PORT_CLK, LCD_PIN_CLK, GPIO_PIN_SET);                                      //  set SCK;
      HAL_GPIO_WritePin(LCD_PORT_CLK, LCD_PIN_CLK, GPIO_PIN_RESET);                                    //  clr SCK;
      txdata <<= 1;
   }
}

void LCDWrite(char data_or_command, unsigned char data)
{
   if(data_or_command)  HAL_GPIO_WritePin(LCD_PORT_DC, LCD_PIN_DC, GPIO_PIN_SET);                       //  set DC;
   else HAL_GPIO_WritePin(LCD_PORT_DC, LCD_PIN_DC, GPIO_PIN_RESET);                                    //  clr DC;
   
    HAL_GPIO_WritePin(LCD_PORT_CE, LCD_PIN_CE,GPIO_PIN_RESET);                                        //  clr LCD_CS;
    shiftOut(data);                                                                 //  Send the data
    HAL_GPIO_WritePin(LCD_PORT_CE, LCD_PIN_CE, GPIO_PIN_SET);                                          //  set LCD_CS;
}

void gotoXY(int x, int y)
{
   LCDWrite(0, 0x80 | x);                  	   // Cot.
   LCDWrite(0, 0x40 | y);                   	 // Hang.
}

void LCDBitmap(char my_array[])                //This takes a large array of bits and sends them to the LCD
{
  int index;
  for (index = 0 ; index < (LCD_X * LCD_Y / 8) ; index++)
    LCDWrite(LCD_DATA, my_array[index]);
}

void LCDCharacter(char character)
{
   unsigned int i;
   LCDWrite(LCD_DATA, 0x00);                    //Blank vertical line padding
   for (i = 0; i < 5; i++)   LCDWrite(LCD_DATA, ASCII[character - 0x20][i]);
   LCDWrite(LCD_DATA, 0x00);                    //Blank vertical line padding
}


void LCDString(char *characters)                //Given a string of characters, one by one is passed to the LCD
{
   while (*characters)
    LCDCharacter(*characters++);
}

void LCDClear(void)                             //Clears the LCD by writing zeros to the entire screen
{
   unsigned int i;
   for (i = 0; i < (LCD_X * LCD_Y / 8); i++) LCDWrite(LCD_DATA, 0x00);
   gotoXY(0, 0);                                //After we clear the display, return to the home position
}

void LCDInit(unsigned char contrast,unsigned char coefficent,unsigned char bias)   //This sends the magical commands
{
   LCD_GPIO_Init();
  
   HAL_GPIO_WritePin(LCD_PORT_RST, LCD_PIN_RST, GPIO_PIN_SET);    //  set RST + LCD_CS + DC + SCK + MOSI Configure control pins
   HAL_GPIO_WritePin(LCD_PORT_CE, LCD_PIN_CE, GPIO_PIN_SET);
   HAL_GPIO_WritePin(LCD_PORT_DC, LCD_PIN_DC, GPIO_PIN_SET);
   HAL_GPIO_WritePin(LCD_PORT_CLK, LCD_PIN_CLK, GPIO_PIN_SET);
   HAL_GPIO_WritePin(LCD_PORT_DIN, LCD_PIN_DIN, GPIO_PIN_SET);
   
   HAL_GPIO_WritePin(LCD_PORT_RST, LCD_PIN_RST, GPIO_PIN_RESET);  //  clr RST Reset the LCD to a known state
   HAL_GPIO_WritePin(LCD_PORT_RST, LCD_PIN_RST, GPIO_PIN_SET);    //  set RST;
   
   LCDWrite(LCD_CMD, 0x21);                    //	 Tell LCD that extended commands follow
   LCDWrite(LCD_CMD, 0x80 + contrast);         //	 0x80 //Set LCD Vop (Contrast): Try 0xB1(good @ 3.3V) or 0xBF if your display is too dark (max 127);
   LCDWrite(LCD_CMD, 0x04 + coefficent);       //	 Set Temp coefficent (max 4);
   LCDWrite(LCD_CMD, 0x10 + bias);             //	 LCD bias mode (max 15);
   LCDWrite(LCD_CMD, 0x20);                    //	 We must send 0x20 before modifying the display control mode
   LCDWrite(LCD_CMD, 0x0C);                    //	 Set display control, normal mode. 0x0D for inverse
}

void LCD_GPIO_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
	 
   
   //RCC_APB2PeriphClockCmd(RCC_NOKIA_5110, ENABLE);
	//Hung
	/* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_PORT_RST, LCD_PIN_RST, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT_CE, LCD_PIN_CE, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT_DC, LCD_PIN_DC, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT_DIN, LCD_PIN_DIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT_CLK, LCD_PIN_CLK, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT_VCC, LCD_PIN_VCC, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT_LIG, LCD_PIN_LIG, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_PORT_GND, LCD_PIN_GND, GPIO_PIN_RESET);


   GPIO_InitStructure.Pin = LCD_PIN_RST;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(LCD_PORT_RST, &GPIO_InitStructure);
	
	 GPIO_InitStructure.Pin = LCD_PIN_CE;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(LCD_PORT_CE, &GPIO_InitStructure);
	
	 GPIO_InitStructure.Pin = LCD_PIN_DC;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(LCD_PORT_DC, &GPIO_InitStructure);
	
	 GPIO_InitStructure.Pin = LCD_PIN_DIN;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(LCD_PORT_DIN, &GPIO_InitStructure);
	 
	 GPIO_InitStructure.Pin = LCD_PIN_CLK;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(LCD_PORT_CLK, &GPIO_InitStructure);
	 
	 GPIO_InitStructure.Pin = LCD_PIN_VCC;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(LCD_PORT_VCC, &GPIO_InitStructure);
	 
	 GPIO_InitStructure.Pin = LCD_PIN_LIG;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(LCD_PORT_LIG, &GPIO_InitStructure);
	 
	 GPIO_InitStructure.Pin = LCD_PIN_GND;
   GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
   GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(LCD_PORT_GND, &GPIO_InitStructure);
	 
	 HAL_GPIO_WritePin(LCD_PORT_VCC, LCD_PIN_VCC, GPIO_PIN_SET);               // set LCD_PIN_VCC; => VCC = 3.3v
   HAL_GPIO_WritePin(LCD_PORT_GND, LCD_PIN_GND, GPIO_PIN_RESET);             // clr LCD_PIN_GND; => GND = 0v
	 //GPIO_ResetBits(LCD_PORT_LIG, LCD_PIN_LIG);             // bat LED sang len
	 
	 HAL_GPIO_WritePin(LCD_PORT_LIG, LCD_PIN_LIG, GPIO_PIN_SET);               // tat LED chieu sang

}


/************************* duyhungiot.vn ************************END OF FILE****/
