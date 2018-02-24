#ifndef __DS18B20_H
#define __DS18B20_H
//Thu vien cho DS1802

#include "main.h"
#include "stm32f1xx_hal.h"
#include "oneWire.h"

#define SKIP_ROM 0xCC
#define READ_ROM 0x33
#define MATCH_ROM 0x55
#define SEARCH_ROM 0xF0

#define ALARM_SEARCH 0xEC


float ds18b20_read(void);
  
#endif /* __DS18B20_H */