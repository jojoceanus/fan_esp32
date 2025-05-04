#include <Arduino.h>

#include "dht11.h"
#include "motors.h"
#include "serials.h"
#include "timers.h"
#include "PID.h"

int tag = 0x00;
String data = "";

enum Tags {
	NATW = 0x01,
	HOLDH,
	HOLDT,
	SPEED
};

void setup() {
	// 电机初始化
	motorInit();
	// 串口初始化
	allSerialInit();
	// dht11初始化
	dht11Init();
}

void loop() {
	// 从蓝牙串口读取数据
	if (receiveMessage(tag, data)) {
		if (tag == NATW) {
			autoControl = 1;
		}
		else if (tag == HOLDH) {
			autoControl = 2;
			setHumidity = data.toInt();
		}
		else if (tag == HOLDT) {
			autoControl = 3;
			setTemperature = data.toInt();
		}
		else if (tag == SPEED) {
			autoControl = 0;
			// 缺检查
			setPWM(100 - data.toInt());
		}
		else {
			Serial.println("-----error-----");
			Serial.println(tag);
			Serial.println(data);
			Serial.println("-----error-----");
		}
		tag = 0x00;
		data = "";
	}

	if (autoControl == 1) {
		simulateNaturalWind();
	}
	else if (autoControl == 2) {
		readStatus(temperature, humidity);
		holdHumidity(setHumidity);
		delay(500);
	}
	else if (autoControl == 3) {
		readStatus(temperature, humidity);
		holdTemperature(setTemperature);
		delay(500);
	}
	
	// 处理脉冲计数数据
	if (speedReady) {
		noInterrupts();
		uint16_t count = pulseCount;
		speedReady = false;
		interrupts();

		float result = count / PAULSE_PER_ROTATION / (SAMPLE_TIME_MS / 1000.0f);
		
		String formatresult = String(result, 1);
		Serial.println(count);
		//Serial.println(bluetoothMessage("SPEED", formatresult));
		SerialBT.print(bluetoothMessage("SPEED", formatresult));
	}
	
	// 处理状态数据
	if (statusReady) {
		statusReady = false;
		readStatus(temperature, humidity);

		Serial.println(bluetoothMessage("HUMIDITY", String(humidity, 1)));
		Serial.println(bluetoothMessage("TEMPERATURE", String(temperature, 1)));
		SerialBT.print(bluetoothMessage("HUMIDITY", String(humidity, 1)));
		SerialBT.print(bluetoothMessage("TEMPERATURE", String(temperature, 1)));
	}
}