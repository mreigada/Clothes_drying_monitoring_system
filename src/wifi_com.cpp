//================================[#include guards - begin]=================================//
#include "wifi_com.h"


//========================[Declaration of Private global variables]===================//
WiFiServer server(80);
bool configuration = false;


//===========================[Implementation of public functions]=====================//
void wifiComInit()
{
    WiFi.begin(SSID, PASSWORD);
	for (int i = 0; i <= 3; i++)
	{
		if(WiFi.status() != WL_CONNECTED)
		{
			delay (2000);
		}

		else
		{
			configuration = true;
			break;
		}
	}

	if(configuration == true)
	{
    	server.begin();
    	//WiFi.localIP() Obtenemos la IP  
		webUserInterfaceInit();
		ledIndicatorsChangeState(WAITING_FOR_CONFIGURATION);
	}

	else
	{
		ledIndicatorsChangeState(CONNECTION_ERROR);
	}

}


void wifiComUpdate()
{
	if(configuration == true)
	{
    WiFiClient client = server.available();
    if (client)
	{
		while (!client.available() && client.connected())
			delay (1);

		client.print(getWebUserInterface(client.readStringUntil('\r')));
	}

	client.flush();
	}
}