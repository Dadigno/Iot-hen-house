#include <Arduino.h>
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <semilimes.h>
#include "secret.h" // import wifi credentials, token and channel ID
#include <circular_buffer.h>
#include <Arduino_JSON.h>

#define WIFI_CONN_TIMEOUT 10 //Sec

using namespace websockets;
semilimes semilimes;

WebsocketsClient client;

const char *websockets_connection_string = semilimes_wss_server;

circular_buffer<semilimes_message_t> msg_buf(10);

void onMessageCallback(WebsocketsMessage message)
{
  Serial.print("Got Message: ");
  Serial.println(message.data());

  //semilimes_message_t new_message;
  //new_message = JSON_decode(message.data(), false);
  //msg_buf.put(new_message);
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
  client.onEvent(onEventsCallback);

  // Connect to semilimes server
  client.connect(websockets_connection_string);

  String Body = "This message from ESP32 using the wss Semilimes libs";
  client.send(semilimes.SendTextMessage(myToken, ChannelId, Body));

}

void loop()
{
  client.poll();
  // Serial.println("Sending message");
  //Check message buffer
  /*if (!msg_buf.empty())
  {
    //buffer not empty
    //TODO decode messages
    semilimes_message_t m = msg_buf.get();
    String body = JSON.stringify(m.body);
    
  }*/
  // client.send(semilimes.SendTextMessage(myToken, ChannelId, "Hello, It's me"));
  // delay(1000);
}