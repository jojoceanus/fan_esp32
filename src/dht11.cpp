#include "dht11.h"

DHT dht(DHT_PIN, DHT_TYPE);
float humidity = 0;
float temperature = 0;

// DHT初始化延时
Ticker initDhtTicker;

// DHT初始化回调
void onDhtInit() 
{
	statusTimerInit();
	Serial.println("DHT sensor initialized.");
}

void dht11Init()
{
	// 初始化DHT
	dht.begin();

	// 设置一个一次性定时器，在1000ms后触发onDhtInit函数
  	initDhtTicker.once_ms(1000, onDhtInit);
}

void readStatus(float& ctemperature, float& chumidity)
{
	chumidity = dht.readHumidity();
	ctemperature = dht.readTemperature();
	delay(5);
}

void readStatus()
{
	humidity = dht.readHumidity();
	temperature = dht.readTemperature();
	delay(5);
}