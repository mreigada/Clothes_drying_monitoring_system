//========================================[Libraries]=================================//
#include "led_indicators.h"

//========================[Declaration of Private global variables]===================//
ledIndicatorsState_t ledIndicatorState;


//===========================[Implementation of public functions]=====================//
void ledIndicatorsInit()
{
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, LOW);

  pinMode(YELLOW_LED_PIN, OUTPUT);
  digitalWrite(YELLOW_LED_PIN, LOW);

  pinMode(GREEN_LED_PIN, OUTPUT);
  digitalWrite(GREEN_LED_PIN, LOW);

  ledIndicatorState = MODULE_INITIALIZED;
}


void ledIndicatorsUpdate()
{
    switch (ledIndicatorState)
    {
        case MODULE_INITIALIZED:
            break;

        case CONNECTION_ERROR:
            connectionErrorTreatment();
            break;

        case WAITING_FOR_CONFIGURATION:
            waitingConfigurationTreatment();
            break;

        case SYSTEM_IN_EXECUTION:
            systemExeTreatment();
            break;
    }
}


void ledIndicatorsChangeState(ledIndicatorsState_t newState)
{
    ledIndicatorState = newState;
}


//=========================[Implementation of private functions]======================//
void connectionErrorTreatment()
{
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
}


void waitingConfigurationTreatment()
{
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
}


void systemExeTreatment()
{
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
}