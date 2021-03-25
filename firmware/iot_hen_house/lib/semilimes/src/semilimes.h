#ifndef semilimes_h
#define semilimes_h

#include <Arduino.h>
#include <Arduino_JSON.h>
#include <circular_buffer.h>


#define semilimes_wss_server "wss://cloud.semilimes.net/CloudServer/wsclient"
//#define semilimes_wss_server "wss://dev.semilimes.net/CloudServer/wsclient"
//#define SendRestfulMessageRequest_api "https://cloud.semilimes.net/CloudServer/api/3A01CE9E-F850-4049-AD45-DA372E44B89B"
#define SendRestfulMessageRequest_api "https://dev.semilimes.net/CloudServer/api/3A01CE9E-F850-4049-AD45-DA372E44B89B"

#define semilimes_user 0
#define semilimes_channel 1


typedef struct
{
	JSONVar conversation;
	JSONVar sender_id;
	JSONVar client_id;
	JSONVar message_id;
	JSONVar body;
	JSONVar bodyType;
	JSONVar type;
} semilimes_message_t;

semilimes_message_t JSON_decode(String payload, bool verbose);


class semilimes
{
	public:
		String SendTxtMsg(String AuthToken, String ReceiverID, int dest_type, String Body);
		String SendSelectOpt(String AuthToken, String ReceiverID, int dest_type, String Body, String* OptionTexts, String* OptionValues, int OptionsNumber);
		String SendLocation(String AuthToken, String ReceiverID, int dest_type, String Body, String latitude, String longitude);
		String SendHTML(String AuthToken, String ReceiverID, int dest_type, String Body);
		String ReceiveDate(String AuthToken, String ReceiverID, int dest_type, String Body);
		String ReceiveTime(String AuthToken, String ReceiverID, int dest_type, String Body);
		String ReceiveLocation(String AuthToken, String ReceiverID, int dest_type, String Body);
		String SendJSON(String AuthToken, String ReceiverID, int dest_type, String TypeId, String Body);
		String SendRestMsgReq(String token, String ReceiverID, int dest_type, String msg);
};

#endif
