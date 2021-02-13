#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "ASUS";
const char* password = "albus4082";

String OBJECT = "Pipeline_1";
String ID     = "SLAVE_LED_GADGET(Valve)";


ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;
HTTPClient httpClient;

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);

  connect_to_WIFI();
  
  httpUpdater.setup(&httpServer);
  httpServer.begin();
  httpServer.on("/gpio_ON", handleLedOn);
  httpServer.on("/gpio_OFF", handleLedOff);
  
  pinMode(2,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(14,OUTPUT);
  digitalWrite(2, 1);
  Serial.println("setup");
}

void connect_to_WIFI()
{
   bool was_disconnect = false;
   while (WiFi.status() != WL_CONNECTED) 
  {
    was_disconnect = true;
    WiFi.begin(ssid, password);
    Serial.println("trying");
    delay(3000); // ОЧЕНЬ!!! ОЧЕНЬ !!! ОЧЕНЬ ВАЖНО!!!! Иначе все встанет и не найти ошибку 
  }
  if (was_disconnect)
  {
    registration();
  }
}
void handleLedOn() { digitalWrite(14, 1); digitalWrite(12, 1); digitalWrite(13, 1); }
void handleLedOff(){ digitalWrite(14, 0); digitalWrite(12, 0); digitalWrite(13, 0); }
void registration()
{
    Serial.println("registration");
       String host = "192.168.1.3";
       int port = 80;
       String link = "/new_site/reg.php?object="+OBJECT+"&id="+ID;//+"&ip="+ipToString(WiFi.localIP());
        
        httpClient.begin(host, port, link);
        Serial.println(httpClient.GET());
        httpClient.end();
}

void loop(void) 
{
  connect_to_WIFI();
  httpServer.handleClient();
}
