//======================================[Libraries]===================================//
#include "clothes_drying_estimator.h"


//========================[Declaration of Private global variables]===================//
bool clothesEstimatorUpdateRequired;
clothingThickness_t chosenClothingThickness;
float savedTemperature;
float savedHumidity;
float initialEstimatedDryingTime;
float estimatedDryingTime;


//===========================[Implementation of public functions]=====================//
void clothesDryingEstimatorInit()
{
  clothesEstimatorUpdateRequired = false;
}


void enableClothesDryingEstimator(clothingThickness_t clothingThickness)
{
  //Initialization of the estimated drying time
  savedTemperature = dhtSensorReadTemperature();
  savedHumidity = dhtSensorReadHumidity();
  chosenClothingThickness = clothingThickness;
  initialEstimatedDryingTime = calculateSecondsToDryClothes(savedTemperature, savedHumidity, chosenClothingThickness);
  estimatedDryingTime = initialEstimatedDryingTime;

  //Timer 1 setup
  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP);
  timer1_write(TIMER1_25_SECONDS_TICKS_EQUIVALENCE);
  timer1_attachInterrupt(changeClothesEstimatorUpdateFlag);
}


void disableClothesDryingEstimator()
{
  timer1_detachInterrupt();
}


void clothesDryingEstimatorUpdate()
{
  if(clothesEstimatorUpdateRequired)
  {
    updateDryingData();
    clothesEstimatorUpdateRequired = false;
  }

  if(estimatedDryingTime < 0)
    disableClothesDryingEstimator();
}


//===========================[Implementation of private functions]=====================//
IRAM_ATTR void changeClothesEstimatorUpdateFlag()
{
  clothesEstimatorUpdateRequired = true;
  estimatedDryingTime = estimatedDryingTime - SECONDS_BETWEEN_UPDATE;
}


void updateDryingData()
{
  float currentTemperature = dhtSensorReadTemperature();
  float currentHumidity = dhtSensorReadHumidity();
  float auxTime = calculateSecondsToDryClothes(currentTemperature, currentHumidity, chosenClothingThickness);

  if(isnan(currentTemperature) != true && (savedTemperature != currentTemperature || savedHumidity != currentHumidity))
  {
     savedTemperature = currentTemperature;
     savedHumidity = currentHumidity;
     estimatedDryingTime = auxTime - (initialEstimatedDryingTime - estimatedDryingTime);
  }
}


float calculateSecondsToDryClothes(float temperature, float humidity, clothingThickness_t thickness)
{
  float secondsToDry = 0;

  switch (thickness)
  {
    case THIN: 
          secondsToDry = (humidity/temperature)*3600;
          break;
    
    case THICK:
          secondsToDry = 4 * (humidity/temperature)*3600;
          break;
  }

  return secondsToDry;
}


void serialPrintDryingClothesEstimation()
{
  if(estimatedDryingTime > 0)
  {
    int minutes = (int) estimatedDryingTime/60;
    int hours = minutes/60;
    minutes = minutes%60;

    Serial.println(" "); 
    Serial.print("Temperature: ");
    Serial.print(savedTemperature);
    Serial.println("ºC");
    Serial.print("Humidity: ");
    Serial.print(savedHumidity);
    Serial.println("%");
    Serial.print("Estimated time to complete drying clothes: ");
    Serial.print(hours);
    Serial.print("hs. ");
    Serial.print(minutes);
    Serial.println(" min.");
    Serial.println(" ");
  }

  else
    Serial.println("The estimated laundry drying time has already elapsed.");
}


char* readDryingClothesEstimation()
{
  char* strEstimation = " ";

  if(estimatedDryingTime > 0)
  {
    int minutes = (int) estimatedDryingTime/60;
    int hours = minutes/60;
    minutes = minutes%60;
    sprintf(strEstimation, "%d hs. %d min.", hours, minutes);
  }

  else
    strEstimation = "The estimated laundry drying time has already elapsed.";

  return strEstimation;
}