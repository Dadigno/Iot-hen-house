#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <semilimes.h>
#include "secret.h" // import wifi credentials, token and channel ID
#include <utils.h>

#define WIFI_CONN_TIMEOUT 10 //Sec

using namespace websockets;
semilimes semilimes;

WebsocketsClient client;

const char *websockets_connection_string = semilimes_wss_server;

void onMessageCallback(WebsocketsMessage message)
{
  Serial.print("Got Message: ");
  Serial.println(message.data());
  JSON_decode(message.data());
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
  Serial.println(ssid);

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

  // run callback when messages are received
  client.onMessage(onMessageCallback);

  // run callback when events are occuring
  client.onEvent(onEventsCallback);
  return true;
}

void setup()
{
  Serial.begin(115200);

  while (!init_wifi())
    ;

  // Connect to semilimes server
  client.connect(websockets_connection_string);

  String Body = "This message from ESP32 using the wss Semilimes libs";
  client.send(semilimes.SendTextMessage(myToken, ChannelId, Body));
}

void loop()
{
  client.poll();
}