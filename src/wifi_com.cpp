//================================[#include guards - begin]=================================//
#include "wifi_com.h"


//========================[Declaration of Private global variables]===================//
WiFiServer server(80);
WiFiClient client;
wifiComState_t wifiComState;
String httpRequestLine;


//===========================[Implementation of public functions]=====================//
void wifiComInit()
{
    wifiComState = WIFI_STATE_INIT;
}


void wifiComUpdate()
{
	 switch (wifiComState) 
	 {
		case WIFI_STATE_INIT:
			if(wifiEstablishConnection())
				wifiComState = WIFI_STATE_SERVER_INIT;
			else
				wifiComState = WIFI_STATE_ERROR;
			break;

		case WIFI_STATE_SERVER_INIT:
			wifiServerInit();
			wifiComState = WIFI_STATE_READ_REQUEST;
			break;

		case WIFI_STATE_READ_REQUEST:
			wifiReadRequest();
			wifiComState = WIFI_STATE_SEND_HTML;
			break;

		case WIFI_STATE_SEND_HTML:
			wifiSendHtml();
			wifiComState = WIFI_STATE_READ_REQUEST;
			break;

		case WIFI_STATE_ERROR:
			wifiErrorTreatment();
			break;
	}
}


//===========================[Implementation of private functions]=====================//
bool wifiEstablishConnection()
{
	bool connectionEstablished = false;	

    WiFi.begin(SSID, PASSWORD);

	for(int i = 0; i <= MAX_CONNECTION_ATTEMPTS; i++)
	{
		if(WiFi.status() != WL_CONNECTED)
			delay(1000);

		else
		{
			connectionEstablished = true;
			break;
		}
	}

	return connectionEstablished;
}


void wifiServerInit()
{
	server.begin();
}


void wifiReadRequest()
{
	client = server.available();
    if(client)
	{
		while (!client.available() && client.connected())
			delay (1);

		setSystemConfigurationUsingHttpLine(client.readStringUntil('\r'));
	}
}


void wifiSendHtml()
{
	client.print(getWebUserInterface());
	client.flush();
}


void wifiErrorTreatment()
{
	setSystemConfiguration(ERROR_CONFIG);
}