#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "esp_camera.h"
#include "driver/rtc_io.h"

// Pin definition for CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22
#define STACK_SIZE        16384

const char* ssid = "WijtsB";
const char* password = "C0cac0la";

String serverPath = "http://192.168.0.161:5000/api/Posters";
String posterId = "fd38ef73-eba5-4f87-a26e-e6a22147e4da";
String name = "test-top";

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

void captureAndSendImage(HTTPClient& http, const String& formData) {
  Serial.println("Capturing image...");
  Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());

  // Check if there is enough free heap
  if (ESP.getFreeHeap() < 200000) {
    Serial.println("Low free heap. Capture aborted.");
    return;
  }

  camera_config_t config;
  // ... (existing camera configuration)

  // Set a lower frame size
  config.frame_size = FRAMESIZE_QQVGA;  // Adjust the frame size as needed

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x ", err);
    return;
  }

  camera_fb_t *fb = esp_camera_fb_get();
  if (fb) {
    // Continue with the existing code for sending the image

    // Reset the camera configuration back to the original
    config.frame_size = FRAMESIZE_QVGA;  // Adjust the frame size as needed
    esp_camera_deinit();
    esp_camera_init(&config);

    // ... (existing code)

    return;
  } else {
    Serial.println("Camera capture failed");
  }
}

void customLoopTask(void *pvParameters) {
    for (;;) {
        HTTPClient http;

        Serial.printf("Free heap before capturing image: %d bytes\n", ESP.getFreeHeap());
        delay(30000); // 30 seconds delay

        // Connect to WiFi if not connected
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("Reconnecting to WiFi...");
            WiFi.begin(ssid, password);
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
            }
            Serial.println("\nReconnected to WiFi");
        }

        // Capture and send image
        captureAndSendImage(http, "name=" + urlEncode(name));

        // End the request
        http.end();
    }
}

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(customLoopTask, "loopTask", STACK_SIZE, NULL, 1, NULL, 1);

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

  // Camera setup
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
  config.frame_size = FRAMESIZE_QVGA;
  config.fb_count = 1; // Adjust the buffer count as needed
  config.jpeg_quality = 20;

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x ", err);
    return;
  }

  HTTPClient http;

  // Send request to create a poster
  http.begin(serverPath + "/Create");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Example
  // String formData = "name=" + urlEncode(name) + "&" + "date=" + urlEncode(date)
  String formData = "name=" + urlEncode(name);

  // Capture and send image during setup
  captureAndSendImage(http, formData);

  // End the request
  http.end();
}

void loop() {
  // Do nothing here
}