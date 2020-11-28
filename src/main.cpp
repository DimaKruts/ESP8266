#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 
#include "ArduinoOTA.hpp"
#include "FileSystem.hpp"
#include "Configer.hpp"
#include "SSDP.hpp"
#include "DES.h"

const char* name = "ESP_TEST";
const char* ssid = "TP-Link_A6DC";
const char* password = "91160799";
const int ESP_BUILTIN_LED = 2;

ESP8266WebServer HTTP(80);

void setup() 
{
  Serial.begin(115200);
  Serial.println("Booting");  //  "Загрузка"
  FS_init();
  Config cnfg;
  loadConfiguration(Config_File, cnfg);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  HTTP.begin();
  ArduinoOTA_init(name);
  SSDP_init(HTTP, name);
  Serial.println("Ready");  //  "Готово"
  Serial.print("IP address: ");  //  "IP-адрес: "
  Serial.println(WiFi.localIP());
  pinMode(ESP_BUILTIN_LED, OUTPUT);
  
  HTTP.onNotFound([&]() {                              // If the client requests any URI
    if (!handleFileRead(HTTP, HTTP.uri()))                  // send it if it exists
      HTTP.send(404, "text/plain", "404: Not Found"); // otherwise, respond with a 404 (Not Found) error
  });
  HTTP.on("/test", []() {
    HTTP.send(200, "text/plain", "OK");
  });
}


void loop() 
{
  HTTP.handleClient();
  ArduinoOTA.handle();
  digitalWrite(ESP_BUILTIN_LED, LOW);
  delay(1000);
  digitalWrite(ESP_BUILTIN_LED, HIGH);
  delay(1000);
}
