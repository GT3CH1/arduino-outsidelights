#include <GoogleArduino.h>
#include "secret.h"

const int lightPin = 2;
const int resetPin = 4;
int invertedPins[] = {};
GoogleArduino automation(resetPin);

void setup(){
  automation.setup(FIREBASE_HOST,FIREBASE_AUTH,WIFI_SSID,WIFI_PASSWORD,invertedPins);
  automation.firstRun("1",lightPin);
}

void loop(){
  automation.checkStatus("1",lightPin);
  delay(5000);
}
