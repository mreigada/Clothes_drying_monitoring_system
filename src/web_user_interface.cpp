//================================[#include guards - begin]=================================//
#include "web_user_interface.h"


//===========================[Declaration of Private global variables]=====================//
bool systemAlreadyConfigured;
char* htmlGenerated;


//==========================[Implementation of public functions]===========================//
void webUserInterfaceInit()
{
	bool systemAlreadyConfigured = false;
	char* htmlGenerated = NULL;
}


char* getWebUserInterface(String httpRequestLine)
{

	html_t htmlRequired = getRequiredHtmlType(httpRequestLine);

	switch (htmlRequired)
	{
		case MAIN_MENU:
			configureSystemForMainMenu();
			generateMainMenuHtml();
			break;
	
		case OUTDOOR_THIN:
			configureSystemForOutdoorThinClothes();
			generateOutdoorClothesHtml();
			break;

		case OUTDOOR_THICK:
			configureSystemForOutdoorThickClothes();
			generateOutdoorClothesHtml();
			break;

		case INDOOR_THIN:
			configureSystemForIndoorThinClothes();
			generateIndoorClothesHtml();
			break;

		case INDOOR_THICK:
			configureSystemForIndoorThickClothes();
			generateIndoorClothesHtml();
			break;	
			
		case ENV_VARIABLES:
			configureSystemForEnviromentalVars();
			generateEnviromentalVarsHtml();
			break;

		default:
			break;
	}

	return htmlGenerated;
}



//==========================[Implementation of private functions]===========================//
void deleteWebUserInterface()
{
	if(htmlGenerated)
		free(htmlGenerated);
}


html_t getRequiredHtmlType(String httpRequestLine)
{
	html_t requiredHtmlType = UNKNOWN; 

	if(httpRequestLine == "GET / HTTP/1.1")
		requiredHtmlType = MAIN_MENU;

	if(httpRequestLine == "GET /get?Configuration=OUTDOOR_THIN HTTP/1.1")
		requiredHtmlType = OUTDOOR_THIN;

	if(httpRequestLine == "GET /get?Configuration=OUTDOOR_THICK HTTP/1.1")
		requiredHtmlType = OUTDOOR_THICK;

	if(httpRequestLine == "GET /get?Configuration=INDOOR_THIN HTTP/1.1")
		requiredHtmlType = INDOOR_THIN;

	if(httpRequestLine == "GET /get?Configuration=INDOOR_THICK HTTP/1.1")
		requiredHtmlType = INDOOR_THICK;

	if(httpRequestLine == "GET /get?Configuration=ENV_VARIABLES HTTP/1.1")
		requiredHtmlType = ENV_VARIABLES;

	return requiredHtmlType;
}


void configureSystemForMainMenu()
{
	if(systemAlreadyConfigured)
	{
		disableClothesDryingEstimator();
		disableRainSensor();
		deleteWebUserInterface();
		systemAlreadyConfigured = false;
	}
}


void configureSystemForOutdoorThinClothes()
{
	if(!systemAlreadyConfigured)
	{
		enableClothesDryingEstimator(THIN);
		enableRainSensor();	
		systemAlreadyConfigured = true;				
	}
}


void configureSystemForOutdoorThickClothes()
{
	if(!systemAlreadyConfigured)
	{
		enableClothesDryingEstimator(THICK);
		enableRainSensor();	
		systemAlreadyConfigured = true;				
	}
}


void configureSystemForIndoorThinClothes()
{
	if(!systemAlreadyConfigured)
	{
		enableClothesDryingEstimator(THIN);
		systemAlreadyConfigured = true;				
	}
}


void configureSystemForIndoorThickClothes()
{
	if(!systemAlreadyConfigured)
	{
		enableClothesDryingEstimator(THICK);
		systemAlreadyConfigured = true;				
	}	
}


void configureSystemForEnviromentalVars()
{
	if(!systemAlreadyConfigured)
	{
		enableRainSensor();
		systemAlreadyConfigured = true;				
	}
}


void generateMainMenuHtml()
{
	htmlGenerated = (char*) malloc(strlen(index_html) + 1);
	strcpy(htmlGenerated, index_html);
}


void generateOutdoorClothesHtml()
{
	char* dryingEstimation = readDryingClothesEstimation();
	char* rainState = readRainSensorStateDescription();

	htmlGenerated = (char*) malloc(strlen(drying_html) + strlen(dryingEstimation) + strlen(rainState_html) + strlen(rainState) + strlen(footer_html) + 1);
	strcpy(htmlGenerated, drying_html);
	strcat(htmlGenerated, dryingEstimation);
	strcat(htmlGenerated, rainState_html);
	strcat(htmlGenerated, rainState);
	strcat(htmlGenerated, footer_html);
}


void generateIndoorClothesHtml()
{
	char* dryingEstimation = readDryingClothesEstimation();

	htmlGenerated = (char*) malloc(strlen(drying_html) + strlen(dryingEstimation) + strlen(footer_html) + 1);
	strcpy(htmlGenerated, drying_html);
	strcat(htmlGenerated, dryingEstimation);
	strcat(htmlGenerated, footer_html);
}


void generateEnviromentalVarsHtml()
{
	char* rainState = readRainSensorStateDescription();
	char temperature[13];
	char humidity[8];
	sprintf(temperature, "%0.1f &deg;C", dhtSensorReadTemperature());
	sprintf(humidity, "%0.1f %%", dhtSensorReadHumidity());

	htmlGenerated = (char*) malloc(strlen(environmental_html) + strlen(rainState_html) + strlen(rainState) + strlen(temperature_html) + strlen(humidity_html) + strlen(temperature) + strlen(humidity) + strlen(footer_html) + 1);
	
	strcpy(htmlGenerated, environmental_html);			
	strcat(htmlGenerated, temperature_html);
	strcat(htmlGenerated, temperature);
	strcat(htmlGenerated, humidity_html);
	strcat(htmlGenerated, humidity);
	strcat(htmlGenerated, rainState_html);
	strcat(htmlGenerated, rainState);
	strcat(htmlGenerated, footer_html);
}