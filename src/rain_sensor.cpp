//========================================[Libraries]=================================//
#include "rain_sensor.h"

//========================[Declaration of Private global variables]===================//
rainSensorActivation_t rainSensorActivation;
rainState_t rainState;
bool rainSensorUpdateRequired;
const char* rainStateDescription;  


//===========================[Implementation of public functions]=====================//
void rainSensorInit()
{
    pinMode(RAIN_SENSOR_DIGITAL_PIN, INPUT);
    rainSensorActivation = OFF;
    rainSensorUpdateRequired = false;
    rainState = NO_RAIN;
    rainStateDescription = noRainDescription;
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
        updateRainState();        
        rainSensorUpdateRequired = false;       
    }
}


void enableRainSensor()
{
    attachInterrupt(RAIN_SENSOR_DIGITAL_PIN, activateRainSensorUpdateIndicator, CHANGE);
}


void disableRainSensor()
{
    detachInterrupt(RAIN_SENSOR_DIGITAL_PIN);
}


rainState_t readRainState()
{
    return rainState;
}


const char* readRainStateDescription()
{
    return rainStateDescription;
}


//=========================[Implementation of private functions]======================//
void turnOnTreatment()
{
    delay(DEBOUNCE_RAIN_SENSOR_TIME_MS);
    if(digitalRead(RAIN_SENSOR_DIGITAL_PIN) == LOW) 
    {
        rainSensorActivation = ON;
    }
}


void turnOffTreatment()
{
    delay(DEBOUNCE_RAIN_SENSOR_TIME_MS);
    if(digitalRead(RAIN_SENSOR_DIGITAL_PIN) == HIGH)
    {
        rainSensorActivation = OFF;
    }
}


void updateRainState()
{
    if(rainSensorActivation == ON)
    {
        int analogRainSensorLecture = getAnalogRainSensorLecture();

        if (analogRainSensorLecture <= DRIZZLE_UPPER_LIMIT && analogRainSensorLecture > DRIZZLE_LOWER_LIMIT)
        {
            rainState = DRIZZLE_RAIN;
            rainStateDescription = drizzleRainDescription;
        }

        else if (analogRainSensorLecture <= DRIZZLE_LOWER_LIMIT && analogRainSensorLecture > REGULAR_RAIN_LOWER_LIMIT)
        {
            rainState = REGULAR_RAIN;
            rainStateDescription = regularRainDescription;
        }

        else
        {
            rainState = HEAVY_RAIN;
            rainStateDescription = heavyRainDescription;
        }
    }

    else
    {
        rainState = NO_RAIN;
        rainStateDescription = noRainDescription;
    }
}


int getAnalogRainSensorLecture()
{
    int analogRainSensorLecture = 0;

    for(int i = 0; i < 1024; i++)
        analogRainSensorLecture = analogRainSensorLecture + analogRead(RAIN_SENSOR_ANALOG_PIN);
    
    analogRainSensorLecture = analogRainSensorLecture/1024;

    return analogRainSensorLecture;
}


IRAM_ATTR void activateRainSensorUpdateIndicator()
{
    rainSensorUpdateRequired = true;
}