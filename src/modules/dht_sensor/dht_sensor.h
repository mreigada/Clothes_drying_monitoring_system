//================================[#include guards - begin]=================================//
#ifndef _DHT_SENSOR_H_
#define _DHT_SENSOR_H_

#include <ESP8266WiFi.h>


//===============================[Declaration of private defines]===========================//
#define MIN_INTERVAL 2000
#define DHT_SENSOR_PIN D5


//=====================[Declarations (prototypes) of public functions]======================//
void dhtSensorInit(void);
void dhtSensorUpdate();
float dhtSensorReadTemperature();
float dhtSensorReadHumidity();
float convertCtoF(float);
float convertFtoC(float);


//=====================[Declarations (prototypes) of private functions]=====================//        
boolean read(bool force=false);
uint32_t expectPulse(bool level);
void dhtSensorUpdateTemperature(bool S=false, bool force=false);
void dhtSensorUpdateHumidity(bool force=false);

//=================================[#include guards - end]==================================//

#endif //_DHT_SENSOR_H_