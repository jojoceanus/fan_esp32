#include "timers.h"
#include <Arduino.h>

// 转速测量
hw_timer_t* speedTimer = NULL;
volatile bool speedReady = false;
// 脉冲计数
volatile uint16_t pulseCount = 0;

// 温度湿度
hw_timer_t* statusTimer = NULL;
volatile bool statusReady = false;

// 转速监测中断函数
void IRAM_ATTR onSpeedTimer() 
{
    int16_t count;
    pcnt_get_counter_value(PCNT_UNIT, &count);
    pulseCount = count;          // 获取当前计数值
    pcnt_counter_clear(PCNT_UNIT); // 清零计数器
    speedReady = true;            // 设置数据就绪标志
}

// 定时器中断处理函数 状态
void IRAM_ATTR onStatusTimer() 
{
    statusReady = true;            // 设置数据就绪标志
}

void speedTimerInit()
{
    // 配置硬件定时器（500ms间隔读取转速数据）
    speedTimer = timerBegin(0, 80, true);                   // 使用定时器0，1MHz时钟
    timerAttachInterrupt(speedTimer, &onSpeedTimer, true);  // 绑定中断处理函数
    timerAlarmWrite(speedTimer, 500000, true);              // 500ms周期
    timerAlarmEnable(speedTimer);                           // 启用定时器
}

void statusTimerInit()
{
    // DHT初始化完成后的回调函数
    statusTimer = timerBegin(1, 80, true);                    // 使用定时器1，1MHz时钟
    timerAttachInterrupt(statusTimer, &onStatusTimer, true);  // 绑定中断处理函数
    timerAlarmWrite(statusTimer, 5000000, true);              // 5000ms周期
    timerAlarmEnable(statusTimer);                            // 启用定时器, DHT初始化完成后启用
}