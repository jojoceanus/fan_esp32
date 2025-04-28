#include <BluetoothSerial.h>

#ifndef _SERIALS_H
#define _SERIAL_H

// 蓝牙串口全局变量
static BluetoothSerial SerialBT;
const char startMarker = '$';
const char endMarker = '#';
const char devideMarker = ' ';

void allSerialInit();
void SerialInit();
String bluetoothMessage(String sendTag, String sendMessage);
boolean receiveMessage(String& tag, String& data);

#endif