#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <SPI.h>
#include <SD.h>

#include "Ultrasonic.h"
Ultrasonic ultrasonic(5,4); 

// Данные Роутера
const char* ssid     = "ASUS";
const char* password = "albus4082";

// Идентификаторы устрйоства(ID-устройства и Объект на котором он расположен)
String OBJECT = "Reservoir_1";
String SENSOR = "UZ_1";

// Сокет (ip+port) сервера
String host = "http://192.168.1.3:80";

String uad_link   = host + "/oil_depot/uad.php";
String write_link = "/oil_depot/write.php?object="+OBJECT+"&sensor="+SENSOR;


HTTPClient http;
File myFile;
int time_now = 0;


void connect_LED(String value)
{
    if (value == "ON") { digitalWrite(2, 0); } 
    if (value == "OFF"){ digitalWrite(2, 1); }
}

void check_connection()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        connect_LED("OFF");
        bank_mode();
    }
    connect_LED("ON");
}

void send_GET(String link, String data)
{
    http.begin(link + data);
    http.GET();
    http.end();
}

void send_POST(String link, String data)
{
    http.begin(link);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.POST(data);
    http.end();
}

void send_data()
{
    String data_link, value;
    
    if (millis() - time_now >= 5000)
    {
        time_now = millis();
        data_link = write_link + "&data=" + get_volume();
        send_GET(host, data_link);
    }
}

void write_to_SD(String file)
{
    myFile = SD.open(file, FILE_WRITE);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        myFile.print(get_volume());
        myFile.println(";(disconnect)");
        delay(5000); // Делаем паузу, чтобы не зависло
    }
    myFile.close();
}

String read_from_SD(String file)
{
    String data;
    myFile = SD.open(file);
    
    data = "object="+OBJECT + "&sensor="+SENSOR + "&data=";
    while (myFile.available())
    {
       char ltr = myFile.read();
       data += ltr;
    }
    myFile.close();
    SD.remove(file);
    
    return data;
}

void bank_mode()
{
    String filename = "bank1.txt";
    write_to_SD(filename);
    send_POST(uad_link, read_from_SD(filename));
}

String get_volume()
{
  return String(102 - 2 * ultrasonic.Ranging(CM));
}

void setup() 
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    if (!SD.begin(4)) 
    {
        return;
    }
    
    pinMode(2,OUTPUT);
    time_now = millis();
}

void loop()
{
    check_connection();
    send_data();
}
