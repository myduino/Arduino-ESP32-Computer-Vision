#include "esp_camera.h"
#include <WiFi.h>
#include <ArduinoWebsockets.h>
#include "esp_timer.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "soc/soc.h" //disable brownout problems
#include "soc/rtc_cntl_reg.h" //disable brownout problems
#include "driver/gpio.h"


// configuration for AI Thinker Camera board
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

#define LED 12
#include "SetMotor.h"


// const char* ssid     = "network-name"; // CHANGE HERE
// const char* password = "network-password"; // CHANGE HERE
const char* ssid = "myinvententerprise";
const char* password = "04222682";

const char* websockets_server_host = "192.168.0.101"; //current laptop server
const uint16_t websockets_server_port = 3001; // OPTIONAL CHANGE 

camera_fb_t * fb = NULL;
size_t _jpg_buf_len = 0;
uint8_t * _jpg_buf = NULL;
uint8_t state = 0;

using namespace websockets;
WebsocketsClient client;

void onMessageCallback(WebsocketsMessage message) {
  Serial.print("Got Message: ");
  Serial.println(message.data());

  String data = message.data();
  int motor = data.toInt();
  if(motor >= 200 || motor <= -200)
  {
    if(motor >= 200)
      Car_right(30,30);
    else
      Car_left(30,30);
    delay(2);
  }
  else if(motor >10 && motor <= 200)
  {
    if(motor<30)
    {
      Car_forward(50,70); //(motor_right,motor_left)
    }
    else 
      Car_forward(30,70);
    delay(2);
  }
  else if(motor < -10 && motor >= -200)
  {
    if(motor>-30)
    {
      Car_forward(70,50); //(motor_right,motor_left)
    }
    else 
      Car_forward(70,30);
    delay(2);
  }
  else{
    Car_forward(70,70);
    delay(2);
  }
  // String speed_left = motor.substring(0, motor.indexOf(",")); //(255,150) from 255 to ','
  // String speed_right = motor.substring(motor.indexOf(",") + 1); //(255/150) from ',' to 150

  // Car_forward(speed_left.toInt(), speed_right.toInt());
  // if(speed_left.toInt() <)
}

esp_err_t init_camera() {
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

  // parameters for image quality and size
  config.frame_size = FRAMESIZE_SVGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA (SVGA = 800 x 600)
  config.jpeg_quality = 10; //10-63 lower number means higher quality
  config.fb_count = 2;
  
  
  // Camera init
  Serial.println("Camera init ");
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("FAIL: 0x%x", err);
    ESP.restart(); //// addition
    //return err; //Actual
  }

  sensor_t * s = esp_camera_sensor_get();
  s ->set_saturation(s,2); // -2 to 2
  s->set_framesize(s, FRAMESIZE_SVGA);
  Serial.println("camera init OK");
  return ESP_OK;
};

esp_err_t init_wifi() {
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wi-Fi AP ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100); //500
    Serial.print(".");
  }
  Serial.println(" connected!");
  //Serial.println("WiFi OK");
  Serial.println("connecting to WS: ");
  client.onMessage(onMessageCallback);
  bool connected = client.connect(websockets_server_host, websockets_server_port, "/");
  if (!connected) {
    Serial.println("WS connect failed!");
    Serial.println(WiFi.localIP());
    state = 3;
    return ESP_FAIL;
  }
  if (state == 3) {
    return ESP_FAIL;
  }

  Serial.println("WS OK");
  //client.send("hello from ESP32 camera stream!");
  return ESP_OK;
};


void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  i2c_init();

  Serial.begin(115200);
  Serial.setDebugOutput(true);

  init_camera();
  init_wifi();
}

void loop() {

  if(!client.available())
  {
    init_wifi();
  }

  if (client.available()) {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Image capture failed");
      esp_camera_fb_return(fb);
      ESP.restart();
    }
    client.sendBinary((const char*) fb->buf, fb->len);
    //Serial.println("image sent");
    esp_camera_fb_return(fb);
    client.poll();
  }
  // Car_forward(200, 200);    //The car moves forward
  // delay(2000);              //delay 2s
  // Car_backwards(200, 200);  //The car moves back
  // delay(2000);
  // Car_left(100, 100);  //The car turns left
  // delay(2000);
  // Car_right(100, 100);  //The car turns right
  // delay(2000);
  // Car_stop();  //The car stops
  // delay(2000);
}