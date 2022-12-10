//======================================[Libraries]===================================//
#include "clothes_drying_monitoring_system.h"


//===========================[Implementation of public functions]=====================//
void clothesDryingMonitoringSystemInit()
{
  ledIndicatorsInit();
  rainSensorInit();
  dhtSensorInit();
  clothesDryingEstimatorInit();
  wifiComInit();
}


void clothesDryingMonitoringSystemUpdate()
{
  ledIndicatorsUpdate();
  rainSensorUpdate();
  dhtSensorUpdate();
  clothesDryingEstimatorUpdate();
  wifiComUpdate();
  delay(SYSTEM_TIME_INCREMENT_MS);
}