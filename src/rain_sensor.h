//================================[#include guards - begin]=================================//
#ifndef _RAIN_SENSOR_H_
#define _RAIN_SENSOR_H_

#include <ESP8266WiFi.h>


//===============================[Declaration of private defines]===========================//
#define RAIN_SENSOR_DIGITAL_PIN D5
#define RAIN_SENSOR_ANALOG_PIN A0
#define DEBOUNCE_RAIN_SENSOR_TIME_MS   10
#define DRIZZLE_UPPER_LIMIT   1024
#define DRIZZLE_LOWER_LIMIT   600
#define REGULAR_RAIN_LOWER_LIMIT   400

const char noRainDescription[] = "there is no rain";
const char drizzleRainDescription[] = "drizzle";
const char regularRainDescription[] = "regular rain";
const char heavyRainDescription[] = "heavy rain";


//==============================[Declaration of private data types]=========================//
typedef enum
{
    ON,
    OFF
} rainSensorActivation_t;

typedef enum
{
    NO_RAIN,
    DRIZZLE_RAIN,
    REGULAR_RAIN,
    HEAVY_RAIN
} rainState_t;


//=====================[Declarations (prototypes) of public functions]======================//
void rainSensorInit();
void rainSensorUpdate();
void enableRainSensor();
void disableRainSensor();
rainState_t readRainState();
const char* readRainStateDescription();


//=====================[Declarations (prototypes) of private functions]=====================//        
void turnOnTreatment();
void turnOffTreatment();
void updateRainState();
int getAnalogRainSensorLecture();
void activateRainSensorUpdateIndicator();

//=================================[#include guards - end]==================================//

#endif // _RAIN_SENSOR_H_