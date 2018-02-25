#include "ds1307.h"

extern I2C_HandleTypeDef hi2c1;

uint8_t rtcTxBuffer[64];
uint8_t rtcRxBuffer[64];

void i2cInit(void); //Khoi tao giao tiep I2C
void keypadInit(void) //Khoi tao IO cho ban phim cai dat gio
{
}

char bcd2dec(char bcd) //Ham chuyen tu ma BCD sang THAP PHAN
{
	char H, L; //Bit high, bit low
	char ch, dv, dec; //So hang chuc, hang don vi
	H = bcd >> 4;
	L = bcd & 0x0F;
	ch = H*10;
	dv = L;
	dec = ch + dv;
	return dec;
}

char dec2bcd(char dec) //Ham chuyen ma THAP PHAN san BCD
{
	char ch, dv; //chu so hang chuc va hang don vi
	char H, L, bcd;
	
	ch = dec / 10;
	dv = dec % 10; //chia lay phan nguyen
	
	H = ch << 4;
	L = dv;
	bcd = H | L;
	return bcd;
	
}

void rtcWriteTime(char hrs, char min, char sec) // Ham cai dat gio phut giay
{
	rtcTxBuffer[0] = 0x00; // Dia chi cua thanh ghi giay
	rtcTxBuffer[1] = dec2bcd(sec) & 0x7F; //truyen gia tri giay cho DS1307, dam bao CH = 0
	rtcTxBuffer[2] = dec2bcd(min); //Truyen gia tri cho thanh ghi phut
	rtcTxBuffer[3] = dec2bcd(hrs) & 0x3F; // Truyen gia tri cho thanh ghi gio, che do 24H
	
	HAL_I2C_Master_Transmit(&hi2c1, DS1307_ADDR_W, rtcTxBuffer, 4, 100);
	//&hi2c1 => Chon kenh I2C1
  //DS1307_ADDR_W => Dia chi cua DS1307 che do ghi
	//rtcTxBuffer => Mang du lieu can truyen
	//4 => co 4 phan tu
	//100 => Thoi gian TimeOut la 100ms
	
	HAL_Delay(100);
	
}

void rtcWriteDate(char day, char date, char mth, char yrs) //Ham cai dat thu ngay thang nam
{
	rtcTxBuffer[0] = 0x03; // Dia chi cua thanh ghi Thu
	rtcTxBuffer[1] = dec2bcd(day); //truyen gia tri Thu 
	rtcTxBuffer[2] = dec2bcd(date); //truyen gia tri Ngay
	rtcTxBuffer[3] = dec2bcd(mth); //Truyen gia tri cho thanh ghi Thang
	rtcTxBuffer[4] = dec2bcd(yrs); // Truyen gia tri cho thanh ghi Nam
	
	HAL_I2C_Master_Transmit(&hi2c1, DS1307_ADDR_W, rtcTxBuffer, 5, 100);
	//&hi2c1 => Chon kenh I2C1
  //DS1307_ADDR_W => Dia chi cua DS1307 che do ghi
	//rtcTxBuffer => Mang du lieu can truyen
	//5 => co 5 phan tu
	//100 => Thoi gian TimeOut la 100ms
	
	HAL_Delay(100);
}

void rtcReadTime(char *hrs, char *min, char *sec) //Ham doc gio phut giay
{
	rtcTxBuffer[0] = 0x00; // Dia chi cua thanh ghi giay
	HAL_I2C_Master_Transmit(&hi2c1, DS1307_ADDR_W, rtcTxBuffer, 1, 100);
	
	HAL_I2C_Master_Receive(&hi2c1, DS1307_ADDR_R, rtcRxBuffer, 3, 100);
	//&hi2c1 => Chon kenh I2C1
  //DS1307_ADDR_R => Dia chi cua DS1307 che do doc
	//rtcRxBuffer => Mang du lieu can truyen
	//3 => co 3 phan tu, cho gio phut giay
	//100 => Thoi gian TimeOut la 100ms
	
	*sec = bcd2dec(rtcRxBuffer[0]);
	*min = bcd2dec(rtcRxBuffer[1]);
	*hrs = bcd2dec(rtcRxBuffer[2]);
	
	HAL_Delay(100);
	
	
}


void rtcReadDate(char *day, char *date, char *mth, char *yrs) // Ham doc thu ngay thang nam
{
	rtcTxBuffer[0] = 0x03; // Dia chi cua thanh ghi Thu
	
	HAL_I2C_Master_Transmit(&hi2c1, DS1307_ADDR_W, rtcTxBuffer, 1, 100);
	
	HAL_I2C_Master_Receive(&hi2c1, DS1307_ADDR_R, rtcRxBuffer, 4, 100);
	//&hi2c1 => Chon kenh I2C1
  //DS1307_ADDR_R => Dia chi cua DS1307 che do doc
	//rtcRxBuffer => Mang du lieu can truyen
	//3 => co 3 phan tu, cho gio phut giay
	//100 => Thoi gian TimeOut la 100ms
	
	*day = bcd2dec(rtcRxBuffer[0]);
	*date = bcd2dec(rtcRxBuffer[1]);
	*mth = bcd2dec(rtcRxBuffer[2]);
	*yrs = bcd2dec(rtcRxBuffer[3]);
	
	HAL_Delay(100);
}

void keySetTime(void); //Ham set thoi gian bang phim nhan

