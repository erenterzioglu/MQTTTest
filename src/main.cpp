#include <Arduino.h>
#include <WifiManager.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <PubSubClient.h>
#include "SPIFFSUtils.h"
#include "ServerUtils.h"
#include <ESP8266mDNS.h>


/*
char mqtt_server[40] = "broker.emqx.io" ;
char mqtt_port[6] = "1883";
char topic_name[33] = "testtopic/#";
*/

char mqtt_server[40] = "" ;
char mqtt_port[6] = "";
char topic_name[33] = "";

#define BUILTIN_LED 2

WiFiClient espClient;
PubSubClient client(espClient);
WiFiManager wifiManager;

//ESP8266WebServer webServer; // This externed value may be arbitary 

void reconnect();
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  
  Serial.begin(9600);
  pinMode(BUILTIN_LED,OUTPUT);
  digitalWrite(BUILTIN_LED,HIGH);

  configFileRead(mqtt_server, mqtt_port, topic_name);
  // Uncomment and run it once, if you want to erase all the stored information
  //wifiManager.resetSettings();
  wifiManager.setConfigPortalTimeout(180);
      
  //set config save notify callback
  //wifiManager.setSaveConfigCallback(saveConfigCallback);

  WiFiManagerParameter custom_mqtt_server("server", "mqtt server", mqtt_server, 40);
  WiFiManagerParameter custom_mqtt_port("port", "mqtt port", mqtt_port, 5);
  WiFiManagerParameter custom_topic_name("topic", "topic name", topic_name, 34);

  wifiManager.addParameter(&custom_mqtt_server);
  wifiManager.addParameter(&custom_mqtt_port);
  wifiManager.addParameter(&custom_topic_name);

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
  
  MDNS.addService("http", "tcp", 80);

  strcpy(mqtt_server, custom_mqtt_server.getValue());
  strcpy(mqtt_port, custom_mqtt_port.getValue());
  strcpy(topic_name, custom_topic_name.getValue());

  configFileWrite(mqtt_server,mqtt_port,topic_name);
  
  client.setServer(mqtt_server, atoi(mqtt_port));
  client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  //digitalWrite(BUILTIN_LED,LOW);
  std::string str;
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    str[i] = (char)payload[i];
  }
  Serial.println();
  //messages[tail] = str;
  tail++;
  //digitalWrite(BUILTIN_LED,HIGH);
  delay(10);
}

void reconnect() {
  unsigned long localTimeout = millis();
  // Loop until we're reconnected
  while ((!client.connected()) && (millis()-localTimeout < 5000)) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
   
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      //client.subscribe("testtopic/#");
      client.subscribe(topic_name);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(10);
    }
  }
}

unsigned long cmpTime = millis();
void loop() {
  // put your main code here, to run repeatedly:
  if ((!client.connected()) && millis()-cmpTime > 5000) {
    reconnect();
    cmpTime = millis();
  }

  MDNS.update();

  if(client.connected()){
    client.loop();
    cmpTime = millis();
  }

  webServer.handleClient();
  delay(10);
  // Serial.print("in loop");
  if(resetWifiFlag){
    wifiManager.resetSettings();
    resetWifiFlag = false;
    ESP.reset();
  }

}