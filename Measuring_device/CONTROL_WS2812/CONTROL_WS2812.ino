#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

// Данные Роутера
const char* ssid     = "ASUS";
const char* password = "albus4082";

// Идентификаторы устрйоства(ID-устройства и Объект на котором он расположен)
String OBJECT = "Pipeline_1";
String ID     = "Pump";

// Сокет (ip+port) сервера
String host = "http://192.168.1.3:80";
String reg_link = "/oil_depot/reg.php?object="+OBJECT+"&id="+ID;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
HTTPClient httpClient;

//------------------------------------
#include <NeoPixelAnimator.h>
#include <NeoPixelBrightnessBus.h>
#include <NeoPixelBus.h>
#include <NeoPixelSegmentBus.h>

#include <FastLED.h>

#define LED_COUNT 24 // число пикселей в ленте
#define LED_DT 2    // пин, куда подключен DIN ленты (номера пинов ESP8266 совпадает с Arduino)  

uint8_t bright = 10; // яркость (0 - 255)
uint8_t ledMode = 0; // эффект (0 - 29)

uint8_t flag = 1; // флаг отмены эффекта

CRGBArray<LED_COUNT> leds;

uint8_t delayValue = 2; // задержка
uint8_t stepValue = 10; // шаг по пикселям
uint8_t hueValue = 0; // тон цвета

void updateColor(uint8_t r,uint8_t g,uint8_t b)
{
    for(uint8_t i = 0 ; i < LED_COUNT; i++ )
    {
        leds[i].setRGB(r,g,b);
    }
}

uint8_t idex = 0; //индекс текущего пикселя    
uint8_t ihue = 0; // тон цвета
uint8_t saturationVal = 255; // насыщенность 
void white_loop()
{ 
    idex++;
    ihue = ihue + stepValue;
    if(idex >= LED_COUNT)
    {
        idex = 0;
    }
    leds[idex].setRGB(ihue,ihue,ihue);//CHSV(255, 0, 255);
    LEDS.show();
    delay(delayValue);
}
void rainbow_loop()
{ 
    idex++;
    ihue = ihue + stepValue;
    if(idex >= LED_COUNT)
    {
        idex = 0;
    }
    if(ihue > 255){
        ihue = 0;
    }
    leds[idex] = CHSV(ihue, saturationVal, 255);
    LEDS.show();
    delay(delayValue);
}
//------------------------------------
void connect_LED(String value)
{
    if (value == "ON") { digitalWrite(16, 1); } 
    if (value == "OFF"){ digitalWrite(16, 0); }
}

void setup(void) 
{
    build.path=D:\WorkSpace\eng
    pinMode(16,OUTPUT);
    
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);
    
    connect_to_WIFI();
    
    httpUpdater.setup(&httpServer);
    httpServer.begin();
    httpServer.on("/gpio_ON", handleLedOn);
    httpServer.on("/gpio_OFF", handleLedOff);

    LEDS.setBrightness(bright);
    LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настройки для вашей ленты (ленты на WS2811, WS2812, WS2812B)
    LEDS.show();
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

void handleLedOn() { ledMode = 1; digitalWrite(14, 1); digitalWrite(12, 1); digitalWrite(13, 1); }
void handleLedOff()
{ 
    ledMode = 0; 
    updateColor(0,0,0);
    LEDS.show();
}


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
    if (ledMode == 1)
    {
        white_loop();
        //rainbow_loop();
    }
}
