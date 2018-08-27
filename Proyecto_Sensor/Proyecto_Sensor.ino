#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include "ESPAWSImplementations.h"

EspHttpClient httpClient;
EspDateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;

const char* ssid            =   "iPhone de Jhon";
const char* password        =   "1234567890";
const String OpenPaq        =   "{\"state\":{\"reported\":{"; 
const String SensorName     =   "\"Temperatura\":";
const String ClosePaq       =   "}}}";

String Data;//Cadenas de caracteres con las cuales se completa una sombra

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WAP
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  iotClient.setAWSRegion("us-east-1");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("Enpoint");
  iotClient.setAWSPath("/things/HomeIO/shadow");
  iotClient.setAWSKeyID("ID");
  iotClient.setAWSSecretKey("Key");
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void loop(){
  String Sombra =OpenPaq+SensorName+random(14, 30)+ClosePaq;
  char shadow[100];
  int len= Sombra.length()+1;
  char Datos[len];
  Sombra.toCharArray(Datos,len);
  strcpy(shadow,Datos);
//  const char* shadow = strcat(OpenPaq,SensorName);
  //OpenPaq+SensorName+ClosePaq;
 // const char* shadow = "{\"state\":{\"reported\": {\"foobar\": 20}}}";
  const char* result = iotClient.update_shadow(shadow, actionError);

  Serial.print(result);

  delay(1000);
}
