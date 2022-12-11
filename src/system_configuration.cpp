//========================================[Libraries]=================================//
#include "system_configuration.h"

//========================[Declaration of Private global variables]===================//
configuration_t selectedConfig;
bool systemAlreadyConfigured;


//===========================[Implementation of public functions]=====================//
void systemConfigurationInit()
{
    selectedConfig = INIT_CONFIG;
    systemAlreadyConfigured = false;
}


void systemConfigurationUpdate()
{
    switch (selectedConfig)
	{
		case INIT_CONFIG:
			configureSystemInit();
		break;

		case IDLE_CONFIG:
			configureSystemAsIdle();
			break;
	
		case OUTDOOR_THIN_CONFIG:
			configureSystemForOutdoorThinClothes();
			break;

		case OUTDOOR_THICK_CONFIG:
			configureSystemForOutdoorThickClothes();
			break;

		case INDOOR_THIN_CONFIG:
			configureSystemForIndoorThinClothes();
			break;

		case INDOOR_THICK_CONFIG:
			configureSystemForIndoorThickClothes();
			break;	
			
		case ENV_VARIABLES_CONFIG:
			configureSystemForEnviromentalVars();
			break;

		case ERROR_CONFIG:
			configureSystemForErrorIndication();
			break;

		default:
			break;
	}
}


void setSystemConfiguration(configuration_t newConfiguration)
{
    selectedConfig = newConfiguration;
}


void setSystemConfigurationUsingHttpLine(String httpLine)
{
	selectedConfig = UNKNOWN_CONFIG;

	if(httpLine == "GET / HTTP/1.1")
		selectedConfig = IDLE_CONFIG;

	if(httpLine == "GET /get?Configuration=OUTDOOR_THIN HTTP/1.1")
		selectedConfig = OUTDOOR_THIN_CONFIG;

	if(httpLine == "GET /get?Configuration=OUTDOOR_THICK HTTP/1.1")
		selectedConfig = OUTDOOR_THICK_CONFIG;

	if(httpLine == "GET /get?Configuration=INDOOR_THIN HTTP/1.1")
		selectedConfig = INDOOR_THIN_CONFIG;

	if(httpLine == "GET /get?Configuration=INDOOR_THICK HTTP/1.1")
		selectedConfig = INDOOR_THICK_CONFIG;

	if(httpLine == "GET /get?Configuration=ENV_VARIABLES HTTP/1.1")
		selectedConfig = ENV_VARIABLES_CONFIG;
}


//=========================[Implementation of private functions]======================//
void configureSystemInit()
{
	if(!systemAlreadyConfigured)
	{
		ledIndicatorsChangeState(WAITING_FOR_CONFIGURATION);
		systemAlreadyConfigured = true;
	}
}


void configureSystemAsIdle()
{
	setWebUserInterface(MAIN_MENU);
	if(systemAlreadyConfigured)
	{
		disableClothesDryingEstimator();
		disableRainSensor();
		ledIndicatorsChangeState(WAITING_FOR_CONFIGURATION);
		systemAlreadyConfigured = false;
	}
}


void configureSystemForOutdoorThinClothes()
{
	setWebUserInterface(OUTDOOR_THIN);
	if(!systemAlreadyConfigured)
	{
		enableClothesDryingEstimator(THIN);
		enableRainSensor();	
		ledIndicatorsChangeState(SYSTEM_IN_EXECUTION);
		systemAlreadyConfigured = true;				
	}
}


void configureSystemForOutdoorThickClothes()
{
	setWebUserInterface(OUTDOOR_THICK);
	if(!systemAlreadyConfigured)
	{
		enableClothesDryingEstimator(THICK);
		enableRainSensor();	
		ledIndicatorsChangeState(SYSTEM_IN_EXECUTION);
		systemAlreadyConfigured = true;				
	}
}


void configureSystemForIndoorThinClothes()
{
	setWebUserInterface(INDOOR_THIN);
	if(!systemAlreadyConfigured)
	{
		enableClothesDryingEstimator(THIN);
		ledIndicatorsChangeState(SYSTEM_IN_EXECUTION);
		systemAlreadyConfigured = true;				
	}
}


void configureSystemForIndoorThickClothes()
{
	setWebUserInterface(INDOOR_THICK);
	if(!systemAlreadyConfigured)
	{
		enableClothesDryingEstimator(THICK);
		ledIndicatorsChangeState(SYSTEM_IN_EXECUTION);
		systemAlreadyConfigured = true;				
	}	
}


void configureSystemForEnviromentalVars()
{
	setWebUserInterface(ENV_VARIABLES);
	if(!systemAlreadyConfigured)
	{
		enableRainSensor();
		ledIndicatorsChangeState(SYSTEM_IN_EXECUTION);
		systemAlreadyConfigured = true;				
	}
}


void configureSystemForErrorIndication()
{
	ledIndicatorsChangeState(CONNECTION_ERROR);
}