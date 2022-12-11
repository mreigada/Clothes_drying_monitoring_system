//================================[#include guards - begin]=================================//
#ifndef _SYSTEM_CONFIGURATION_H_
#define _SYSTEM_CONFIGURATION_H_

#include <ESP8266WiFi.h>
#include "clothes_drying_estimator.h"
#include "rain_sensor.h"
#include "dht_sensor.h"
#include "led_indicators.h"
#include "web_user_interface.h"


//===============================[Declaration of private defines]===========================//


//==============================[Declaration of private data types]=========================//
typedef enum
{
	INIT_CONFIG,
	IDLE_CONFIG,
    OUTDOOR_THIN_CONFIG,
    OUTDOOR_THICK_CONFIG,
	INDOOR_THIN_CONFIG,
	INDOOR_THICK_CONFIG,
	ENV_VARIABLES_CONFIG,
	ERROR_CONFIG,
	UNKNOWN_CONFIG
} configuration_t;

//=====================[Declarations (prototypes) of public functions]======================//
void systemConfigurationInit();
void systemConfigurationUpdate();
void setSystemConfiguration(configuration_t newConfiguration);
void setSystemConfigurationUsingHttpLine(String httpRequestLine);


//=====================[Declarations (prototypes) of private functions]=====================//
void configureSystemInit();
void configureSystemAsIdle();
void configureSystemForOutdoorThinClothes();
void configureSystemForOutdoorThickClothes();
void configureSystemForIndoorThinClothes();
void configureSystemForIndoorThickClothes();
void configureSystemForEnviromentalVars();
void configureSystemForErrorIndication();


//=================================[#include guards - end]==================================//

#endif // SYSTEM_CONFIGURATION