//================================[#include guards - begin]=================================//
#ifndef _LED_INDICATORS_H_
#define _LED_INDICATORS_H_

#include <ESP8266WiFi.h>


//===============================[Declaration of private defines]===========================//
#define RED_LED_PIN D6
#define YELLOW_LED_PIN D7
#define GREEN_LED_PIN  D8

//==============================[Declaration of private data types]=========================//
typedef enum
{
    MODULE_INITIALIZED,
    CONNECTION_ERROR,
    WAITING_FOR_CONFIGURATION,
    SYSTEM_IN_EXECUTION,
} ledIndicatorsState_t;


//=====================[Declarations (prototypes) of public functions]======================//
void ledIndicatorsInit();
void ledIndicatorsUpdate();
void ledIndicatorsChangeState(ledIndicatorsState_t newState);

//=====================[Declarations (prototypes) of private functions]=====================//
void initTreatment();   
void connectionErrorTreatment();
void waitingConfigurationTreatment();
void systemExeTreatment();


//=================================[#include guards - end]==================================//

#endif // _LED_INDICATORS_H_