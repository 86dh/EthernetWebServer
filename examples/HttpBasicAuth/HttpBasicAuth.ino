/****************************************************************************************************************************
 *  HTTPBasicAuth.h - Dead simple web-server for Ethernet shields
 *
 * EthernetWebServer is a library for the Ethernet shields to run WebServer
 *
 * Forked and modified from ESP8266 https://github.com/esp8266/Arduino/releases
 * Built by Khoi Hoang https://github.com/khoih-prog/ESP8266_AT_WebServer
 * Licensed under MIT license
 * Version: 1.0.0
 *
 * Original author:
 * @file       Esp8266WebServer.h
 * @author     Ivan Grokhotkov
 *
 * Version Modified By   Date      Comments
 * ------- -----------  ---------- -----------
 *  1.0.0   K Hoang      13/02/2020 Initial coding for Arduino Mega, Teensy, etc
 *****************************************************************************************************************************/

#include <SPI.h>
#include <Ethernet.h>
#include <EthernetWebServer.h>

#ifdef CORE_TEENSY
  // For Teensy 4.0
  #if defined(__IMXRT1062__)
  #define BOARD_TYPE      "TEENSY 4.0"
  #elif ( defined(__MKL26Z64__) || defined(ARDUINO_ARCH_AVR) )
  #define BOARD_TYPE      "TEENSY LC or 2.0"
  #else
  #define BOARD_TYPE      "TEENSY 3.X"
  #endif
#else
// For Mega
#define BOARD_TYPE      "AVR Mega"
#endif

// Enter a MAC address and IP address for your controller below.

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

// Select the IP address according to your local network
IPAddress ip(192, 168, 2, 100);

EthernetWebServer server(80);

const char* www_username = "admin";
const char* www_password = "ethernet";

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nStarting HTTPBasicAuth on " + String(BOARD_TYPE));

  // start the ethernet connection and the server:
  Ethernet.begin(mac, ip);

  server.on("/", []() 
  {
    if (!server.authenticate(www_username, www_password)) 
    {
      return server.requestAuthentication();
    }
    server.send(200, "text/plain", "Login OK");
  });
  
  server.begin();

  Serial.print(F("HTTP EthernetWebServer started @ IP : "));
  Serial.println(Ethernet.localIP());

  Serial.print(F("Open http://"));
  Serial.print(Ethernet.localIP());
  Serial.println(F("/ in your browser to see it working"));
}

void loop() 
{
   server.handleClient();
}