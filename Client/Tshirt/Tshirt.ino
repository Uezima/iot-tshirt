/******************************************************
 ******************************************************
 *       _       _     _       _     _      _         *       
 *      (_)     | |   | |     | |   (_)    | |        * 
 *       _  ___ | |_  | |_ ___| |__  _ _ __| |_       * 
 *      | |/ _ \| __| | __/ __| '_ \| | '__| __|      *
 *      | | (_) | |_  | |_\__ \ | | | | |  | |_       *
 *      |_|\___/ \__|  \__|___/_| |_|_|_|   \__|      *
 ******************************************************                                                  
 ******************************************************
 **Created 28 Jan 2018*********************************
 **By Guilherme Uezima*********************************
 ******************************************************
 ======================================================
 *         L.E.D tshirt controlled by a Wemos         *
 *                    D1 mini board                   *
 ======================================================*/

#include <ESP8266WiFi.h>  //WIFI Connection
#include <ArduinoJson.h>  //JSON Communication with server
#include <PubSubClient.h> //MQTT Communication

/* CONST BLOCK ======= */
const char* SSID = "* WIFI NETWORK *";
const char* WIFI_PASSWORD = "* WIFI PASSWORD *";
const int   LED_PIN = 15;

const char* MQTT_SERVER = "* MQTT HOST URL *";
const int   MQTT_PORT   = 0000; //* MQTT HOST PORT *
const char* MQTT_USER   = "* MQTT HOST USER *";
const char* MQTT_PASS   = "* MQTT HOST PASSWORD *";
const char* MQTT_TOPIC  = "***";

/* VARS BLOCK ======= */
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

/* INFO LOG ======= */
void infoLog(String msg){
  Serial.println("[INFO] " + msg);
}

/* WIFI BLOCK ======== */
void configureWiFi() {
  infoLog("Connection to network");
  Serial.println(SSID);

  if(WiFi.status() == WL_CONNECTED)
    return;

  WiFi.begin(SSID, WIFI_PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print("|");
  }
  Serial.println("");
  infoLog("Connected in network");

  digitalWrite(LED_PIN, HIGH);
  delay(2000);
  digitalWrite(LED_PIN, LOW);
}

void sendJSONMQTT(int jsonBufferSize, JsonObject& JSONencoder, char* topic) {
  char JSONmessageBuffer[jsonBufferSize];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  if(mqttClient.publish(topic, JSONmessageBuffer)){
    infoLog("Success sending message");
  }else{
    infoLog("Error sending message");
    infoLog("RESET");
    setup();
  }
}

void sendJSON() {
  StaticJsonBuffer<500> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();

  JSONencoder["TEST"] = "CON"; 

  sendJSONMQTT(500, JSONencoder, "iot-t-shirt/led/test");
}

/* CALLBACK MQTT BLOCK ======== */
void callback(char* topic, byte* payload, unsigned int length) {
  infoLog("==========================================");
  infoLog("Message arrived from MQTT Server - Topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for(int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
  }

  digitalWrite(LED_PIN, HIGH);
  delay(2000);
  digitalWrite(LED_PIN, LOW);

  Serial.println();
  infoLog("==========================================");
}

/* PUBSUB MQTT BLOCK ======== */
void configureMQTT() {
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(callback);

  while(!mqttClient.connected()){
    if(mqttClient.connect("WEMOSD1Client", MQTT_USER, MQTT_PASS)){
      infoLog("Connected in MQTT server");
       digitalWrite(LED_PIN, HIGH);
       delay(2000);
       digitalWrite(LED_PIN, LOW);
    }else{
      infoLog("Connection to MQTT server failed");
      Serial.println(mqttClient.state());
    }
    delay(2000);
    Serial.print("|");
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  infoLog("Establishing WiFi connection");
  configureWiFi();
  configureMQTT();
  mqttClient.subscribe("iot-t-shirt/led");

  infoLog("Configuration completed!");
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  mqttClient.loop();
  delay(2000);
  Serial.println("Testando conexao"); 
  sendJSON();
}
