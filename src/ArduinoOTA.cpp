#include "Arduino.h"
#include <ArduinoOTA.h>
#include "ArduinoOTA.hpp"

void ArduinoOTA_init(const char* name)
{
    // строчка для номера порта по умолчанию
    // можно вписать «8266»:
    // ArduinoOTA.setPort(8266);
    // строчка для названия хоста по умолчанию;
    // можно вписать «esp8266-[ID чипа]»:
    ArduinoOTA.setHostname(name);
    // строчка для аутентификации
    // (по умолчанию никакой аутентификации не будет):
    // ArduinoOTA.setPassword((const char *)"123");
    ArduinoOTA.onStart([]() 
    {
        Serial.println("Start"); //  "Начало OTA-апдейта"
    });
    ArduinoOTA.onEnd([]() 
    {
        Serial.println("\nEnd"); //  "Завершение OTA-апдейта"
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) 
    {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) 
    {
        Serial.printf("Error[%u]: ", error);
        switch (error)
        {
        case OTA_AUTH_ERROR:
            Serial.println("Auth Failed");
            //  "Ошибка при аутентификации"
            break;
        case OTA_BEGIN_ERROR:
            Serial.println("Begin Failed");
            //  "Ошибка при начале OTA-апдейта"
            break;
        case OTA_CONNECT_ERROR:
            Serial.println("Connect Failed");
            //  "Ошибка при подключении"
            break;
        case OTA_RECEIVE_ERROR:
            Serial.println("Receive Failed");
            //  "Ошибка при получении данных"
            break;
        case OTA_END_ERROR:
            Serial.println("End Failed");
            //  "Ошибка при завершении OTA-апдейта"
        default:
            Serial.println("Something was wrong");
            break;
        }
    });
    ArduinoOTA.begin();
}