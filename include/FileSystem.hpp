#pragma once
#include "Arduino.h"
#include <ESP8266WebServer.h> 

void FS_init(void);
String getContentType(String);
bool handleFileRead(ESP8266WebServer& HTTP, String path);