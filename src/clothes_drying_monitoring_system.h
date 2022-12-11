//================================[#include guards - begin]=================================//
#ifndef _CLOTHES_DRYING_MONITORING_SYSTEM_H_
#define _CLOTHES_DRYING_MONITORING_SYSTEM_H_

#include <ESP8266WiFi.h>
#include "led_indicators.h"
#include "rain_sensor.h"
#include "dht_sensor.h"
#include "clothes_drying_estimator.h"
#include "wifi_com.h"
#include "system_configuration.h"
#include "web_user_interface.h"


//==============================[Declaration of public defines]=============================//
#define SYSTEM_TIME_DELAY_MS   50


//=======================[Declarations (prototypes) of public functions]====================//
void clothesDryingMonitoringSystemInit();
void clothesDryingMonitoringSystemUpdate();


//=================================[#include guards - end]==================================//

#endif // _CLOTHES_DRYING_MONITORING_SYSTEM_H_