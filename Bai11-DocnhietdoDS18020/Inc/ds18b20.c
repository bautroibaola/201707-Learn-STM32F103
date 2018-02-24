#include "main.h"
#include "stm32f1xx_hal.h"
#include "ds18b20.h"

float ds18b20_read(void){
	 uint8_t busy=0, temp1, temp2;
	 uint16_t temp3,TimeOut;
	 float result;
	 oneWire_reset();
	 OneWire_WriteByte(SKIP_ROM); //(0xCC);
	 OneWire_WriteByte(0x44);
	 while ((busy==0)&&TimeOut<2000)
	 {
			busy = OneWire_Read();
	 }
	 OneWire_reset();
	 OneWire_WriteByte(0xCC);
	 OneWire_WriteByte(0xBE);
	 temp1 = OneWire_ReadByte();
	 temp2 = OneWire_ReadByte();
	 //
	 temp3 = temp2;
	 temp3<<=8;
	 temp3|=temp1;
	 result = (float) temp3 / 16.0;
	 delay_ms(200);
	 return(result);
}
  