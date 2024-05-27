/*
  keyestudio  ESP32-CAM Video Smart Car
  Define Network SSID & Password
  Set ap to 1 to use ESP32-CAM as Standalone Access Point with default IP 192.168.4.1
  Set ap to 0 to connect to a router using DHCP with hostname espressif
*/
#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_camera.h"
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "SetMotor.h"
#include "app_server.h"

// bool ap = 0;  //When it is 1, esp32 turns on wifi, the mobile phone is connected, and the IP is 192.168.4.1; when it is 0, it is connected to wifi, and the IP needs to be obtained through serial port printing.
// const char* ssid = "ChinaNet_2.4G";        //AP Name or Router SSID
// const char* password = "ChinaNet@233";  //Password. Leave blank for open network.
// const char* ssid = "myinvententerprise";
// const char* password = "04222682";

bool ap = 1;
const char* ssid = "keyes1";        //AP Name or Router SSID
const char* password = "88888888";  //Password. Leave blank for open network.



//AP Settings
int channel = 11;       // Channel for AP Mode
int hidden = 0;         // Probably leave at zero
int maxconnection = 1;  // Only allow one device to connect

// Camera Pin Definitions - Don't heckin' touch.
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

// Webserver / Controls Function
void startCameraServer();

void setup() {
  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // Prevent brownouts by silencing them. You probably want to keep this.
  i2c_init();  //Initialize IIC, SDA is IO14, SCL is IO13, the pins are bound to the motor driver board and cannot be modified.

  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  // Camera Configuration - Again, don't touch.
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
  //init with high specs to pre-allocate larger buffers
  if (psramFound()) {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {  //ESP_OK
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  //drop down frame size for higher initial frame rate
  sensor_t* s = esp_camera_sensor_get();
  s->set_framesize(s, FRAMESIZE_QVGA);
  //Video flip code
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
  // s->set_vflip(s, 0);
  // s->set_hmirror(s, 0);

  ledcSetup(7, 5000, 8);
  ledcAttachPin(12, 7);  //IO12 is the LED control pin and cannot be changed.

  if (!ap) {
    // Connect to Router
    Serial.println("ssid: " + (String)ssid);
    Serial.println("password: " + (String)password);
    Serial.println("WiFi is Client Scout32");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");
  } else {
    // Setup Access Point
    Serial.println("ssid: " + (String)ssid);
    Serial.println("password: " + (String)password);
    Serial.println("WiFi is Standalone Scout32");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password, channel, hidden, maxconnection);
    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.softAPIP());
    Serial.println("' to connect");
  }

  //Flash LED as ready indicator
  for (int i = 0; i < 5; i++) {
    ledcWrite(7, 0);  // flash led
    delay(200);
    ledcWrite(7, 255);
    delay(200);
  }

  //Start Webserver
  startCameraServer();
}

int i = 0;

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  // Serial.printf("RSSi: %ld dBm\n",WiFi.RSSI());

}
