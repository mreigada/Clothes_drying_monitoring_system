//================================[#include guards - begin]=================================//
#ifndef _WIFI_COM_H_
#define _WIFI_COM_H_

#include <ESP8266WiFi.h>
#include "system_configurator.h"
#include "web_user_interface.h"


//===============================[Declaration of private defines]===========================//
#define MAX_CONNECTION_ATTEMPTS 50


//===============================[Declaration of private variables]=========================//
const char SSID[] = "SSID";
const char password[] = "password";
const char apiKey[] = "apiKey";
const char host[] = "api.pushbullet.com"; 


//=============================[Declaration of private data types]==========================//
typedef enum {
   WIFI_STATE_INIT,
   WIFI_STATE_SERVER_INIT,
   WIFI_STATE_CHECK_CONNECTION,
   WIFI_STATE_CHECK_FOR_REQUEST,
   WIFI_STATE_ATTEND_REQUEST,
   WIFI_STATE_TRY_TO_RECONNECT,
   WIFI_STATE_CONNECTION_ERROR
} wifiComState_t;


//===============================[Declaration of private variables]=========================//



//=====================[Declarations (prototypes) of public functions]======================//
void wifiComInit();
void wifiComUpdate();
void sendNotification(String title,String body);


//=====================[Declarations (prototypes) of private functions]=====================//
bool wifiEstablishConnection();
void wifiServerInit();
bool wifiCheckConnection();
bool wifiCheckForRequest();
void wifiAttendRequest();
void wifiTryToReconnect();
void wifiErrorTreatment();


//=================================[#include guards - end]==================================//


#endif // _WIFI_COM_H_