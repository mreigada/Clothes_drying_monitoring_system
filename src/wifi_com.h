//================================[#include guards - begin]=================================//
#ifndef _WIFI_COM_H_
#define _WIFI_COM_H_

#include <ESP8266WiFi.h>
#include "clothes_drying_estimator.h"
#include "rain_sensor.h"
#include "dht_sensor.h"

void wifiComInit();
void wifiComUpdate();


#endif //_WIFI_COM_H_