#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <semilimes.h>
#include <Arduino_JSON.h>

#include "secret.h" // import wifi credentials, token and channel ID
#define WIFI_CONN_TIMEOUT 10 //Sec
#define BUFF_SIZE 10

using namespace websockets;
semilimes semilimes;

WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message)
{
  Serial.println("Got Message: ");

  semilimes_message_t new_message;
  new_message = JSON_decode(message.data(), false);
  if (new_message.bodyType != "Event" && new_message.type != "Server") 
  {
    Serial.println(message.data());
  }
}

void onEventsCallback(WebsocketsEvent event, String data)
{
  if (event == WebsocketsEvent::ConnectionOpened)
  {
    Serial.println("Connnection Opened");
  }
  else if (event == WebsocketsEvent::ConnectionClosed)
  {
    Serial.println("Connnection Closed");
  }
  else if (event == WebsocketsEvent::GotPing)
  {
    Serial.println("Got a Ping!");
  }
  else if (event == WebsocketsEvent::GotPong)
  {
    Serial.println("Got a Pong!");
  }
}

boolean init_wifi()
{
  // Connect to wifi
  Serial.print("Connecting to ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);

  int time = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
    time += 1;
    if (time > WIFI_CONN_TIMEOUT)
    {
      Serial.println("Connection timeout");
      return false;
    }
  }

  return true;
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Hello World");

  while (!init_wifi())
    ;

  // run callback when messages are received
  client.onMessage(onMessageCallback);

  // run callback when events are occuring
  //client.onEvent(onEventsCallback);

  // Connect to semilimes server
  client.connect(semilimes_wss_server);

  client.send(semilimes.SendTxtMsg(myToken, ChannelId, semilimes_channel, "ESP8266 started!"));

  //Message test
  String body = "Selection";
  String OptionTexts[4] = {"Blue", "Red", "Orange", "Yellow"};
  String OptionValues[4] = {"A", "B", "C", "D"};

  client.send(semilimes.SendSelectOpt(myToken, ChannelId, semilimes_channel, body, OptionTexts, OptionValues, sizeof(OptionTexts) / sizeof(*OptionTexts)));
}

void loop()
{
  client.poll();

  delay(10);
}