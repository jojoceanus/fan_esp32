#include <driver/pcnt.h>

#ifndef _TIMERS_H
#define _TIMERS_H


// 转速测量
#define PCNT_UNIT PCNT_UNIT_0
extern volatile uint16_t pulseCount;
extern volatile bool speedReady;

// 温度湿度
extern volatile bool statusReady;

void speedTimerInit();
void statusTimerInit();

#endif