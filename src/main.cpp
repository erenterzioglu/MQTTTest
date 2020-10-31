#include <Arduino.h>
#include <WifiManager.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <PubSubClient.h>
#include "SPIFFSUtils.h"
#include "ServerUtils.h"
#include <ESP8266mDNS.h>

bool shouldSaveConfig = false; // May be delete 

char mqtt_server[40] = "broker.emqx.io" ;
char mqtt_port[6] = "1883";
char blynk_token[33] = " ";

WiFiClient espClient;
PubSubClient client(espClient);

ESP8266WebServer webServer; // This externed value may be arbitary 

void reconnect();
void callback(char* topic, byte* payload, unsigned int length);

//callback notifying us of the need to save config
// May be deleted too 
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void setup() {
  Serial.begin(9600);
  WiFiManager wifiManager;

  //configFileRead(mqtt_server, mqtt_port, blynk_token);
  // Uncomment and run it once, if you want to erase all the stored information
  //wifiManager.resetSettings();
  wifiManager.setConfigPortalTimeout(180);
      
  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 5);
  WiFiManagerParameter custom_blynk_token("blynk", "blynk token", blynk_token, 34);

  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_blynk_token);

  if(!wifiManager.autoConnect("ESP-8266", "123456")) {
    Serial.println("failed to connect and hit timeout");
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(1000);
  } 
  
  //if you get here you have connected to the WiFi
  Serial.println("connected...");
 
  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
 
  configWebServer();

  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(blynk_token, custom_blynk_token.getValue());

  configFileWrite(mqtt_server,mqtt_port,blynk_token);
  
  client.setServer(mqtt_server, atoi(mqtt_port));
  client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
   
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.subscribe("testtopic/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) {
    reconnect();
  }
  
  client.loop();
  webServer.handleClient();
  delay(5000);
}