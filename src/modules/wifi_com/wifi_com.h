//================================[#include guards - begin]=================================//
#ifndef _WIFI_COM_H_
#define _WIFI_COM_H_

#include <ESP8266WiFi.h>
#include "system_configurator.h"
#include "web_user_interface.h"


//===============================[Declaration of private defines]===========================//
#define MAX_CONNECTION_ATTEMPTS 10


//===============================[Declaration of private variables]=========================//
const char SSID[] = "Home signal";
const char password[] = "kneesocks12";
const char apiKey[] = "o.0LLdoAE6L4FxN7UjOhS7S44CcfGaBhRk";
const char host[] = "api.pushbullet.com"; 


//=============================[Declaration of private data types]==========================//
typedef enum {
   WIFI_STATE_INIT,
   WIFI_STATE_SERVER_INIT,
   WIFI_STATE_READ_REQUEST,
   WIFI_STATE_ATTEND_REQUEST,
   WIFI_STATE_ERROR
} wifiComState_t;


//===============================[Declaration of private variables]=========================//



//=====================[Declarations (prototypes) of public functions]======================//
void wifiComInit();
void wifiComUpdate();
void sendNotification(String title,String body);


//=====================[Declarations (prototypes) of private functions]=====================//
bool wifiEstablishConnection();
void wifiServerInit();
bool wifiReadRequest();
void wifiAttendRequest();
void wifiErrorTreatment();


//=================================[#include guards - end]==================================//


#endif // _WIFI_COM_H_