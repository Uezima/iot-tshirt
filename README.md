# iot-tshirt
T-shirt connected on the internet with leds that light up when someone likes a Facebook page

![alt tag](https://i.imgur.com/IwlVf1cl.jpg)

## Setup
1. Clone the project
2. Change WIFI credentials (Client side - Wemos D1 Mini)
3. Change MQTT credentials (Client side - Wemos D1 Mini)
4. Change Facebook Client ID (Server side)
5. Run the server and access /tshirt/start URL

## Wifi config 
Client/Tshirt.ino
```
const char* SSID = "* WIFI NETWORK *";
const char* WIFI_PASSWORD = "* WIFI PASSWORD *";
```

## MQTT Server config
Client/Tshirt.ino
```
const char* MQTT_SERVER = "* MQTT HOST URL *";
const int   MQTT_PORT   = 0000; //* MQTT HOST PORT *
const char* MQTT_USER   = "* MQTT HOST USER *";
const char* MQTT_PASS   = "* MQTT HOST PASSWORD *";
const char* MQTT_TOPIC  = "***";
```

## Facebook Client ID config
Server/webservice/FacebookCom.js

Generate your Facebook Client ID on the [Facebook Graph API Platform](https://developers.facebook.com/tools/explorer/)

```
var facebookClient = process.env.FACEBOOK_CLIENT_ID || "* FACEBOOK TOKEN CLIENT_ID *";  
var facebookAPIEndpoint = 'https://graph.facebook.com/v3.1';
var facebookPageID = '* FACEBOOK PAGE ID *';
```