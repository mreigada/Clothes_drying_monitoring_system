//================================[#include guards - begin]=================================//
#ifndef _DHT_SENSOR_H_
#define _DHT_SENSOR_H_

#include <ESP8266WiFi.h>


//===============================[Declaration of private defines]===========================//
#define MIN_INTERVAL 2000


//=====================[Declarations (prototypes) of public functions]======================//
void dhtSensorInit(void);
void dhtSensorUpdate();
float dhtSensorReadTemperature();
float dhtSensorReadHumidity();
float convertCtoF(float);
float convertFtoC(float);
float computeHeatIndex(float temperature, float percentHumidity, bool isFahrenheit=true);


//=====================[Declarations (prototypes) of private functions]=====================//        
boolean read(bool force=false);
uint32_t expectPulse(bool level);
void dhtSensorUpdateTemperature(bool S=false, bool force=false);
void dhtSensorUpdateHumidity(bool force=false);

//=================================[#include guards - end]==================================//

#endif //_DHT_SENSOR_H_