# MQTTTEST

This project is an test dashboard for MQTT projects. Project developed with
an ESP8266 microcontroller and Arduino libray choosed for development.  

## Features
* Wi-Fi Configration
* Broker Configration
* Messages watching from a topic
* Reset Wi-Fi
* Change Broker
* Keep changes on reboot

All of the above can be handled without changing the code

## Used Libaries
* [PubSubClient](https://github.com/knolleary/pubsubclient)
* [mDNS](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266mDNS)
* [ArduinoJSON](https://arduinojson.org/)
* [WiFiManager](https://github.com/tzapu/WiFiManager)
* Some internal Espressif Libraries like FS.h,  DNSServer.h, ESP8266Webserver.h
, ESP8266WiFi.h and so on

## How To Run This Project
Project development in PlatformIO. After downloading project code open in
PlatformIO enviroment and check Espressif Platform extension has been installed.
If you faced issues, firstly please check libraries has been installed correctly
and then check path settings are correct.

## How To Connect The Server
Project has an mDNS solution for connect to the server
easily, but it runs sometimes buggy and response rate is
a bit slow on my tests. You can connect to the server with IP and device prints
its IP while starting the server. If mDNS works great you can access the web
interface with "esp8266.local/" address.

## Features can be added
* Multiple MQTT server, port number and topic support.
* Publish data to the broker support.
* WebUI can be modified more beautifully.
* Server response time can be upgrade.
* Connection supoort for some server that requires logging in for safety.

## Important notes for developers
If you interested the project and develop it you might faced some issues and you should know theese:

* If you have a Wi-Fi extender, you should check which network you and server are connected.
* IP address of the server changes sometimes, you should check the IP address or modify the code for static IP address. Hopefully this problem can be handled easily with WiFi-Manager library
* If you want to change configration json file or something goes wrong, you can erase flash with:  ["esptool.py erase_flash"](https://www.esp8266.com/viewtopic.php?f=6&t=3955)

### Some tutorials that you can follow to develop this kind of project
* Webserver Tutorials:
  * [Introduction to WebServer](https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/)
  * [Webserver using mDNS](https://tttapa.github.io/ESP8266/Chap10%20-%20Simple%20Web%20Server.html)
  * [Webserver with multiple pages](https://www.arduinoslovakia.eu/blog/2019/4/esp8266---http-server-s-viac-strankami?lang=en)
* [WiFi Manager with server configration](https://github.com/tzapu/WiFiManager/blob/master/examples/AutoConnectWithFSParameters/AutoConnectWithFSParameters.ino)
* PubSubClient tutorials:
  * [Library Documentation](https://pubsubclient.knolleary.net/api)
  * [Sample MQTT configration](https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_esp8266/mqtt_esp8266.ino)
