//================================[#include guards - begin]=================================//
#include "wifi_com.h"

WiFiServer server(80);
const char* ssid = "Home signal";
const char* password = "kneesocks12";


void wifiComInit()
{
    WiFi.begin(ssid, password);
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