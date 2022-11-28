//================================[#include guards - begin]=================================//
#include "wifi_com.h"

WiFiServer server(80);
const char* ssid = "Home signal";
const char* password = "kneesocks12";
bool alreadyConfigured = false;


const char index_html[] = R"rawliteral(	
<!DOCTYPE html><html><head>
<title>Clothes drying monitoring system</title>
<style>
.titl
{
text-align: center;
}
.configBox
{
width: 350px;
height: 160px;
margin: 12px;
border: solid black 1px;
border-radius: 8px;
padding: 6px;
background-color: #f2f2f2;
}
body
{
display: flex;
align-items: center;
justify-content: center;
margin: 0 auto;
height: 80vh;
background-color: #f1f1f1;
}
select
{
margin-bottom: 10px;
margin-top: 10px;
border-radius: 2px;
}
h1
{
color: green;
}
</style>
</head>
<body>
<center>
<h1>Clothes drying monitoring system</h1>
<div class=configBox>
<form action=/get>
<label for=cloth>Clothing thickness</label>
<select name=clothingThickness id=cloth>
<option value=THIN>THIN</option>
<option value=THICK>THICK</option>
</select>
</br>
</br>
<label for=rainsense>Rain Sensor</color>
<select name=rainSensor id=rainsense>
<option value=ENABLED>ENABLED</option>
<option value=DISABLED>DISABLED</option>
</select>
</br>
</br>
</select>
<label for=rainsense>Measured physical magnitudes</color>
<select name=physicalmags id=physicalmags>
<option value=VISIBLE>VISIBLE</option>
<option value=NOT VISIBLE>NOT VISIBLE</option>
</select>
</br>
</br>
</br>
<input type=submit value="Start monitoring">
</form>
</div>
</body>
</html>
)rawliteral";


const char drying_html[] = R"rawliteral(
<!DOCTYPE html><html><head>
<title>Clothes drying monitoring system</title>
<meta http-equiv="refresh" content="10">
<style>
.configBox
{
margin: 12px;
border: solid black 1px;
border-radius: 8px;
padding: 6px;
background-color: #f2f2f2;
}
body
{
display: flex;
align-items: center;
justify-content: center;
margin: 0 auto;
height: 80vh;
background-color: #f1f1f1;
}
</style>
</head>
<body>
<center>
</br>
<div class=configBox>
<h2>Estimated clothes drying time: 
)rawliteral";


const char rainSensorEnable_html[] = R"rawliteral(
<h2>Rain state: )rawliteral";


const char temperature_html[] = R"rawliteral(
<h2>Temperature[&deg;C]: )rawliteral";

const char humidity_html[] = R"rawliteral(
<h2>Humidity[%]: )rawliteral";


void wifiComInit()
{
    WiFi.begin(ssid, password);
  	while (WiFi.status() != WL_CONNECTED)
  	{
		delay (1000);
  	}

    server.begin(); //Iniciamos el servidor
    //WiFi.localIP() Obtenemos la IP  
}


void wifiComUpdate()
{
    WiFiClient client = server.available();
    if (client)
	{
		while (!client.available() && client.connected())
			delay (1);

		String primeraLinea = client.readStringUntil('\r');
		if(primeraLinea.indexOf ("favicon") == -1 && primeraLinea != "GET / HTTP/1.1")
    	{
			if(primeraLinea.indexOf("clothingThickness=THIN") != -1)
			{
				if(!alreadyConfigured)
				{
					enableClothesDryingEstimator(THIN);					
				}

				client.print(drying_html);
				client.print(readDryingClothesEstimation());
			}

			if(primeraLinea.indexOf("clothingThickness=THICK") != -1)
			{
				if(!alreadyConfigured)
					enableClothesDryingEstimator(THICK); 

				client.print(drying_html);
				client.print(readDryingClothesEstimation());
			}

			if(primeraLinea.indexOf("rainSensor=ENABLED") != -1)
			{
				if(!alreadyConfigured)
					enableRainSensor();

				client.print(rainSensorEnable_html);
				client.print(rainSensorReadStateDescription());
			}

			if(primeraLinea.indexOf("rainSensor=DISABLED") != -1)
			{
				if(!alreadyConfigured)
					disableRainSensor();
			}

			if(primeraLinea.indexOf("physicalmags=VISIBLE") != -1)
			{
				client.print(temperature_html);
				client.print(dhtSensorReadTemperature());
				client.println(humidity_html);
				client.print(dhtSensorReadHumidity());
			}

			client.println("</div>");
			client.println("</br>");
			client.println("<div style='text-align:center;'>");
			client.println("<button onClick=location.href='./'>Back to main menu</button>");			
			client.println("</div>");
			alreadyConfigured = true;
    	}

		if(primeraLinea == "GET / HTTP/1.1")
		{	
			if(alreadyConfigured == true)
			{
				alreadyConfigured = false;
				disableClothesDryingEstimator();
				disableRainSensor();
			}
			client.print(index_html);
		}

		client.flush();
	}
}