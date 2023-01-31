//======================================[Libraries]===================================//
#include "clothes_drying_time_calculator.h"


//========================[Declaration of Private global variables]===================//
clothingThickness_t selectedClothinThickness;
runningState_t runningState;
bool clothesEstimatorUpdateRequired;
float savedTemperature;
float savedHumidity;
float initialEstimatedDryingTime;
float estimatedDryingTime;


//===========================[Implementation of public functions]=====================//
void clothesDryingEstimatorInit()
{
  clothesEstimatorUpdateRequired = false;
  runningState = STOPPED;
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
  enableUpdateTimer();
  runningState = RUNNING;
}


void disableClothesDryingEstimator()
{
  disableUpdateTimer();
}


void clothesDryingEstimatorUpdate()
{
  if(clothesEstimatorUpdateRequired)
  {
    updateDryingData();
    clothesEstimatorUpdateRequired = false;

    if(estimatedDryingTime < 0)
    {
      disableClothesDryingEstimator();
      runningState = STOPPED;
    }
  }
}


float calculateSecondsToDryClothes(float temperature, float humidity, clothingThickness_t thickness)
{
  float secondsToDry = 0;

  switch (thickness)
  {
    case THIN: 
          secondsToDry = 1.5 * (humidity/temperature) * 180 + 7200;
          break;
    
    case THICK:
          secondsToDry = 5 * (humidity/temperature) * 180 + 10800;
          break;
  }

  return secondsToDry;
}


runningState_t readClothesDryingEstimationState()
{
  return runningState;
}


char* readDryingClothesEstimation()
{
  char* strEstimation;

  if(estimatedDryingTime > 0)
  {
    strEstimation = secondsToHourFormat(estimatedDryingTime);
  }

  else
    strEstimation = (char*) dryingTimeElapsedMsg;

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


void enableUpdateTimer()
{
  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP);
  timer1_write(TIMER1_25_SECONDS_TICKS_EQUIVALENCE);
  timer1_attachInterrupt(updateClothesEstimatorIndicators);
}


void disableUpdateTimer()
{
  timer1_detachInterrupt();
  timer1_disable();
}