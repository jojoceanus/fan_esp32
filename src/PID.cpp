#include <Arduino.h>

#include "PID.h"

// PID参数
float tKp = 2.0; // 比例增益
float tKi = 0.1; // 积分增益
float tKd = 1.0; // 微分增益

float hKp = 2.0; // 比例增益
float hKi = 0.1; // 积分增益
float hKd = 1.0; // 微分增益

float setTemperature = 0.0; // 设定温度 (目标值)
float setHumidity = 0.0; // 设定温度 (目标值)

// PID变量
float terror = 0.0;
float tintegral = 0.0;
float tderivative = 0.0;
float tlastError = 0.0;

float herror = 0.0;
float hintegral = 0.0;
float hderivative = 0.0;
float hlastError = 0.0;

// 温度控制
void holdTemperature(const float& setTemperature) {
    // 计算误差
    terror = setTemperature - temperature;

    // 计算积分项
    tintegral += terror;

    // 计算微分项
    tderivative = terror - tlastError;

    // 更新上一次误差
    tlastError = terror;

    // 计算PID输出
    float tpidOutput = tKp * terror + tKi * tintegral + tKd * tderivative;

    // 将PID输出映射到PWM占空比 (反向逻辑：占空比越高，风扇转速越慢)
    dutyCycle = constrain(50 - tpidOutput, 0, 100); // 50为基准值，可根据需求调整

    // 调用setPWM函数设置占空比
    setPWM(dutyCycle);
}

// 湿度控制
void holdHumidity(const float& setHumidity) {
    // 计算误差
    herror = setHumidity - humidity;

    // 计算积分项
    hintegral += herror;

    // 计算微分项
    hderivative = herror - hlastError;

    // 更新上一次误差
    hlastError = herror;

    // 计算PID输出
    float hpidOutput = hKp * herror + hKi * hintegral + hKd * hderivative;

    // 将PID输出映射到PWM占空比 (反向逻辑：占空比越高，风扇转速越慢)
    dutyCycle = constrain(50 - hpidOutput, 0, 100); // 50为基准值，可根据需求调整

    // 调用setPWM函数设置占空比
    setPWM(dutyCycle);
}