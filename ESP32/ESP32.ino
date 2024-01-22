#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "hoeresnellewifi";
const char* password = "xdxdxdxd";

String snapPath = "127.0.0.1/api/Posters/Snap";

String posterId = "fd38ef73-eba5-4f87-a26e-e6a22147e4da";

void setup() {
  Serial.begin(115200);

  // Connect to wifi
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());  

  HTTPClient http;

  // Send request 
  http.begin("http://127.0.0.1:5000/api/Posters/Test");
  //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.GET();
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  Serial.println(http.getString());
  http.end();
}

void loop() {

}