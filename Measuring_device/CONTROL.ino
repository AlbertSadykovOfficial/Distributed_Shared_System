#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "ASUS";
const char* password = "albus4082";

String OBJECT = "Pipeline_1";
String ID     = "Pump";

String host = "http://192.168.1.3:80";
String reg_link = "/oil_depot/reg.php?object="+OBJECT+"&id="+ID;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
HTTPClient httpClient;

void connect_LED(String value)
{
    if (value == "ON") { digitalWrite(4, 1); } 
    if (value == "OFF"){ digitalWrite(4, 0); }
}

void setup(void) 
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);
    
    connect_to_WIFI();
    
    httpUpdater.setup(&httpServer);
    httpServer.begin();
    httpServer.on("/gpio_ON", handleLedOn);
    httpServer.on("/gpio_OFF", handleLedOff);
    
    pinMode(4,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(14,OUTPUT);
}

void connect_to_WIFI()
{
     bool was_disconnect = false;
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        was_disconnect = true;
        connect_LED("OFF");
        delay(3000); // Делаем паузу, чтобы не зависло
    }
    if (was_disconnect)
    {
        registration();
    }
    
    connect_LED("ON");
}

void handleLedOn() { digitalWrite(14, 1); digitalWrite(12, 1); digitalWrite(13, 1); }
void handleLedOff(){ digitalWrite(14, 0); digitalWrite(12, 0); digitalWrite(13, 0); }


void registration()
{
    httpClient.begin(host + reg_link);
    httpClient.GET();
    httpClient.end();
}


void loop(void) 
{
    connect_to_WIFI();
    httpServer.handleClient();
}
