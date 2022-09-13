#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"
#include <ESP8266WiFi.h>      // Replace with WiFi.h for ESP32
#include <ESP8266WebServer.h> // Replace with WebServer.h for ESP32
#include <AutoConnect.h>

ESP8266WebServer Server; // Replace with WebServer for ESP32
AutoConnect Portal(Server);
AutoConnectConfig Config;

const int RELAY_1 = 16;
const int RELAY_2 = 5;
const int RELAY_3 = 4;
const int RELAY_4 = 14;
const int LED = 2;
unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;
unsigned long LedsSequence[4]; //[x] is the number of leds array

// const char *subscribeTopic = new char[strlen(THINGNAME) + strlen("aws/things//tock/update") + 1];
// const char *t = strcpy((char *)subscribeTopic, THINGNAME);
// const char *ts = strcat("aws/things/",(char *)subscribeTopic, "/command");

// const char *publishTopic = new char[strlen(THINGNAME) + strlen("/return") + 1];
// const char *tss = strcpy((char *)publishTopic, THINGNAME);
// const char *tsss = strcat((char *)publishTopic, "/return");

#define AWS_IOT_SUBSCRIBE_TOPIC "tock/things/pool-green2b/update" // "pool-green2b/command"
#define AWS_IOT_PUBLISH_TOPIC "tock/things/pool-green2b/update/return"     // "pool-green2b/return"

WiFiClientSecure net;

BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

PubSubClient client(net);

time_t now;
time_t nowish = 1510592825;

void connectAWS();
void publishMessage(String msg);

void blinkLed(int led, int interval, int array, int repeat)
{
  if ((int)((long)millis() - LedsSequence[array]) >= interval)
  {
    LedsSequence[array] = millis(); // stores the millis value in the selected array
    digitalWrite(LED, !digitalRead(LED)); // changes led state
  }
}

void rootPage()
{
  char content[] = "TOCK Tecnologia LTDA";
  Server.send(200, "text/plain", content);
}
void espReset()
{
  Serial.println("restarting ... ");
  delay(5000);
  ESP.resetFreeContStack();
}
void autoconnect_setup()
{
  Serial.println("autoconnect_setup");
  digitalWrite(LED, LOW);

  Config.autoReconnect = true;  // Attempt automatic reconnection.
  // Config.reconnectInterval = 6; // Seek interval time is 180[s].
  // Config.autoReset = true;
  Config.apid = "TOCK CONFIG";
  Config.psk = "12345678";
  // Config.portalTimeout = 180;
  // Config.beginTimeout = 30;
  Portal.config(Config);

  Server.on("/", rootPage);
  if (Portal.begin())
  {
    Serial.println("\nWiFi connected: " + WiFi.SSID());
    Serial.println("Local IP: " + WiFi.localIP().toString());
    connectAWS();
  }
}
void autoconnect_loop()
{
  Portal.handleClient();
}

void pushRelay(int id)
{
  digitalWrite(id, LOW);
  delay(500);
  digitalWrite(id, HIGH);
}

void NTPConnect(void)
{
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, 0 * 3600, "pool.ntp.org", "time.nist.gov");
  now = time(nullptr);
  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println("done!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}

void messageReceived(char *topic, byte *payload, unsigned int length)
{
  StaticJsonDocument<400> doc;
  deserializeJson(doc, payload);
  Serial.println((String)doc["state"]);
  //print received message
  Serial.print("Received [");
  Serial.print(topic);
  Serial.println("]: ");
  for (int i = 0; i < length; i++){Serial.print((char)payload[i]);}

  if(doc["state"]["desired"]["pin1"] == "x"){pushRelay(RELAY_1);}
  if(doc["state"]["desired"]["pin2"] == "x"){pushRelay(RELAY_2);}
  if(doc["state"]["desired"]["pin3"] == "x"){pushRelay(RELAY_3);}
  if(doc["state"]["desired"]["pin4"] == "x"){pushRelay(RELAY_4);}

  JsonObject crew = doc["state"];
  doc["state"]["reported"] = doc["state"]["desired"];
  crew.remove("desired");

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish((const char *)AWS_IOT_PUBLISH_TOPIC, jsonBuffer);

  // publishMessage(doc);
  
  
  // int buttonId = (int)doc["desired"];
  //if (buttonId < 5 && buttonId > 0)
  // {
  //   publishMessage("button-id-" + (String)buttonId + "-success");
  // }
  // switch (buttonId)
  // {
  // case 1:
  //   pushRelay(RELAY_1);
  //   break;
  // case 2:
  //   pushRelay(RELAY_2);
  //   break;
  // case 3:
  //   pushRelay(RELAY_3);
  //   break;
  // case 4:
  //   pushRelay(RELAY_4);
  //   break;

  // default:
  //   publishMessage("button-id-" + (String)buttonId + "-fail");
  //   break;
  // }
}

void connectAWS()
{
  digitalWrite(LED, LOW); //changes led state
  delay(3000);
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));

  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   blinkLed(LED, 50, 0);
  //   Serial.print(".");
  //   delay(1000);
  // }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WiFi not connected!");
    // autoconnect_setup();
    autoconnect_loop();
    return;
    // while (WiFi.status() != WL_CONNECTED)
    // {
    //   // reset.attach(1, espReset); // pisca se enquanto tenta se conectar ao wifi
    //   autoconnect_setup();
    // }
  }
  else if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected: " + WiFi.localIP().toString());
    // reset.detach();
  }

  NTPConnect();

  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);

  client.setServer(MQTT_HOST, 8883);
  client.setCallback(messageReceived);
  client.setSocketTimeout(30);

  Serial.println("Connecting to AWS IOT");

  while (!client.connect(THINGNAME))
  {
    blinkLed(LED, 100, 0, 3);
    Serial.print(".");
    delay(1000);
  }
  if (!client.connected())
  {
    Serial.println("AWS IoT Timeout!");
    return;
  }
  // Subscribe to a topic
  client.subscribe((const char *)AWS_IOT_SUBSCRIBE_TOPIC);

  // reset.detach();
  Serial.println("AWS IoT Connected!");
}

void publishMessage(StaticJsonDocument<400> doc)
{
  // StaticJsonDocument<200> doc;
  // doc["reported"] = msg;
  // char jsonBuffer[512];
  // serializeJson(doc, jsonBuffer); // print to client
  // Serial.println("publishing message ");
  // Serial.print("[");
  // Serial.print(AWS_IOT_PUBLISH_TOPIC);
  // Serial.print("]: ");
  // Serial.println(jsonBuffer);

  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client
  client.publish((const char *)AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(RELAY_1, OUTPUT);
  digitalWrite(RELAY_1, HIGH);
  pinMode(RELAY_2, OUTPUT);
  digitalWrite(RELAY_2, HIGH);
  pinMode(RELAY_3, OUTPUT);
  digitalWrite(RELAY_3, HIGH);
  pinMode(RELAY_4, OUTPUT);
  digitalWrite(RELAY_4, HIGH);
  Serial.begin(115200);
  autoconnect_setup();
  // connectAWS();
}

void loop()
{
  autoconnect_loop();
  if (!WiFi.isConnected())
  {
    blinkLed(LED, 100, 0, 1);
  }
  else
  {
    blinkLed(LED, 1000, 0, 4);
    if (!client.connected())
    {
      Serial.println("Client not connected! Connecting...");
      connectAWS();
    }
    client.loop();
  }

  // if (!client.connected())
  // {
  //   blinkLed(LED, 100, 0);
  //   connectAWS();
  // }
  // else
  // {
  //   blinkLed(LED, 1000, 0);
  //   client.loop();
  // }
}