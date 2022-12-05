//================================[#include guards - begin]=================================//
#ifndef _WIFI_COM_H_
#define _WIFI_COM_H_

#include <ESP8266WiFi.h>
#include "web_user_interface.h"


//===============================[Declaration of private defines]===========================//
#define SSID "SSID"
#define PASSWORD "PASSWORD"

//=====================[Declarations (prototypes) of public functions]======================//
void wifiComInit();
void wifiComUpdate();

//=================================[#include guards - end]==================================//

#endif // _WIFI_COM_H_