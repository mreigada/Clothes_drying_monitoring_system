//================================[#include guards - begin]=================================//
#ifndef _CLOTHES_DRYING_ESTIMATOR_H_
#define _CLOTHES_DRYING_ESTIMATOR_H_

#include <ESP8266WiFi.h>
#include "dht_sensor.h"
#include "math.h"


//==============================[Declaration of public defines]=============================//
#define dhtSensorPin D1
#define TIMER1_25_SECONDS_TICKS_EQUIVALENCE 7812500
#define SECONDS_BETWEEN_UPDATE 25

//==============================[Declaration of public data types]==========================//
typedef enum
{
    THIN,
    THICK
} clothingThickness_t;


//=======================[Declarations (prototypes) of public functions]====================//
void clothesDryingEstimatorInit();
void clothesDryingEstimatorUpdate();
void enableClothesDryingEstimator(clothingThickness_t clothingThickness);
void disableClothesDryingEstimator();
char* readDryingClothesEstimation();

//======================[Declarations (prototypes) of private functions]====================//
void changeClothesEstimatorUpdateFlag();
void updateDryingData();
float calculateSecondsToDryClothes(float temperature, float humidity, clothingThickness_t thickness);
void serialPrintDryingClothesEstimation();

//=================================[#include guards - end]==================================//

#endif // _CLOTHES_DRYING_ESTIMATOR_H_