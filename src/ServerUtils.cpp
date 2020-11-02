#include "ServerUtils.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>

#define MESSAGE_BUFFER_SIZE 20

std::string messages[MESSAGE_BUFFER_SIZE];
int head=0;
int tail=0;

ESP8266WebServer webServer(80);

void handle_OnConnect();
void handle_led1on();
void handle_NotFound();
String DashboardPage();
String SettingsPage();
void settings();

void configWebServer(){
     
  webServer.on("/", handle_OnConnect);
  webServer.on("/settings", settings);
  webServer.onNotFound(handle_NotFound);
  
  webServer.begin();
  Serial.println("HTTP server started");
}

void handle_OnConnect() {
  Serial.println("Connection..");
  webServer.send(200, "text/html", DashboardPage()); 
}

void settings() {
  Serial.println("Settings");
  webServer.send(200, "text/html", SettingsPage()); 
}

void handle_NotFound(){
  webServer.send(404, "text/plain", "Not found");
}

String DashboardPage(){
    String dashboardPage ;
    
    dashboardPage = "<!DOCTYPE html>\n";
    dashboardPage += "<html lang=\"en\" dir=\"ltr\">\n";
    dashboardPage += "<head> <meta http-equiv=\"refresh\" content=\"50\" charset=\"utf-8\"><title>MQTT Dashboard</title></head>\n";
    dashboardPage += "<body>\n";
    dashboardPage += "<h1>MQTT Dashboard <a href=\"/settings\"><button type=\"button\" name=\"SettingsButton\">Settings</button></a></h1>\n";
    dashboardPage += "<p>Incoming MQTT Messages:</p>\n";
    dashboardPage += "<textarea name=\"name\" rows=\"8\" cols=\"80\">\n";

    for(int i=0; i< 20; i++){
        dashboardPage += messages[i].c_str();
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
    settingsPage += "<head><meta charset=\"utf-8\"><title>Settings</title></head> \n";
    settingsPage += "<body><button type=\"button\" name=\"Forgot_Broker\">Forgot Broker</button><p></p> \n";
    settingsPage += "<button type=\"button\" name=\"Restore\">Restore Device</button></body> \n";
    settingsPage += " </body></html> \n";
    settingsPage += " \n";
    settingsPage += " \n";
    settingsPage += " \n";
    settingsPage += " \n";
    settingsPage += " \n";
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
