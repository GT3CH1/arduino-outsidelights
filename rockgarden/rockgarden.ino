#include <aa_lib.h>
#include <aREST.h>
#include "secret.h"
int LIGHT_PIN = 2;

aREST m_rest = aREST();
WiFiServer m_server(80);
aa_lib automation(WIFI_SSID, WIFI_PASSWORD, DEVICE_TYPE, UPDATE_SERVER, SERVER_PORT, VERSION, API_KEY, API_ID);
String ipAddr;
String lastIpAddr;
void setup() {
  // put your setup code here, to run once:
  automation.setup();
  m_server.begin();
  m_rest.function("on", setOn);
  m_rest.function("off", setOff);
  checkGuid(GUID,automation.getLastState(GUID));
}

void loop() {
  automation.checkAndConnectWifi();
  automation.handleSketchDownload();
  ipAddr = automation.getIP();
  if (lastIpAddr != ipAddr){
    lastIpAddr = ipAddr;
    Serial.println("Updating in database");
    automation.sendUpdate(GUID);
  }
  WiFiClient client = m_server.available();
  if (!client) {
     return;
  }
  while(!client.available()){
    delay(1);
  }
  m_rest.handle(client);
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
  if (guid == GUID){
    pinMode(LIGHT_PIN,OUTPUT);
    digitalWrite(LIGHT_PIN, state ? LOW : HIGH);
  }
}
