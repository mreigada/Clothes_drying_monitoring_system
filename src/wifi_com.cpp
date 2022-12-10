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
				wifiComState = WIFI_READ_REQUEST;
			else
				wifiComState = WIFI_STATE_ERROR;
			break;

		case WIFI_READ_REQUEST:
			wifiReadRequest();
			wifiComState = WIFI_STATE_SEND_HTML;
			break;

		case WIFI_STATE_SEND_HTML:
			wifiSendHtml();
			wifiComState = WIFI_READ_REQUEST;
			break;

		case WIFI_STATE_ERROR:
			wifiErrorTreatment();
			break;
	}
}


//===========================[Implementation of private functions]=====================//
bool wifiEstablishConnection()
{
	bool establishedConnection = false;	

    WiFi.begin(SSID, PASSWORD);

	for(int i = 0; i <= MAX_CONNECTION_ATTEMPTS; i++)
	{
		if(WiFi.status() != WL_CONNECTED)
		{
			delay(2000);
		}

		else
		{
			server.begin();
			webUserInterfaceInit();
			ledIndicatorsChangeState(WAITING_FOR_CONFIGURATION);
			establishedConnection = true;
			break;
		}
	}

	return establishedConnection;
}


void wifiReadRequest()
{
    client = server.available();

    if(client)
	{
		while (!client.available() && client.connected())
			delay (1);

		httpRequestLine = client.readStringUntil('\r');
	}
}


void wifiSendHtml()
{
	client.print(getWebUserInterface(httpRequestLine));
	client.flush();
}


void wifiErrorTreatment()
{
	ledIndicatorsChangeState(CONNECTION_ERROR);
}