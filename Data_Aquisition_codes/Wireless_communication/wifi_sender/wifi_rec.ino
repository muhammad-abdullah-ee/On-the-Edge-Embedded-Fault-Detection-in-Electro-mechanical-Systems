//#include <ESP8266wifi.h>

#include "ESPAsyncWebServer.h"


// Set your access point network credentials
const char* ssid = "ESP32-sender";
const char* password = "12345678";
const unsigned int MAX_MESSAGE_LENGTH = 64;
static char message[MAX_MESSAGE_LENGTH];
float x  = Serial.read();
AsyncWebServer server(80);
String readTemp() {
  return(message);
   
}

void setup()
{
  Serial.begin(115200);
 /* Serial.println();

  WiFi.begin("128home", "abdullah");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("not connected");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());*/

  WiFi.softAP(ssid, password);
  while (!Serial) {
; // wait for serial port to connect. Needed for native USB port only
}
server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){   
  request->send_P(200, "text/plain", readTemp().c_str());

});
  server.begin();
 

 
}

void loop() {
  
while (Serial.available() > 0)
 {
   //Create a place to hold the incoming message
   
   static unsigned int message_pos = 0;

   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();

   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
   {
     //Add the incoming byte to our message
     message[message_pos] = inByte;
     message_pos++;
   }
   //Full message received...
   else
   {
     //Add null character to string
     message[message_pos] = '\0';

     //Print the message (or do other things)
     Serial.println(message);

     //Reset for the next message
     message_pos = 0;
   }
 }
}
