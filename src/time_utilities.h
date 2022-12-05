//================================[#include guards - begin]=================================//
#ifndef _TIME_UTILITIES_H_
#define _TIME_UTILITIES_H_

#include <ESP8266WiFi.h>


//==============================[Declaration of private data types]=========================//


//==============================[Declaration of public data types]==========================//


//========================[Declarations (prototypes) of private functions]==================//


//====[Declarations (prototypes) of public functions]====//
void msDelay(long unsigned int timeToDelay);
char* secondsToHourFormat(int seconds);

#endif // _TIME_UTILITIES_H_