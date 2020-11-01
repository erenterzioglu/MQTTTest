#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include<Arduino.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include "SPIFFSUtils.h"

void configFileRead(char* mqtt_server, char* mqtt_port, char*topic_name){    
 
  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");

          strcpy(mqtt_server, json["mqtt_server"]);
          strcpy(mqtt_port, json["mqtt_port"]);
          strcpy(topic_name, json["topic_name"]);

        /*
          if(json["ip"]) {
            Serial.println("setting custom ip from config");
            static_ip = json["ip"];
            strcpy(static_ip, json["ip"]);
            strcpy(static_gw, json["gateway"]);
            strcpy(static_sn, json["subnet"]);
            strcat(static_ip, json["ip"]);
            static_gw = json["gateway"];
            static_sn = json["subnet"];
            Serial.println(static_ip);
            Serial.println("converting ip");
            IPAddress ip = ipFromCharArray(static_ip);
            Serial.println(ip);
          } else {
            Serial.println("no custom ip in config");
          }*/

        } else {
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
  }
}

void configFileWrite(char* mqtt_server, char* mqtt_port, char*topic_name ){
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["mqtt_server"] = mqtt_server;
    json["mqtt_port"] = mqtt_port;
    json["topic_name"] = topic_name;

    //json["ip"] = WiFi.localIP().toString();
    //json["gateway"] = WiFi.gatewayIP().toString();
    //json["subnet"] = WiFi.subnetMask().toString();
    
    // SPIFFS control might be need 
    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.prettyPrintTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  

}