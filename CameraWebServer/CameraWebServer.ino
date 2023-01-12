#include "esp_camera.h"
#include <WiFi.h>

#define CAMERA_MODEL_M5STACK_WIDE

#define RXD2 33
#define TXD2 4

WiFiServer TCPServer(8266); //Servidor del ESP32
WiFiClient TCPClient; //Cliente TCP (PC)


#include "camera_pins.h"

const char* ssid = "Yova";
const char* password = "contra0102";

void startCameraServer();

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.setDebugOutput(true);
  Serial.println();

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
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);//flip it back
    s->set_brightness(s, 1);//up the blightness just a bit
    s->set_saturation(s, -2);//lower the saturation
  }
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  startCameraServer();

  Serial.print("Camera Ready! Use 'http://");
  Serial.print(WiFi.localIP());
  Serial.println("' to connect");

  TCPServer.begin();
}

void loop() {

     /*if (Serial.available() > 0)
       byteReceived(Serial.read());*/
    if (!TCPClient.connected()) {
        // try to connect to a new client
        TCPClient = TCPServer.available();
    } else {
        // read data from the connected client
        if (TCPClient.available() > 0) {
          
            int n = TCPClient.read(); 
            Serial.println(n);
            control(n);
            
        }
    }
}

void control(int n){
  
  switch (n) {
  case 48:
    Serial2.println("0");
  break;
  case 49:
    Serial2.println("1");
  break;
  case 50:
    Serial2.println("2");
  break;
  case 51:
    Serial2.println("3");
  break;
  case 52:
    Serial2.println("4");
  break;
  case 53:
    Serial2.println("5");
  break;
  case 54:
    Serial2.println("6");
  break;
  case 55:
    Serial2.println("7");
  break;
  case 56:
    Serial2.println("8");
  break;
  default:
    Serial2.println("8");
  break;
  }

  Serial.println(n);

}
