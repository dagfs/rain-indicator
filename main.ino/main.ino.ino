#include <Arduino.h>

#include <Wire.h> // input output
#include <SPI.h>
#include <ESP8266WiFi.h>        // ESP WiFi module
#include <ESP8266WiFiMulti.h>   // ESP WiFi module
#include <ESP8266HTTPClient.h>


ESP8266WiFiMulti WiFiMulti;

    HTTPClient http;

int RED_LEDS = 5;//pin D1

void init_wifi() {
    WiFiMulti.addAP("Dag", "12345678");
    digitalWrite(RED_LEDS, LOW);
    delay(5000);
    digitalWrite(RED_LEDS, HIGH);
    bool connected = false;
    while(!connected){
      digitalWrite(RED_LEDS, LOW);
    delay(1000);
    digitalWrite(RED_LEDS, HIGH);
      if(WiFiMulti.run() == WL_CONNECTED){
          connected = true;
        }
      }
    

}



void init_led() {
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
}

void setup() {
  Serial.begin (115200);
    init_led();
    init_wifi();
    
        Serial.print("Setup");
}

String response;

void loop() {
        http.begin("http://rain-indicator.eu-gb.cf.appdomain.cloud/rain");
        int httpCode = http.GET();
        response = http.getString();

        
  Serial.print("httpCode: ");
        Serial.print(httpCode);
        
  Serial.print("Response: ");
        Serial.print(response);
        
  Serial.print("\n");
        if(response[0] == '1'){
          digitalWrite(5, HIGH);//d1
    
          } else {
            
    digitalWrite(5, LOW);
            }

            if(response[1] == '1'){
          digitalWrite(4, HIGH);//d3
    
          } else {
            
    digitalWrite(4, LOW);
            }

            if(response[2] == '1'){
          digitalWrite(0, HIGH);//
    
          } else {
            
    digitalWrite(0, LOW);
            }

            if(response[3] == '1'){
          digitalWrite(2, HIGH);
    
          } else {
            
    digitalWrite(2, LOW);
            }
        http.end();
        delay(3600000);


}
