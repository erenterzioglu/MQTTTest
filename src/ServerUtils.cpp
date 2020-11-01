#include "ServerUtils.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>
//#include <iostream>

ESP8266WebServer webServer(80);
std::vector<std::string> messages;

void handle_OnConnect();
void handle_led1on();
void handle_NotFound();
String DashboardPage();

void configWebServer(){
     
  webServer.on("/", handle_OnConnect);
  webServer.on("/led1on", handle_led1on);
  webServer.onNotFound(handle_NotFound);
  
  webServer.begin();
  Serial.println("HTTP server started");
}

void handle_OnConnect() {
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  webServer.send(200, "text/html", DashboardPage()); 
}

void handle_led1on() {
  Serial.println("GPIO7 Status: ON");
  webServer.send(200, "text/html", DashboardPage()); 
}

void handle_NotFound(){
  webServer.send(404, "text/plain", "Not found");
}

String DashboardPage(){
    String dashboardPage ;
    
    dashboardPage = "<!DOCTYPE html>\n";
    dashboardPage += "<html lang=\"en\" dir=\"ltr\">\n";
    dashboardPage += "<head> <meta charset=\"utf-8\"><title>MQTT Dashboard</title></head>\n";
    dashboardPage += "<body>\n";
    dashboardPage += "<h1>MQTT Dashboard <button type=\"button\" name=\"SettingsButton\">Settings</button></h1>\n";
    dashboardPage += "<p>Incoming MQTT Messages:</p>\n";
    dashboardPage += "<textarea name=\"name\" rows=\"8\" cols=\"80\">\n";

    for(std::string &tmpMessage: messages){
        dashboardPage += tmpMessage.c_str();
        dashboardPage += "\n"; 
    }

    dashboardPage += "</textarea>\n";
    dashboardPage += "</body> \n";
    dashboardPage += "</html> \n";
    /*
<!DOCTYPE html>
<html lang="en" dir="ltr">
<head><meta charset="utf-8"><title>MQTT Dashboard</title></head>
<body>
<h1>MQTT Dashboard <button type="button" name="SettingsButton">Settings</button></h1>
<p>Incoming MQTT Messages:</p>
<textarea name="name" rows="8" cols="80">
</textarea>
</body>
</html>
    */
   return dashboardPage;
}

String SettingsPage(){
    String settingsPage;

    settingsPage = "<!DOCTYPE html>\n";
    settingsPage += " \n";


/*
<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>Settings</title>
  </head>
  <body>
    <button type="button" name="Forgot_Broker">Forgot Broker</button>
    <p></p>
    <button type="button" name="Restore">Restore Device</button>
  </body>
</html>
*/
    return settingsPage;
}
