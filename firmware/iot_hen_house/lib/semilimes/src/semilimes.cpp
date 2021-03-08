#include "semilimes.h"

semilimes_message_t JSON_decode(String payload, bool verbose)
{
	JSONVar myObject = JSON.parse(payload);
	semilimes_message_t new_message;
	// JSON.typeof(jsonVar) can be used to get the type of the var
	if (JSON.typeof(myObject) == "undefined")
	{
		Serial.println("Parsing input failed!");
	}
	else
	{
		
		new_message.conversation = myObject["ConversationID"];
		new_message.sender_id = myObject["SenderID"];
		new_message.client_id = myObject["ClientID"];
		new_message.message_id = myObject["MessageID"];
		new_message.body = myObject["Body"];

		if (verbose)
		{
			if (myObject.hasOwnProperty("ConversationID"))
			{
				Serial.print("myObject[\"ConversationID\"] = ");
				Serial.println(myObject["ConversationID"]);
			}
			if (myObject.hasOwnProperty("SenderID"))
			{
				Serial.print("myObject[\"SenderID\"] = ");
				Serial.println(myObject["SenderID"]);
			}
			if (myObject.hasOwnProperty("ClientID"))
			{
				Serial.print("myObject[\"ClientID\"] = ");
				Serial.println(myObject["ClientID"]);
			}
			if (myObject.hasOwnProperty("MessageID"))
			{
				Serial.print("myObject[\"MessageID\"] = ");
				Serial.println(myObject["MessageID"]);
			}
			if (myObject.hasOwnProperty("Body"))
			{
				Serial.print("myObject[\"Body\"] = ");
				Serial.println(myObject["Body"]);
			}
		}
	}
	return new_message;
}




semilimes::semilimes(){
  
}

String semilimes::SendTextMessage(String AuthToken, String ReceiverID, String Body)
{
  String TypeID = "590E4E6C-2C5D-47E8-8F38-311D5A299EE7";
  String wsmsg = "{\"AuthToken\": \"" + AuthToken + "\", ";
  wsmsg += "\"Type\": \"chat\", ";
  wsmsg += "\"TypeID\": \"" + TypeID + "\", ";
  wsmsg += "\"ReceiverID\": \"" + ReceiverID + "\", ";
  wsmsg += "\"Body\": \"" + Body + "\"}";

  return wsmsg;
}

String semilimes::SendSelectOptions(String AuthToken, String ReceiverID, String Body, String* OptionsText, String* OptionsValue, int OptionsNumber)
{
  int i;
  String TypeID = "4DB40F80-4C25-454B-BDB4-330A05285D71";
  String wsmsg = "{\"AuthToken\": \"" + AuthToken + "\", ";
  wsmsg += "\"Type\": \"chat\", ";
  wsmsg += "\"TypeID\": \"" + TypeID + "\", ";
  wsmsg += "\"ReceiverID\": \"" + ReceiverID + "\", ";
  wsmsg += "\"Body\": \"" + Body + "\", ";
  wsmsg += "\"Layout\": \"flexible\", ";
  wsmsg += "\"Options\": [ ";
  for(i=0;i<OptionsNumber-1;i++)
  {
    wsmsg += "{\"Text\": \"" + *(OptionsText+i) + "\", \"Value\": \"" + *(OptionsValue+i) + "\"},";
  }
  wsmsg += "{\"Text\": \"" + *(OptionsText+i) + "\", \"Value\": \"" + *(OptionsValue+i) + "\"}],";
  wsmsg += "\"Data\": {}}";

  return wsmsg;
}

String semilimes::SendLocation(String AuthToken, String ReceiverID, String Body, String latitude, String longitude)
{
  String TypeID = "4BDD5F50-DC68-11EA-9FCE-5302A705E738";
  String wsmsg = "{\"AuthToken\": \"" + AuthToken + "\", ";
  wsmsg += "\"Type\": \"chat\", ";
  wsmsg += "\"TypeID\": \"" + TypeID + "\", ";
  wsmsg += "\"ReceiverID\": \"" + ReceiverID + "\", ";
  wsmsg += "\"Location\": {\"latitude\":" + latitude + ",\"longitude\":" + longitude + "},";
  wsmsg += "\"Body\": \"" + Body + "\"} ";

  return wsmsg;
}

