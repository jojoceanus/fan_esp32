#include "serials.h"
#include <Arduino.h>

void allSerialInit()
{
	// 初始化串口监视器，波特率设置为115200
	Serial.begin(115200);
	Serial.println("Initializing Serial...");

	// 初始化蓝牙模块
	SerialBT.begin("ESP32_BLUETOOTH"); // 设置蓝牙设备名称
	Serial.println("Waiting for Bluetooth connection...");

	// 等待蓝牙连接
	while (!SerialBT) {
		delay(1000); // 等待1秒
		Serial.print(".");
	}

	// 连接成功后打印信息
	Serial.println("");
	Serial.println("Bluetooth connected!");
}

void serialInit()
{
    // 初始化串口监视器，波特率设置为115200
	Serial.begin(115200);
	Serial.println("Initializing Serial...");
}

String bluetoothMessage(String sendTag, String sendMessage) {
	String data = "";
	data += startMarker;
	data += sendTag;
	data += devideMarker;
	data += sendMessage;
	data += endMarker;
	return data;
}

int readMessage = 0;
int tagordata = 0;

boolean receiveMessage(String& tag, String& data)
{
	if (SerialBT.available()) 
	{
		tag = "";
		data = "";
		while (SerialBT.available()) 
		{
		char c = SerialBT.read();
		if (readMessage) 
		{
			if (c == startMarker) 
			{
			tag = "";
			data = "";
			tagordata = 1;
			} 
			else if (c == devideMarker) 
			{
			tagordata = 2;
			} 
			else if (c == endMarker) 
			{
			readMessage = 0;
			break;
			} 
			else if (tagordata == 1) 
			{
			tag += c;
			} 
			else if (tagordata == 2) 
			{
			data += c;
			}
		} 
		else 
		{
			if (c == startMarker) 
			{
			readMessage = 1;
			tagordata = 1;
			}
		}
		}

		if (data.length() > 0) {
		Serial.print("tag|");
		Serial.print(tag);
		Serial.println("|");
		Serial.print("data|");
		Serial.print(data);
		Serial.println("|");
		}

		return 1;
	}

	return 0;
}