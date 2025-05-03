#include "dht11.h"
#include "motors.h"

#ifndef _PID_H
#define _PID_H

extern float setTemperature;
extern float setHumidity;

void holdHumidity(const float& setHumidity);
void holdTemperature(const float& setTemperature);

#endif