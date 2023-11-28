#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90393.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "mainpage.h"
#include "jscript.h"

     Adafruit_MLX90393 sensor = Adafruit_MLX90393();
    const char* ssid = "Galaxy M12 7ED0";
    const char* password = "tiaq1076";
    WebServer server(80);
//YOUR_SDA_PIN = D21
//YOUR_SCL_PIN= D
String text= "";
void setup() {
 // Wire.begin(YOUR_SDA_PIN, YOUR_SCL_PIN);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Magnetometer Test"); Serial.println("");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.on("/", []() {server.send(200, "text/html", page);});
    server.on("/jscript.js", []() {server.send(200, "text/javascript", javascript);});

    // Set up The Sensor
    while (!Serial) {
                      delay(10);
                    }
  Serial.println("Starting Adafruit MLX90393 Demo");

        if (! sensor.begin_I2C(0X18)) { 
                                 Serial.println("No sensor found ... check your wiring?");
                                while (1) { delay(10); }
                                  }
  Serial.println("Found a MLX90393 sensor");
              
}

void loop() {
  float a,b,c;
  sensors_event_t event;
  sensor.getEvent(&event);
  server.on("/data", [](){
      Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print(" uT\t");
      Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print(" uT\t");
      Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.println(" uT");

       text1 = (String)a;
       text2 = (String)b;
       text3 = (String)c;
       server.send(200, "text/plain", text1);
       server.send(200, "text/plain", text2);
       server.send(200, "text/plain", text3);
  }

  delay(500); // Adjust the delay as needed
}
