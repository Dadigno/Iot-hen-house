/*
  Secured Esp8266 Websockets Client

  This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server (using WSS)
        3. Sends the websockets server a message ("Hello Server")
        4. Sends the websocket server a "ping"
        5. Prints all incoming messages while the connection is open

    NOTE:
    The sketch dosen't check or indicate about errors while connecting to 
    WiFi or to the websockets server. For full example you might want 
    to try the example named "Esp8266-Client" (And use the ssl methods).

  Hardware:
        For this sketch you only need an ESP8266 board.

  Created 15/02/2019
  By Gil Maimon
  https://github.com/gilmaimon/ArduinoWebsockets

*/
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>
#include <semilimes.h>
#include <semilimes_device.h>
#include <Arduino_JSON.h>

const char* ssid = "....."; //Enter SSID
const char* password = "......"; //Enter Password
String AuthToken = ".....";
String ChannelId = "...."; //the channel ID
 
  //1) Get the certificate from your site (443=HTTPS port)
      //openssl s_client -connect cloud.semilimes.net:443
  //2) copy the certificate (from "-----BEGIN CERTIFICATE-----" to "-----END CERTIFICATE-----") and paste into a file (cert.perm).
  //3) Then use the cert.perm to generate SHA1 fingerprint
      //openssl x509 -noout -in ./cert.perm -fingerprint -sha1

// Semilimes Server SHA1 key
//const char echo_org_ssl_fingerprint[] PROGMEM = "18 A1 01 25 81 A2 62 FC 7D 75 BC 3C E3 3A 29 DD B9 30 74 4F";

using namespace websockets;

WebsocketsClient client;
semilimes semilimes;

#define LED D0

class digital : public semilimes_device
{
  public:
  virtual int SetOutSpecific(int output_n,int value)
  {
    dev_outputs[output_n]=value;
    if (output_n==1) 
    {
      if(value) digitalWrite(LED, LOW);
      else digitalWrite(LED, HIGH);
    }
    Serial.println("name: "+dev_name+" id:"+dev_id+" group:"+dev_group+" subg:"+dev_subgroup+" OutN:"+output_n+" value:"+dev_outputs[output_n]);
    return value;
  }
  virtual int GetInSpecific(int input_n)
  {   
    if (input_n==1) 
    {
      dev_inputs[input_n] = digitalRead(LED);
    }
    Serial.println("name: "+dev_name+" id:"+dev_id+" group:"+dev_group+" subg:"+dev_subgroup+" InN:"+input_n+" value:"+dev_inputs[input_n]);
    return dev_inputs[input_n];
  }
};

digital Lamp1;

void JSON_decode(String payload)
{
  JSONVar myObject = JSON.parse(payload);
  /*
  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }
  
  if (myObject.hasOwnProperty("ConversationID")) {
    Serial.print("myObject[\"ConversationID\"] = ");
    Serial.println(myObject["ConversationID"]);
  }
  if (myObject.hasOwnProperty("SenderID")) {
    Serial.print("myObject[\"SenderID\"] = ");
    Serial.println(myObject["SenderID"]);
  }  
  if (myObject.hasOwnProperty("ClientID")) {
    Serial.print("myObject[\"ClientID\"] = ");
    Serial.println(myObject["ClientID"]);
  }
  if (myObject.hasOwnProperty("MessageID")) {
    Serial.print("myObject[\"MessageID\"] = ");
    Serial.println(myObject["MessageID"]);
  }
  if (myObject.hasOwnProperty("Body")) {
    Serial.print("myObject[\"Body\"] = ");
    Serial.println(myObject["Body"]);
  }*/
  if (myObject.hasOwnProperty("ConversationID") && (JSON.stringify(myObject["ConversationID"])=='"'+ChannelId+'"')) {
    String msg = JSON.stringify(myObject["Body"]);
    //remove the quotation marks
    msg.remove(0,1);
    msg.remove(msg.length()-1,1);
    Serial.println(msg);
    client.send(Lamp1.parse_msg(msg,ChannelId));
  }
}

void onMessageCallback(WebsocketsMessage message) {
    JSON_decode(message.data());
    //Serial.print("Got Message: ");
    //Serial.println(message.data());
}

void onEventsCallback(WebsocketsEvent event, String data) {
    if(event == WebsocketsEvent::ConnectionOpened) {
        Serial.println("Connnection Opened");
    } else if(event == WebsocketsEvent::ConnectionClosed) {
        Serial.println("Connnection Closed");
    } else if(event == WebsocketsEvent::GotPing) {
        Serial.println("Got a Ping!");
    } else if(event == WebsocketsEvent::GotPong) {
        Serial.println("Got a Pong!");
    }
}
void setup() {
 
    pinMode(LED, OUTPUT);    // LED pin as output.
    
    Serial.begin(115200);
    // Connect to wifi
    WiFi.begin(ssid, password);

    // Wait some time to connect to wifi
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(1000);
    }

    // run callback when messages are received
    client.onMessage(onMessageCallback);
    
    // run callback when events are occuring
    //client.onEvent(onEventsCallback);

    // Before connecting, set the ssl fingerprint of the server
    //client.setFingerprint(echo_org_ssl_fingerprint);

    // Connect to server
    client.connect(semilimes_wss_server);
    
    client.send(semilimes.SendTxtMsg(AuthToken, ChannelId, semilimes_channel, "ESP8266 started!"));
    
    Lamp1.init(AuthToken, "Simon Lamp",1,1,1,1,1);
}

void loop() {
    client.poll();
}
