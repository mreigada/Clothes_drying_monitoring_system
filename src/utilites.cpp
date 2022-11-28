//=======================================[Libraries]===================================//
#include "utilities.h"


//=============[Declaration and initialization of public global variables]============//


//=============[Declaration and initialization of private global variables]===========//


//=======================[Implementation of public functions]=========================//
void msDelay(long unsigned int timeToDelay)
{
    long unsigned int initTime = millis();
    while(millis() - initTime < timeToDelay){};
}