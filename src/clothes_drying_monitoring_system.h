//================================[#include guards - begin]=================================//
#ifndef _CLOTHES_DRYING_MONITORING_SYSTEM_H_
#define _CLOTHES_DRYING_MONITORING_SYSTEM_H_

#include <ESP8266WiFi.h>
#include "rain_sensor.h"
#include "dht_sensor.h"
#include "clothes_drying_estimator.h"
#include "wifi_com.h"
#include "led_indicators.h"


//==============================[Declaration of public defines]=============================//
#define SYSTEM_TIME_INCREMENT_MS   10


//=======================[Declarations (prototypes) of public functions]====================//
void clothesDryingMonitoringSystemInit();
void clothesDryingMonitoringSystemUpdate();


//======================[Declarations (prototypes) of private functions]====================//


//=================================[#include guards - end]==================================//

#endif // _CLOTHES_DRYING_MONITORING_SYSTEM_H_