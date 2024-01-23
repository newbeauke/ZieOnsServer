#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <LittleFS.h>
#include "esp_camera.h"

// Pin definition for CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27
#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22
#define STACK_SIZE 65536

const char *ssid = "WijtsB";
const char *password = "C0cac0la";

String snapPath = "http://192.168.0.161:5000/api/Posters/Snap";
String posterId = "fd38ef73-eba5-4f87-a26e-e6a22147e4da";

const int captureInterval = 10000;  // Capture picture every 10 seconds

void setup() {
  Serial.begin(115200);

   if(!LittleFS.begin()){
    Serial.println("LittleFS Mount Failed");
    return;
  }

  // Setup camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());  
}

// Function to URL encode a string
String urlEncode(const String &value) {
  String encodedValue = "";
  char c;
  char code0;
  char code1;

  for (size_t i = 0; i < value.length(); i++) {
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

void captureAndSend() {
  camera_fb_t *fb = NULL;

  // Take a picture
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Failed to capture picture");
    esp_err_t res = ESP_FAIL;
    Serial.printf("Camera capture failed with error 0x%x", res);
    return;
  }

  // Save the picture to LittleFS
  File file = LittleFS.open("/picture.jpg", "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    esp_camera_fb_return(fb);
    return;
  }
  file.write(fb->buf, fb->len);
  file.close();

  // Release the frame buffer
  esp_camera_fb_return(fb);

  // Send the picture to the API
  WiFiClient client;
  if (client.connect("192.168.0.161", 5000)) {
    client.println("POST /api/Posters/Snap HTTP/1.1");
    client.println("Host: 192.168.0.161");
    client.println("Content-Type: multipart/form-data; boundary=boundary");
    client.print("Content-Length: ");
    client.println(file.size() + 250); // Adjust for additional form data

    // Start sending the multipart/form-data
    client.println("--boundary");
    client.println("Content-Disposition: form-data; name=\"posterId\"");
    client.println();
    client.println(posterId);
    client.println("--boundary");
    client.println("Content-Disposition: form-data; name=\"image\"; filename=\"picture.jpg\"");
    client.println("Content-Type: image/jpeg");
    client.println();

    // Send the image data
    file.seek(0);
    while (file.available()) {
      client.write(file.read());
    }

    // Finish sending the multipart/form-data
    client.println();
    client.println("--boundary--");
    client.println();

    // Wait for the server response
    while (client.connected() && !client.available()) {
      delay(1);
    }

    // Print the server response
    while (client.available()) {
      Serial.write(client.read());
    }

    client.stop();

    // Delete the picture file
    LittleFS.remove("/picture.jpg");
  } else {
    Serial.println("Failed to connect to the server");
  }
}

void loop() {
  static unsigned long lastCaptureTime = 0;

  // Capture and send picture every captureInterval milliseconds
  if (millis() - lastCaptureTime >= captureInterval) {
    captureAndSend();
    lastCaptureTime = millis();
  }

  // Add other loop tasks here if needed
}