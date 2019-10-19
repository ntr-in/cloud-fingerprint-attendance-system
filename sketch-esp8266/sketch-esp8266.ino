#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

char ssid[] = "bakul";   // your network SSID (name) 
char pass[] = "bakulbakul";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 877894;
const char * myWriteAPIKey = "VU0348WOREPGPX9A";

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
    ThingSpeak.setField(1, Serial.readStringUntil('\n'));
    ThingSpeak.setField(2, Serial.readStringUntil('\n'));
    ThingSpeak.setField(3, Serial.readStringUntil('\n'));
    ThingSpeak.setField(4, Serial.readStringUntil('\n'));
    
    // write to the ThingSpeak channel
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    
  }
  
  delay(20000); // Wait 20 seconds to update the channel again
}
