//================================[#include guards - begin]=================================//
#include "wifi_com.h"


//========================[Declaration of Private global variables]===================//
WiFiServer server(80);
WiFiClient client;
WiFiClientSecure externalClient;
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


void sendNotification(String title, String body) 
{
	externalClient.setInsecure();
	externalClient.connect(host, 443);

  	String message = "{\"type\": \"note\", \"title\": \"" + title + "\", \"body\": \"" + body + "\"}\r\n";

  	externalClient.print(String("POST ") + "/v2/pushes" + " HTTP/1.1\r\n" + "Host: api.pushbullet.com" + "\r\n" + "Authorization: Bearer " + apiKey + "\r\n" +
               "Content-Type: application/json\r\n" + "Content-Length: " + String(message.length()) + "\r\n\r\n" + message);
}


//===========================[Implementation of private functions]=====================//
bool wifiEstablishConnection()
{
	bool connectionEstablished = false;	

    WiFi.begin(SSID, password);

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