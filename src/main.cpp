#include <Arduino.h>
#include<WifiManager.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>

void setup() {
    WiFiManager wifiManager;
    // Uncomment and run it once, if you want to erase all the stored information
    //wifiManager.resetSettings();
    //wifiManager.setConfigPortalTimeout(180);
    
    if(!wifiManager.autoConnect("ESP-8266", "123456")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  } 

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");
}

void loop() {
  // put your main code here, to run repeatedly:
}