//==================================[Libraries]==================================//
#include <ESP8266WiFi.h>
#include "clothes_drying_monitoring_system.h"


//=======[Setup function, the program entry point after power on or reset]=======//
void setup()
{
	clothesDryingMonitoringSystemInit();
}

void loop()
{
	clothesDryingMonitoringSystemUpdate();
}