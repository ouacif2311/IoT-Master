#include "ThingSpeak.h"
#include <WiFiNINA.h>
//#include "secrets.h"
char ssid[]  = "AndroidAP041f" ; // your network SSID (name)
char pass[]  = "lckt0603" ; // your network password
char keyIndex = 0; // your network key Index number (needed only for WEP)
WiFiClient client;
unsigned long myChannelNumber = 1955494;
const char * myWriteAPIKey = "ONB4QEWWHHNB2VHM";
int channelField = 1;
int SensorPin = 0;
float adcValue;
float voltageValue;
float temperatureValue = 0;
int samplingTime = 20000; // Wait 20 seconds between each hannel update
void setup() {
Serial.begin(9600); // Initialize serial
if (WiFi.status() == WL_NO_MODULE) {
Serial.println("Communication with WiFi module failed!");
// don't continue
while (true);
}
String fv = WiFi.firmwareVersion();
if (fv != "1.0.0") {
Serial.println("Please upgrade the firmware");
}
ThingSpeak.begin(client); //Initialize ThingSpeak
}
void loop() {
// Connect or reconnect to WiFi
if(WiFi.status() != WL_CONNECTED){
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  while(WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
    Serial.print(".");
  delay(5000);
  }
Serial.println("\nConnected.");
}
adcValue = analogRead(A0); // Get Data from Temperature Sensor
float mv = ( adcValue/1024.0)*5000;
float cel = mv/10;
Serial.println(cel);
// Write to ThingSpeak
int x = ThingSpeak.writeField(myChannelNumber, channelField, cel, myWriteAPIKey);
if(x == 200){
  Serial.println("Channel update successful.");
}
else{
  Serial.println("Problem updating channel. HTTP error code " + String(x));
}
  delay(20000); // Wait 20 seconds to update the channel again
}
