#include <driver/pcnt.h>
#include "timers.h"

#ifndef _MOTOR_H
#define _MOTOR_H

// 转速控制配置
#define EN_PIN GPIO_NUM_23
#define PWM_PIN GPIO_NUM_33
#define PWM_FREQ 25000
extern int dutyCycle;

// 模拟自然风
#define PWM_MIN_DUTY_CYCLE 0  // 最小占空比
#define PWM_MAX_DUTY_CYCLE 80 // 最大占空比
#define FADE_STEP 2            // 每次占空比变化的步长
#define RANDOM_INTERVAL 5000   // 随机生成新目标值的时间间隔（单位：毫秒）
extern int autoControl;


// 转速相关
#define PCNT_CHANNEL PCNT_CHANNEL_0
#define SAMPLE_TIME_MS 500
#define PAULSE_PER_ROTATION 18.0f
#define PCNT_HIGH_LIMIT 32767
#define PCNT_LOW_LIMIT -1
#define PAULSE_COUNT_PIN GPIO_NUM_14

//void setDutyCycle(int dc);
void setPWM(int dc);
void motorInit();
void simulateNaturalWind();

#endif