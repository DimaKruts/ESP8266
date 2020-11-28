#include "SSDP.hpp"
#include "Arduino.h"
#include <ESP8266WiFi.h>  
#include <ESP8266SSDP.h>
#include <ESP8266WebServer.h>  


void SSDP_init(ESP8266WebServer& http, const char* name)
{
  // SSDP дескриптор
  http.on("/description.xml", HTTP_GET, [&]() 
  {
    SSDP.schema(http.client());
  });
  //Если версия  2.0.0 закаментируйте следующую строчку
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(name);
  SSDP.setSerialNumber(ESP.getChipId());
  SSDP.setURL("/");
  SSDP.setModelName("SSDP");
  SSDP.setModelNumber("000000000001");
  SSDP.setModelURL("https://www.google.com/");
  SSDP.setManufacturer("Tretyakov Sergey");
  SSDP.setManufacturerURL("https://www.google.com/");
  SSDP.begin();
}