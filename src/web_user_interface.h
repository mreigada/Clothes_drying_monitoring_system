//================================[#include guards - begin]=================================//
#ifndef _WEB_USER_INTERFACE_H_
#define _WEB_USER_INTERFACE_H_

#include <ESP8266WiFi.h>
#include "clothes_drying_estimator.h"
#include "rain_sensor.h"
#include "dht_sensor.h"


//==============================[Declaration of private data types]=========================//
typedef enum
{
	MAIN_MENU,
    OUTDOOR_THIN,
    OUTDOOR_THICK,
	INDOOR_THIN,
	INDOOR_THICK,
	ENV_VARIABLES,
	UNKNOWN
} html_t;


const char index_html[] = R"rawliteral(	
<!DOCTYPE html><html><head>
<title>Clothes drying monitoring system</title>
<style>
.titl
{
text-align: center;
}
.configBox
{
margin: 35px;
border: solid black 1px;
border-radius: 8px;
padding: 16px;
background-color: #f2f2f2;
}
body
{
display: flex;
align-items: center;
justify-content: center;
margin: 0 auto;
height: 80vh;
background-color: #f1f1f1;
}
select
{
margin-bottom: 10px;
margin-top: 10px;
border-radius: 2px;
}
h1
{
color: green;
}
</style>
</head>
<body>
<center>
<h1>Clothes drying monitoring system</h1>
<div class=configBox>
<form action=/get>
    <label for="lang">Configuration</label>
    <select name="Configuration" id="config">
	<optgroup label="Outdoor clothes drying">
	<option value="OUTDOOR_THIN">Thin clothes</option>
	<option value="OUTDOOR_THICK">Thick clothes</option>
</optgroup>
<optgroup label="Indoor clothes drying">
<option value="INDOOR_THIN">Thin clothes</option>
<option value="INDOOR_THICK">Thick clothes</option>
</optgroup>
<option value="ENV_VARIABLES">Measure environmental variables</option>
</optgroup>
</select>
</br>
</br>
<input type=submit value="Start monitoring">
</form>
</div>
</body>
</html>
)rawliteral";


const char drying_html[] = R"rawliteral(
<!DOCTYPE html><html><head>
<title>Clothes drying monitoring system</title>
<meta http-equiv="refresh" content="10">
<style>
.configBox
{
margin: 12px;
border: solid black 1px;
border-radius: 8px;
padding: 6px;
background-color: #f2f2f2;
}
body
{
display: flex;
align-items: center;
justify-content: center;
margin: 0 auto;
height: 80vh;
background-color: #f1f1f1;
}
</style>
</head>
<body>
<center>
</br>
<div class=configBox>
<h2>Estimated clothes drying time: 
)rawliteral";


const char rainState_html[] = R"rawliteral(
<h2>Rain state: )rawliteral";


const char environmental_html[] = R"rawliteral(
<!DOCTYPE html><html><head>
<title>Clothes drying monitoring system</title>
<meta http-equiv="refresh" content="5">
<style>
.configBox
{
margin: 12px;
border: solid black 1px;
border-radius: 8px;
padding: 6px;
background-color: #f2f2f2;
}
body
{
display: flex;
align-items: center;
justify-content: center;
margin: 0 auto;
height: 80vh;
background-color: #f1f1f1;
}
</style>
</head>
<body>
<center>
</br>
<div class=configBox>)rawliteral";

const char temperature_html[] = R"rawliteral(
<h2>Temperature: )rawliteral";

const char humidity_html[] = R"rawliteral(
<h2>Humidity: )rawliteral";

const char footer_html[] =  R"rawliteral(
</div>
</br>
<div style='text-align:center;'>
<button onClick=location.href='./'>Back to main menu</button>
</div>
)rawliteral";


//=======================[Declarations (prototypes) of public functions]====================//
void webUserInterfaceInit();
char* getWebUserInterface(String httpRequestLine);


//=======================[Declarations (prototypes) of private functions]====================//
html_t getRequiredHtmlType(String httpRequestLine);
void deleteWebUserInterface();
void generateMainMenuHtml();
void generateOutdoorClothesHtml();
void generateIndoorClothesHtml();
void generateEnviromentalVarsHtml();
void configureSystemForMainMenu();
void configureSystemForOutdoorThinClothes();
void configureSystemForOutdoorThickClothes();
void configureSystemForIndoorThinClothes();
void configureSystemForIndoorThickClothes();
void configureSystemForEnviromentalVars();

//=================================[#include guards - end]==================================//


#endif // _WEB_USER_INTERFACE_H_