//================================[#include guards - begin]=================================//
#ifndef _RAIN_SENSOR_H_
#define _RAIN_SENSOR_H_

#include <ESP8266WiFi.h>
#include "utilities.h"


//===============================[Declaration of private defines]===========================//
#define DEBOUNCE_RAIN_SENSOR_TIME_MS 1500
#define rainSensorDigitalPin D5
#define rainSensorAnalogPin A0
#define NO_RAIN_DESCRIPTION "there is no rain"
#define DRIZZLE_RAIN_DESCRIPTION "drizzle"
#define REGULAR_RAIN_DESCRIPTION "regular rain"
#define HEAVY_RAIN_DESCRIPTION "heavy rain"

//==============================[Declaration of private data types]=========================//
typedef enum
{
    ON,
    OFF
} rainSensorState_t;


//=====================[Declarations (prototypes) of public functions]======================//
void rainSensorInit();
void enableRainSensor();
void disableRainSensor();
char* rainSensorReadStateDescription();
void rainSensorUpdate();



//=====================[Declarations (prototypes) of private functions]=====================//        
void turnOnTreatment();
void turnOffTreatment();
void updateStateDescription();
int getAnalogRainSensorLecture();
void activateRainSensorUpdateFlag();

//=================================[#include guards - end]==================================//

#endif // _RAIN_SENSOR_H_