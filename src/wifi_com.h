//================================[#include guards - begin]=================================//
#ifndef _WIFI_COM_H_
#define _WIFI_COM_H_

#include <ESP8266WiFi.h>
#include "system_configuration.h"
#include "web_user_interface.h"


//===============================[Declaration of private defines]===========================//
#define MAX_CONNECTION_ATTEMPTS 10


//===============================[Declaration of private variables]===========================//
const char SSID[] = "SSID";
const char password[] = "password";
const char apiKey[] = "apiKey";
const char host[] = "api.pushbullet.com"; 


//=============================[Declaration of private data types]==========================//
typedef enum {
   WIFI_STATE_INIT,
   WIFI_STATE_SERVER_INIT,
   WIFI_STATE_READ_REQUEST,
   WIFI_STATE_SEND_HTML,
   WIFI_STATE_ERROR
} wifiComState_t;


//===============================[Declaration of private variables]===========================//




//=====================[Declarations (prototypes) of public functions]======================//
void wifiComInit();
void wifiComUpdate();
void sendNotification(String titulo,String mensaje);

//=====================[Declarations (prototypes) of private functions]======================//
bool wifiEstablishConnection();
void wifiServerInit();
void wifiReadRequest();
void wifiSendHtml();
void wifiErrorTreatment();

//=================================[#include guards - end]==================================//


#endif // _WIFI_COM_H_