#include "UbidotsMicroESP8266.h"
#define TOKEN  "Your_token_here"  // Put here your Ubidots TOKEN
#define WIFISSID "Your_WiFi_SSID"
#define PASSWORD "Your_WiFi_Password"

Ubidots client(TOKEN);

void setup(){
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}
void loop(){
    float value = analogRead(A0);
    float value2 = analogRead(A1);
    float value3 = analogRead(A2);
    client.add("Temperature", value);
    client.add("Humidity", value2);
    client.add("Heat Index", value3);
    client.sendAll(true);
}