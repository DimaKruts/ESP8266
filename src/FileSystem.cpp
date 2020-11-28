#include "Arduino.h"
#include "FileSystem.hpp"

#include <FS.h>
#include <vector>
#include <ESP8266WebServer.h> 

std::vector<String> files;

void FS_init(void)
{
  SPIFFS.begin();
  Dir dir = SPIFFS.openDir("/");
  while (dir.next())
  {
   files.push_back(dir.fileName());
  }
}

bool find(String tmp)
{
  for(auto file:files)
  {
    if(tmp == file)
    return true;
  }
  return false;
}

String getContentType(String filename)
{
  if(filename.endsWith(".htm")) return "text/html";
  else if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".png")) return "image/png";
  else if(filename.endsWith(".gif")) return "image/gif";
  else if(filename.endsWith(".jpg")) return "image/jpeg";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".xml")) return "text/xml";
  else if(filename.endsWith(".pdf")) return "application/x-pdf";
  else if(filename.endsWith(".zip")) return "application/x-zip";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

// bool handleFileRead(ESP8266WebServer& HTTP, String path)
// {  // send the right file to the client (if it exists)
//   //Serial.println("handleFileRead: " + path);
//   if(path.endsWith("/")) path += "index.html";           // If a folder is requested, send the index file
//   String contentType = getContentType(path);             // Get the MIME type
//   String pathWithGz = path + ".gz";
//   if(SPIFFS.exists(pathWithGz) || SPIFFS.exists(path))
//   {  // If the file exists, either as a compressed archive, or normal
//     if(SPIFFS.exists(pathWithGz))                          // If there's a compressed version available
//       path += ".gz";                                         // Use the compressed version
//     File file = SPIFFS.open(path, "r");                    // Open the file
//     size_t sent = HTTP.streamFile(file, contentType);    // Send it to the client
//     file.close();                                          // Close the file again
//     //Serial.println(String("\tSent file: ") + path);
//     return true;
//   }
//   //Serial.println(String("\tFile Not Found: ") + path);
//   return false;                                          // If the file doesn't exist, return false
// }

bool handleFileRead(ESP8266WebServer& HTTP, String path)
{ 
  if(path.endsWith("/")) path += "index.html";           // If a folder is requested, send the index file
  String contentType = getContentType(path);             // Get the MIME type
  String pathWithGz = path + ".gz";
  if(find(pathWithGz) || find(path))
  {  // If the file exists, either as a compressed archive, or normal
    if(find(pathWithGz))                          // If there's a compressed version available
      path += ".gz";                                         // Use the compressed version
    File file = SPIFFS.open(path, "r");                    // Open the file
    int start = millis();
    HTTP.streamFile(file, contentType);    // Send it to the client
    Serial.print(String("\tSent file: ") + path);
    Serial.println(String("\ttime: ") + (millis() - start));
    file.close();                                          // Close the file again
    return true;
  }
  return false;                                          // If the file doesn't exist, return false
}
