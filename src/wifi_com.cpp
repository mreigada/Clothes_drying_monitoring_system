//================================[#include guards - begin]=================================//
#include "wifi_com.h"


//========================[Declaration of Private global variables]===================//
WiFiServer server(80);


//===========================[Implementation of public functions]=====================//
void wifiComInit()
{
    WiFi.begin(SSID, PASSWORD);
  	while (WiFi.status() != WL_CONNECTED)
  	{
		delay (1000);
  	}

    server.begin();
    //WiFi.localIP() Obtenemos la IP  
	webUserInterfaceInit();
}


void wifiComUpdate()
{
    WiFiClient client = server.available();
    if (client)
	{
		while (!client.available() && client.connected())
			delay (1);

		String httpRequestLine = client.readStringUntil('\r');
		client.print(getWebUserInterface(httpRequestLine));
	}
	client.flush();
}