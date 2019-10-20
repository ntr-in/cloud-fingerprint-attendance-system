#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

char ssid[] = "bakul";   // your network SSID (name) 
char pass[] = "bakulbakul";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 889971;// 877894;
const char * myWriteAPIKey = "8U00D081JDQL3H77"; //"VU0348WOREPGPX9A";

void setup() {
  Serial.begin(9600);  // Initialize serial

  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  if (Serial.available()) {

    // set the fields with the values
    String name=Serial.readStringUntil(' ');
    String date=Serial.readStringUntil(' ');
    String t=Serial.readStringUntil(' ');
    ThingSpeak.setField(1, name);
    ThingSpeak.setField(2, date);
    ThingSpeak.setField(3, t);
    
    // write to the ThingSpeak channel
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    HTTPClient http;
    http.begin("https://maker.ifttt.com/trigger/student_entered/with/key/eMAeXhzPzrp6FuNewWHNaJSYsGOTdW4DBAJPbcyoF50?value1=\""+name+"&value2=\""+date+"&value3=\""+t);
    http.GET();
    http.end();
    
    
  }
  
  delay(20000); // Wait 20 seconds to update the channel again
}
