#include <utils.h>
#include <Arduino.h>
#include <Arduino_JSON.h>

void JSON_decode(String payload)
{
  JSONVar myObject = JSON.parse(payload);
  
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
  }
}