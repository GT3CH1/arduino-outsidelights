#include "secret.h"
#include <SPI.h>
#include <WiFiNINA.h>
#include <aREST.h>

int status = WL_IDLE_STATUS;
aREST rest = aREST();
WiFiServer server(80);
int LIGHT_PIN = 2;
bool output;
void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  // put your setup code here, to run once:
  Serial.print("Connecting");
  while(status != WL_CONNECTED){
    status = WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
    Serial.print(".");
    delay(3000);
  }
  Serial.println("");
  Serial.println("Connected.");
  printIP();
  server.begin();
  rest.variable("connected",&status);
  // Lights
  rest.variable("6eaeba5c-9e24-4e85-a21e-afcadc2c967a",&output);
  rest.function("on", setOn);
  rest.function("off", setOff);
}

void printIP(){
    IPAddress ip = WiFi.localIP();
    Serial.println("IP Address: ");
    Serial.println(ip);
}
  
void loop() {
  WiFiClient client = server.available();
  rest.handle(client);
}

int setOn(String guid){
    checkGuid(guid,true);
    return 1;
}

int setOff(String guid){
    checkGuid(guid,false);
    return 1;
}

void checkGuid(String guid, bool state){
  if (guid == "6eaeba5c-9e24-4e85-a21e-afcadc2c967a"){
    pinMode(LIGHT_PIN,OUTPUT);
    digitalWrite(LIGHT_PIN, state ? LOW : HIGH);
  }
}
