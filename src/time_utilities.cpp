//=======================================[Libraries]===================================//
#include "time_utilities.h"


//=============[Declaration and initialization of public global variables]============//


//=============[Declaration and initialization of private global variables]===========//


//=======================[Implementation of public functions]=========================//
char* secondsToHourFormat(int seconds)
{
    char* strTime = "                         ";
    int minutes = seconds/60;
    int hours = minutes/60;
    minutes = minutes%60;

    if(hours > 1)
        sprintf(strTime, "%d hs. %d min.", hours, minutes);

    if(hours == 1)
        sprintf(strTime, "%d h. %d min.", hours, minutes);

    if(hours == 0)
        sprintf(strTime, "%d min.", minutes);

    return strTime;
}


void msDelay(long unsigned int timeToDelay)
{
    long unsigned int initTime = millis();
    while(millis() - initTime < timeToDelay){};
}