//========================================[Libraries]=================================//
#include "rain_sensor.h"

//========================[Declaration of Private global variables]===================//
volatile rainSensorState_t rainSensorActivation; 
char* rainStateDescription;  
bool rainSensorUpdateRequired;


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
    attachInterrupt(rainSensorDigitalPin, activateRainSensorUpdateFlag, CHANGE);
}


void disableRainSensor()
{
    detachInterrupt(rainSensorDigitalPin);
}


char* rainSensorReadStateDescription()
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
    }
    rainSensorUpdateRequired = false;    
}


//=========================[Implementation of private functions]======================//
void turnOnTreatment()
{
    msDelay(DEBOUNCE_RAIN_SENSOR_TIME_MS);
    if(digitalRead(rainSensorDigitalPin) == LOW) 
    {
        rainSensorActivation = ON;
    }
}


void turnOffTreatment()
{
    msDelay(DEBOUNCE_RAIN_SENSOR_TIME_MS);
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

        if (analogRainSensorLecture <= 1024 && analogRainSensorLecture > 600)
            rainStateDescription = DRIZZLE_RAIN_DESCRIPTION;

        else if (analogRainSensorLecture <= 600 && analogRainSensorLecture > 400)
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


IRAM_ATTR void activateRainSensorUpdateFlag()
{
    rainSensorUpdateRequired = true;
}