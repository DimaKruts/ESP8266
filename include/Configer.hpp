#pragma once

#include "Arduino.h"
#include <vector>

#define Config_File "config.json"
#define Buffer_Size 2048

struct WIFI
{
  String name;
  String pass;
};

struct MQTT 
{
  String broker, name, pass;
  int port;
  std::vector<String> listen;
  std::vector<String> publish;
};

struct Config
{
  WIFI wifi[3];
  MQTT mqtt;
};

void loadConfiguration(const char *filename, Config &config);
void saveConfiguration(const char *filename, const Config &config);
void printFile(const char *filename);