#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "";
const char* password = "";

String snapPath = "http://192.168.0.161:5000/api/Posters/Snap";

String posterId = "fd38ef73-eba5-4f87-a26e-e6a22147e4da";

String urlEncode(const String &value) {
  String encodedValue = "";
  char c;
  char code0;
  char code1;

  for (unsigned int i = 0; i < value.length(); i++) {
    c = value.charAt(i);

    if (c == ' ') {
      encodedValue += '+';
    } else if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      encodedValue += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      encodedValue += '%';
      encodedValue += code0;
      encodedValue += code1;
    }
  }

  return encodedValue;
}

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
  http.begin("http://192.168.0.161:5000/api/Posters/Create");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  //Example
  //String formData = "name=" + urlEncode(name) + "&" + "date=" + urlEncode(date)
  String formData = "name=" + urlEncode("test=top");

  int httpResponseCode = http.POST(formData);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  Serial.println(http.getString());
  http.end();
}

void loop() {

}