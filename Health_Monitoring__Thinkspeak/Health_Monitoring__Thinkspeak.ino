#include <ESP8266WiFi.h>
 
String apiKey = "H8ZW4X7KVPQX1I02";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "Innovation Lab";     //  wifi ssid 
const char *pass =  "be_innovative_#";    // wifi password
const char* server = "api.thingspeak.com";

WiFiClient client;
 


int PulseSensorPurplePin = 0;        
int LED13 = 13;                    
int Signal;               
int Threshold = 550;            


void setup() {
  
    pinMode(LED13,OUTPUT);        
    Serial.begin(9600); 
    delay(10); 

    Serial.print("Connecting to: ");
    Serial.println(ssid);

      WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}

void loop() {

  

   float t = analogRead(PulseSensorPurplePin); 
//    Serial.println(Signal);                   


    if (isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   // establishing the connection with thingspeak server
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Heart rate signal: ");
                             Serial.print(t);
                            
                             Serial.println(" Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  
  delay(500);  // dealy half second and regenerate the temperature and send it to the thingspeak


}
