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
  systemConfigurationInit();
  webUserInterfaceInit();
}


void clothesDryingMonitoringSystemUpdate()
{
  ledIndicatorsUpdate();
  rainSensorUpdate();
  dhtSensorUpdate();
  clothesDryingEstimatorUpdate();
  wifiComUpdate();
  systemConfigurationUpdate();
  webUserInterfaceUpdate();
  delay(SYSTEM_TIME_DELAY_MS);
}