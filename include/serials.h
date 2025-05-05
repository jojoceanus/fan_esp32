#include <BluetoothSerial.h>

#ifndef _SERIALS_H
#define _SERIAL_H

// 蓝牙串口全局变量
static BluetoothSerial SerialBT;
const char startMarker = '$';
const char endMarker = '#';
const char devideMarker = ' ';

void allSerialInit();
void serialInit();
String bluetoothMessage(int sendTag, String sendMessage);
boolean receiveMessage(int& tag, String& data);

#endif