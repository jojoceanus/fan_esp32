#include <DHT.h>
#include <Ticker.h>

#include "timers.h"

#ifndef _DHT11_H
#define _DHT11_H

#define DHT_PIN GPIO_NUM_15
#define DHT_TYPE DHT11

extern DHT dht;
extern float humidity;
extern float temperature;

void dht11Init();
void readStatus(float& ctemperature, float& chumidity);

#endif