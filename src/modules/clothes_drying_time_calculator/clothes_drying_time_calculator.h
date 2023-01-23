//================================[#include guards - begin]=================================//
#ifndef _CLOTHES_DRYING_TIME_CALCULATOR_H_
#define _CLOTHES_DRYING_TIME_CALCULATOR_H_

#include <ESP8266WiFi.h>
#include "dht_sensor.h"
#include "time_utilities.h"
#include "math.h"


//==============================[Declaration of public defines]=============================//
#define dhtSensorPin D1
#define TIMER1_25_SECONDS_TICKS_EQUIVALENCE 7812500
#define SECONDS_BETWEEN_UPDATE 25


//===============================[Declaration of private variables]=========================//
const char dryingTimeElapsedMsg[] = "The estimated laundry drying time has already elapsed.";


//==============================[Declaration of public data types]==========================//
typedef enum
{
    THIN,
    THICK
} clothingThickness_t;

typedef enum
{
    RUNNING,
    STOPPED
} runningState_t;


//=======================[Declarations (prototypes) of public functions]====================//
void clothesDryingEstimatorInit();
void clothesDryingEstimatorUpdate();
void enableClothesDryingEstimator(clothingThickness_t clothingThickness);
void disableClothesDryingEstimator();
float calculateSecondsToDryClothes(float temperature, float humidity, clothingThickness_t thickness);
runningState_t readClothesDryingEstimationState();
char* readDryingClothesEstimation();
void serialPrintDryingClothesEstimation();

//======================[Declarations (prototypes) of private functions]====================//
void updateClothesEstimatorIndicators();
void updateDryingData();

//=================================[#include guards - end]==================================//

#endif // _CLOTHES_DRYING_TIME_CALCULATOR_H_