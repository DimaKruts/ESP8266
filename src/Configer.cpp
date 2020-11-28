#include <Arduino.h>
#include <FS.h>
#include <ArduinoJson.h>
#include "Configer.hpp"

void loadConfiguration(const char *filename, Config &config) 
{
  File file = SPIFFS.open(filename, "r");  // Open file for reading
  StaticJsonDocument<Buffer_Size> doc;// Allocate a temporary JsonDocument
  DeserializationError error = deserializeJson(doc, file);// Deserialize the JSON document
  if (error) Serial.println(F("Failed to read file, using default configuration"));
  //=======================================[WiFi]========================================
  config.wifi[0].name = doc["WiFi"]["main"]["name"].as<String>();
  config.wifi[0].pass = doc["WiFi"]["main"]["pass"].as<String>();
  config.wifi[1].name = doc["WiFi"]["AP"]["name"].as<String>();
  config.wifi[1].pass = doc["WiFi"]["AP"]["pass"].as<String>();
  config.wifi[2].name = doc["WiFi"]["reserve"]["name"].as<String>();
  config.wifi[2].pass = doc["WiFi"]["reserve"]["pass"].as<String>();
  //=======================================[MQTT]========================================
  config.mqtt.broker = doc["MQTT"]["broker"].as<String>();
  config.mqtt.name = doc["MQTT"]["name"].as<String>();
  config.mqtt.pass = doc["MQTT"]["pass"].as<String>();
  config.mqtt.port = doc["MQTT"]["port"];
  int arraySize = doc["MQTT"]["topic"]["listen"].size();
  for(int i = 0; i < arraySize; ++i)
    config.mqtt.listen.push_back(doc["MQTT"]["listen"][i].as<String>());
  arraySize = doc["MQTT"]["topic"]["publish"].size();
  for(int i = 0; i < arraySize; ++i)
    config.mqtt.publish.push_back(doc["MQTT"]["publish"][i].as<String>());
  //=======================================[END]=========================================
  file.close();// Close the file (Curiously, File's destructor doesn't close the file)
}

// Saves the configuration to a file
void saveConfiguration(const char *filename, const Config &config) 
{
  SPIFFS.remove(filename);// Delete existing file, otherwise the configuration is appended to the file
  File file = SPIFFS.open(filename, "w");  // Open file for writing
  if (!file) 
  {
    Serial.println(F("Failed to create file"));
    return;
  }
  StaticJsonDocument<Buffer_Size> doc; // Allocate a temporary JsonDocument
  // Set the values in the document
  //=======================================[WiFi]========================================
  doc["WiFi"]["main"]["name"] = config.wifi[0].name;
  doc["WiFi"]["main"]["pass"] = config.wifi[0].pass;
  doc["WiFi"]["AP"]["name"] = config.wifi[1].name;
  doc["WiFi"]["AP"]["pass"] = config.wifi[1].pass;
  doc["WiFi"]["reserve"]["name"] = config.wifi[2].name;
  doc["WiFi"]["reserve"]["pass"] = config.wifi[2].pass;
  //=======================================[MQTT]========================================
  doc["MQTT"]["broker"] = config.mqtt.broker;
  doc["MQTT"]["port"] = config.mqtt.port;
  doc["MQTT"]["name"] = config.mqtt.name;
  doc["MQTT"]["pass"] = config.mqtt.pass;
  for(auto tmp:config.mqtt.listen)
    doc["MQTT"]["listen"].add(tmp);
  for(auto tmp:config.mqtt.publish)
    doc["MQTT"]["publish"].add(tmp);
  //=======================================[END]=========================================
  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) 
  {
    Serial.println(F("Failed to write to file"));
  }
  file.close();// Close the file
}

// Prints the content of a file to the Serial
void printFile(const char *filename)
{
  File file = SPIFFS.open(filename, "r"); // Open file for reading
  if (!file) 
  {
    Serial.println(F("Failed to read file"));
    return;
  }
  while (file.available()) // Extract each characters by one by one 
  {
    Serial.print((char)file.read());
  }
  Serial.println();
  file.close();// Close the file
}
