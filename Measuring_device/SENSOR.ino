#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <SPI.h>
#include <SD.h>

#include "Ultrasonic.h"
Ultrasonic ultrasonic(5,4); 

  const char* ssid     = "ASUS";
  const char* password = "albus4082";

  String OBJECT = "RES_1";
  String SENSOR = "UZ_1";
   
  String host = "192.168.1.3";
  int port = 80;
  String link = "/new_site/write.php?object="+OBJECT+"&sensor="+SENSOR;

  HTTPClient http;
  File myFile;
  int time_now =0;
  void setup() 
  {
    Serial.begin(9600);
    WiFi.mode(WIFI_STA); // Задаем режим работы WIFI_STA (клиент)
    WiFi.begin(ssid, password); // Подключаемся
 
    if (!SD.begin(4)) 
    {
      return;
    }
    time_now = millis();
    Serial.println(time_now, millis());
  }
  
  void send_data()
  {
    //if (millis() - time_now >= 1000)
    //{
        //time_now = millis();
        //Serial.println(time_now);
        
        String link_rand = link + "&data=" + String(102 - 2 * ultrasonic.Ranging(CM));
        
        http.begin(host, port, link_rand);
        http.GET();
        //Serial.println(http.GET());
        http.end();
        delay(5000);
    //}
  }
  
  void check_connection()
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      //bank_mode();
      delay(1000);
    }
  }
  
  void bank_mode()
  {
       String str;
        myFile = SD.open("bank1.txt", FILE_WRITE);
        if (myFile) 
        {
            while (WiFi.status() != WL_CONNECTED) // Ждем пока статус не станет WL_CONNECTED
            {
                if (millis() - time_now >= 5000)
                {
                    time_now = millis();
                    //myFile.print("14:10:15;");
                    myFile.print(String(102 - 2 * ultrasonic.Ranging(CM)));
                    myFile.println(";(disconnect)");
                }
            }            
        } 
        myFile.close();
       
       str = "object="+OBJECT+"&sensor="+SENSOR+"&data=";
       myFile = SD.open("bank1.txt");
       while (myFile.available())
       {
         char ltr = myFile.read();
         str += ltr;
       }
       myFile.close();
       SD.remove("bank1.txt");
       
       http.begin("http://192.168.1.3:80/new_site/uad.php");
       http.addHeader("Content-Type", "application/x-www-form-urlencoded");
       http.POST(str);
       http.end();
  }
  void loop()
  {
    check_connection();
    send_data();
  }
