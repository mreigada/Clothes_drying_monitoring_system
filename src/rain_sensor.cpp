//========================================[Libraries]=================================//
#include "rain_sensor.h"

//========================[Declaration of Private global variables]===================//
rainSensorActivation_t rainSensorActivation;
bool rainSensorUpdateRequired;
char* rainStateDescription;  


//===========================[Implementation of public functions]=====================//
void rainSensorInit()
{
    pinMode(rainSensorDigitalPin, INPUT);
    rainSensorActivation = OFF;
    rainSensorUpdateRequired = false;
    rainStateDescription = NO_RAIN_DESCRIPTION;
}


void enableRainSensor()
{
    attachInterrupt(rainSensorDigitalPin, activateRainSensorUpdateIndicator, CHANGE);
}


void disableRainSensor()
{
    detachInterrupt(rainSensorDigitalPin);
}


char* readRainSensorStateDescription()
{
    updateStateDescription();        
    return rainStateDescription;
}


void rainSensorUpdate()
{
    if(rainSensorUpdateRequired)
    { 
        switch (rainSensorActivation)
        {
            case OFF:
                turnOnTreatment();
                break;
    
            case ON:
                turnOffTreatment();
                break;
        }
        rainSensorUpdateRequired = false;       
    }
}


//=========================[Implementation of private functions]======================//
void turnOnTreatment()
{
    delay(DEBOUNCE_RAIN_SENSOR_TIME_MS);
    if(digitalRead(rainSensorDigitalPin) == LOW) 
    {
        rainSensorActivation = ON;
    }
}


void turnOffTreatment()
{
    delay(DEBOUNCE_RAIN_SENSOR_TIME_MS);
    if(digitalRead(rainSensorDigitalPin) == HIGH)
    {
        rainSensorActivation = OFF;
    }
}


void updateStateDescription()
{
    if(rainSensorActivation == ON)
    {
        int analogRainSensorLecture = getAnalogRainSensorLecture();

        if (analogRainSensorLecture <= DRIZZLE_UPPER_LIMIT && analogRainSensorLecture > DRIZZLE_LOWER_LIMIT)
            rainStateDescription = DRIZZLE_RAIN_DESCRIPTION;

        else if (analogRainSensorLecture <= DRIZZLE_LOWER_LIMIT && analogRainSensorLecture > REGULAR_RAIN_LOWER_LIMIT)
            rainStateDescription = REGULAR_RAIN_DESCRIPTION;

        else
            rainStateDescription = HEAVY_RAIN_DESCRIPTION;
    }

    else
        rainStateDescription = NO_RAIN_DESCRIPTION;
}


int getAnalogRainSensorLecture()
{
    int analogRainSensorLecture = 0;

    for(int i = 0; i < 1024; i++)
        analogRainSensorLecture = analogRainSensorLecture + analogRead(rainSensorAnalogPin);
    
    analogRainSensorLecture = analogRainSensorLecture/1024;

    return analogRainSensorLecture;
}


IRAM_ATTR void activateRainSensorUpdateIndicator()
{
    rainSensorUpdateRequired = true;
}