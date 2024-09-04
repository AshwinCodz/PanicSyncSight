#include <WiFi.h>
#include "ThingSpeak.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

//WIFI STATION USER NAME PASSWORD
const char* WIFI_ssid     = "Gangadharan";
const char* WIFI_password = "Dharan@2021";

//wifi station ip configuration 
IPAddress WIFI_local_IP(192,168,137,174);
IPAddress WIFI_gateway(192, 168, 1, 1);
IPAddress WIFI_subnet(255, 255, 255, 0);
IPAddress WIFI_primaryDNS(8, 8, 8, 8); 
IPAddress WIFI_secondaryDNS(8, 8, 4, 4);

const int myChannelNumber =2226105 ;
const char* myApiKey = "5ZZNFKTB60NEJIV9";
const char* server = "api.thingspeak.com";

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int leadOffPlusPin = 12;  
const int leadOffMinusPin = 13; 
const int ecgAnalogPin = 36;

void setup() {
  Serial.begin(9600);

  mlx.begin();
  pinMode(leadOffPlusPin, INPUT);
  pinMode(leadOffMinusPin, INPUT);
  //clear old config
  WiFi.disconnect(true);        //disable wifi station 
  WiFi.softAPdisconnect(true);  //disable wifi access point 

  pinMode(2, OUTPUT);           // Inbuilt LED light
  delay(1000);                  // Some delay
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  Serial.println("PROJECT NAME      : ESP32 WIFI STATION");
  Serial.print  ("WIFI SSID         : ");
  Serial.println(WIFI_ssid);
  Serial.print  ("WIFI PASSWORD     : ");
  Serial.println(WIFI_password);
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  digitalWrite(2,HIGH);
  delay(500);
  digitalWrite(2,LOW);

  connectWiFi();
   while ((!(WiFi.status() == WL_CONNECTED)))
    {
      connectWiFi();
    }
}

void loop() {
  
  int object_temp_c = mlx.readObjectTempC();
  int object_temp_f = mlx.readObjectTempF();
  int ambient_temp_c = mlx.readAmbientTempC();
  int ambient_temp_f = mlx.readAmbientTempF();
  int ecgValue = analogRead(ecgAnalogPin);
  Serial.println((String) "Object Temperature = " + object_temp_c + " \xC2\xB0" + "C (or) " + object_temp_f + " \xC2\xB0" + "F");
  Serial.println((String) "Ambient Temperature = " + ambient_temp_c + " \xC2\xB0" + "C (or) " + ambient_temp_f + " \xC2\xB0" + "F");
  Serial.println("---------------------");
  Serial.println(ecgValue); // Indicate lead off condition    
  //ThingSpeak.setField(1,ecgValue);
  //ThingSpeak.setField(2,object_temp_c);
  //ThingSpeak.setField(3,ambient_temp_c); 
  //ThingSpeak.writeFields(myChannelNumber, myApiKey);
 // int x = ThingSpeak.writeFields(myChannelNumber, myApiKey);
 // if(x == 200){
   // Serial.println("Data pushed successfull");
 // }else{
 //   Serial.println("Push error" + String(x));
 // }
 // Serial.println("---");
  delay(1000);

}
void connectWiFi()
{ 
  Serial.println("Connecting to WIFi....");
  int i=0;

  WiFi.mode(WIFI_STA);
  WiFi.config(WIFI_local_IP, WIFI_gateway, WIFI_subnet, WIFI_primaryDNS, WIFI_secondaryDNS);
  WiFi.begin(WIFI_ssid, WIFI_password);
  
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    digitalWrite(2,HIGH);
    delay(300);
    digitalWrite(2,LOW);
    delay(200);
    
    Serial.println(" - ");
    i++;
    if(i > 10)    
    { 
      return;
    }
  }

  digitalWrite(2,HIGH);
  delay(400);
  digitalWrite(2,LOW);

  Serial.println("WIFI connected");

  Serial.print("WIFI IP ADDRESS       : ");
  Serial.println(WiFi.localIP());

  Serial.print("WIFI Strength         : ");
  Serial.println(WiFi.RSSI());

  Serial.print("ESP32 MAC address     : ");
  Serial.println(WiFi.macAddress());
}
