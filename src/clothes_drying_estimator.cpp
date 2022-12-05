//======================================[Libraries]===================================//
#include "clothes_drying_estimator.h"


//========================[Declaration of Private global variables]===================//
clothingThickness_t selectedClothinThickness;
bool clothesEstimatorUpdateRequired;
float savedTemperature;
float savedHumidity;
float initialEstimatedDryingTime;
float estimatedDryingTime;


//===========================[Implementation of public functions]=====================//
void clothesDryingEstimatorInit()
{
  clothesEstimatorUpdateRequired = false;
  savedTemperature = 0;
  savedHumidity = 0;
  initialEstimatedDryingTime = 0;
  estimatedDryingTime = 0;
}


void enableClothesDryingEstimator(clothingThickness_t clothingThickness)
{
  savedTemperature = dhtSensorReadTemperature();
  savedHumidity = dhtSensorReadHumidity();
  selectedClothinThickness = clothingThickness;
  initialEstimatedDryingTime = calculateSecondsToDryClothes(savedTemperature, savedHumidity, selectedClothinThickness);
  estimatedDryingTime = initialEstimatedDryingTime;

  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP);
  timer1_write(TIMER1_25_SECONDS_TICKS_EQUIVALENCE);
  timer1_attachInterrupt(updateClothesEstimatorIndicators);
}


void disableClothesDryingEstimator()
{
  timer1_detachInterrupt();
  timer1_disable();
}


void clothesDryingEstimatorUpdate()
{
  if(clothesEstimatorUpdateRequired)
  {
    updateDryingData();
    clothesEstimatorUpdateRequired = false;

    if(estimatedDryingTime < 0)
      disableClothesDryingEstimator();
  }
}


float calculateSecondsToDryClothes(float temperature, float humidity, clothingThickness_t thickness)
{
  float secondsToDry = 0;

  switch (thickness)
  {
    case THIN: 
          secondsToDry = 1.5 * (humidity/temperature)*3600;
          break;
    
    case THICK:
          secondsToDry = 5 * (humidity/temperature)*3600;
          break;
  }

  return secondsToDry;
}


char* readDryingClothesEstimation()
{
  char* strEstimation;

  if(estimatedDryingTime > 60)
  {
    strEstimation = secondsToHourFormat(estimatedDryingTime);
  }

  else
    strEstimation = DRYING_TIME_ELAPSED_MSG;

  return strEstimation;
}


void serialPrintDryingClothesEstimation()
{
  Serial.println(readDryingClothesEstimation());
}


//===========================[Implementation of private functions]=====================//
IRAM_ATTR void updateClothesEstimatorIndicators()
{
  clothesEstimatorUpdateRequired = true;
  estimatedDryingTime = estimatedDryingTime - SECONDS_BETWEEN_UPDATE;
}


void updateDryingData()
{
  float currentTemperature = dhtSensorReadTemperature();
  float currentHumidity = dhtSensorReadHumidity();
  float auxTime = calculateSecondsToDryClothes(currentTemperature, currentHumidity, selectedClothinThickness);

  if(!isnan(currentTemperature) && (savedTemperature != currentTemperature || savedHumidity != currentHumidity))
  {
     savedTemperature = currentTemperature;
     savedHumidity = currentHumidity;
     estimatedDryingTime = auxTime - (initialEstimatedDryingTime - estimatedDryingTime);
  }
}