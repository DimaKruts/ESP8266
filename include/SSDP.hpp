#pragma once

#include "Arduino.h"
#include <ESP8266WebServer.h>  

void SSDP_init(ESP8266WebServer& HTTP, const char* name);