String semilimes::SendHTML(String AuthToken, String ReceiverID, String Body)
{
  String TypeID = "38199F47-504C-4C73-97E5-8076C8CFAA21";
  String wsmsg = "{\"AuthToken\": \"" + AuthToken + "\", ";
  wsmsg += "\"Type\": \"chat\", ";
  wsmsg += "\"TypeID\": \"" + TypeID + "\", ";
  wsmsg += "\"ReceiverID\": \"" + ReceiverID + "\", ";
  wsmsg += "\"Body\": \"" + Body + "\"} ";

  return wsmsg;
}

String semilimes::PickDate(String AuthToken, String ReceiverID, String Body)
{
  String TypeID = "242B5A3B-C1AF-4663-BD97-E296E3DB4D2F";
  String wsmsg = "{\"AuthToken\": \"" + AuthToken + "\", ";
  wsmsg += "\"Type\": \"chat\", ";
  wsmsg += "\"TypeID\": \"" + TypeID + "\", ";
  wsmsg += "\"ReceiverID\": \"" + ReceiverID + "\", ";
  wsmsg += "\"Body\": \"" + Body + "\", ";
  wsmsg += "\"Data\": {}}";

  return wsmsg;
}

String semilimes::PickTime(String AuthToken, String ReceiverID, String Body)
{
  String TypeID = "F489C072-2C8B-4BC6-AD75-946D3CA721B7";
  String wsmsg = "{\"AuthToken\": \"" + AuthToken + "\", ";
  wsmsg += "\"Type\": \"chat\", ";
  wsmsg += "\"TypeID\": \"" + TypeID + "\", ";
  wsmsg += "\"ReceiverID\": \"" + ReceiverID + "\", ";
  wsmsg += "\"Body\": \"" + Body + "\", ";
  wsmsg += "\"Data\": {}}";

  return wsmsg;
}

String semilimes::PickLocation(String AuthToken, String ReceiverID, String Body)
{
  String TypeID = "20A0CE4B-A236-4E96-9629-45A3AF5F62EA";
  String wsmsg = "{\"AuthToken\": \"" + AuthToken + "\", ";
  wsmsg += "\"Type\": \"chat\", ";
  wsmsg += "\"TypeID\": \"" + TypeID + "\", ";
  wsmsg += "\"ReceiverID\": \"" + ReceiverID + "\", ";
  wsmsg += "\"Body\": \"" + Body + "\", ";
  wsmsg += "\"Data\": {}}";

  return wsmsg;
}

String semilimes::SendJSON(String AuthToken, String ReceiverID, String TypeID, String Body)
{
  String wsmsg = "{\"AuthToken\": \"" + AuthToken + "\", ";
  wsmsg += "\"Type\": \"chat\", ";
  wsmsg += "\"TypeID\": \"" + TypeID + "\", ";
  wsmsg += "\"ReceiverID\": \"" + ReceiverID + "\", ";
  wsmsg += "\"Body\": \"" + Body + "\", ";
  wsmsg += "\"Data\": {}}";

  return wsmsg;
}

String semilimes::SendRestfulMessageRequest(String token, String ReceiverId, String msg)
{
  // Data to send with HTTP POST
  String restfulMsg = "{ ";
  restfulMsg += "\"Token\": \"" + token + "\", ";
  restfulMsg += "\"Message\": { ";
  restfulMsg += "\"Type\": \"chat\", ";
  restfulMsg += "\"ReceiverID\": \"" + ReceiverId + "\", ";
  restfulMsg += "\"Body\": \"" + msg + "\"}";
  restfulMsg += "}}";        
    
  return restfulMsg;
}