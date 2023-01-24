//================================[#include guards - begin]=================================//
#include "wifi_com.h"


//===================[Declaration of Private global objects and variables]=================//
WiFiServer server(80);
WiFiClient client;
WiFiClientSecure externalClient;
wifiComState_t wifiComState;
String httpRequestLine;


//============================[Implementation of public functions]=========================//
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
				wifiComState = WIFI_STATE_CONNECTION_ERROR;
			break;

		case WIFI_STATE_SERVER_INIT:
			wifiServerInit();
			wifiComState = WIFI_STATE_CHECK_CONNECTION;
			break;

		case WIFI_STATE_CHECK_CONNECTION:
			if(wifiCheckConnection())
				wifiComState = WIFI_STATE_CHECK_FOR_REQUEST;
			else
				wifiComState = WIFI_STATE_TRY_TO_RECONNECT;
			break;

		case WIFI_STATE_CHECK_FOR_REQUEST:
			if(wifiCheckForRequest())
				wifiComState = WIFI_STATE_ATTEND_REQUEST;
			else
				wifiComState = WIFI_STATE_CHECK_CONNECTION;
			break;

		case WIFI_STATE_ATTEND_REQUEST:
			wifiAttendRequest();
			wifiComState = WIFI_STATE_CHECK_CONNECTION;
			break;

		case WIFI_STATE_TRY_TO_RECONNECT:
			wifiTryToReconnect();
			wifiComState = WIFI_STATE_CHECK_CONNECTION;
			break;

		case WIFI_STATE_CONNECTION_ERROR:
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

	Serial.begin(9600);
	Serial.println(WiFi.localIP());
	return connectionEstablished;
}


void wifiServerInit()
{
	server.begin();
}


bool wifiCheckConnection()
{
	bool activeConnection = false;
	if(WiFi.status() != WL_CONNECTED)
		activeConnection = true;
	
	return activeConnection;
}


bool wifiCheckForRequest()
{
	bool attentionRequired = false;
	client = server.available();
    if(client)
	{
		while (!client.available() && client.connected())
			delay (1);

		setSystemConfigurationUsingHttpLine(client.readStringUntil('\r'));
		attentionRequired = true;
	}

	return attentionRequired;
}


void wifiAttendRequest()
{
	client.print(getWebUserInterface());
	client.flush();
}


void wifiTryToReconnect()
{
  	WiFi.disconnect();
  	WiFi.reconnect();
	delay(1000);
}

void wifiErrorTreatment()
{
	setSystemConfiguration(ERROR_CONFIG);
}