#include "dht11.h"
#include "motors.h"

#ifndef _PID_H
#define _PID_H

extern float setTemperature;
extern float setHumidity;
extern int dutyCycle;

void holdHumidity(const float& setHumidity);
void holdTemperature(const float& setTemperature);
void holdHumidityL(const float& setHumidity);
void holdTemperatureL(const float& setTemperature);

#endif