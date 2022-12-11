//================================[#include guards - begin]=================================//
#include "web_user_interface.h"


//===========================[Declaration of Private global variables]=====================//
char htmlGenerated[HTML_GENERATED_MAX_LENGTH];
html_t typeOfHtmlRequired;


//==========================[Implementation of public functions]===========================//
void webUserInterfaceInit()
{
	typeOfHtmlRequired = UNKNOWN;
}


void webUserInterfaceUpdate()
{
	switch (typeOfHtmlRequired)
	{
		case MAIN_MENU:
			generateMainMenuHtml();
			break;
	
		case OUTDOOR_THIN:
			generateOutdoorClothesHtml();
			break;

		case OUTDOOR_THICK:
			generateOutdoorClothesHtml();
			break;

		case INDOOR_THIN:
			generateIndoorClothesHtml();
			break;

		case INDOOR_THICK:
			generateIndoorClothesHtml();
			break;	
			
		case ENV_VARIABLES:
			generateEnviromentalVarsHtml();
			break;

		case UNKNOWN:
			break;
	}
}


void setWebUserInterface(html_t newHtmlRequired)
{
	typeOfHtmlRequired = newHtmlRequired;
}


char* getWebUserInterface()
{
	return htmlGenerated;
}



//==========================[Implementation of private functions]===========================//
void generateMainMenuHtml()
{
	strcpy(htmlGenerated, index_html);
}


void generateOutdoorClothesHtml()
{
	char* dryingEstimation = readDryingClothesEstimation();
	const char* rainState = readRainStateDescription();

	strcpy(htmlGenerated, drying_html);
	strcat(htmlGenerated, dryingEstimation);
	strcat(htmlGenerated, rainState_html);
	strcat(htmlGenerated, rainState);
	strcat(htmlGenerated, footer_html);
}


void generateIndoorClothesHtml()
{
	char* dryingEstimation = readDryingClothesEstimation();

	strcpy(htmlGenerated, drying_html);
	strcat(htmlGenerated, dryingEstimation);
	strcat(htmlGenerated, footer_html);
}


void generateEnviromentalVarsHtml()
{
	const char* rainState = readRainStateDescription();
	char temperature[13];
	char humidity[8];
	sprintf(temperature, "%0.1f &deg;C", dhtSensorReadTemperature());
	sprintf(humidity, "%0.1f %%", dhtSensorReadHumidity());
	
	strcpy(htmlGenerated, environmental_html);			
	strcat(htmlGenerated, temperature_html);
	strcat(htmlGenerated, temperature);
	strcat(htmlGenerated, humidity_html);
	strcat(htmlGenerated, humidity);
	strcat(htmlGenerated, rainState_html);
	strcat(htmlGenerated, rainState);
	strcat(htmlGenerated, footer_html);
}