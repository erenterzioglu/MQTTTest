#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include <ESP8266WebServer.h>
//#include <iostream>

#define MESSAGE_BUFFER_SIZE 20

extern ESP8266WebServer webServer;
extern std::vector<std::string> messages;

void configWebServer();

#endif