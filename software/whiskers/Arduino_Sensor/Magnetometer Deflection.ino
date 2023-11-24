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
float a,b,c;
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
  sensors_event_t event;
  sensor.getEvent(&event);
  a=event.magnetic.x;
  b=event.magnetic.y;
  c=event.magnetic.z;
 
      //Serial.print("X: "); 
      //Serial.print(a); 
     //Serial.print(" uT\t");
      //Serial.print("Y: "); 
      //Serial.print(b); 
     //Serial.print(" uT\t");
      //Serial.print("Z: "); 
      //Serial.print(c); 
    // Serial.println(" uT\t");
  int def= sqrt(a*a+b*b+c*c);
  Serial.print(def);
  Serial.print("\t");
  if (def>4500){
    Serial.print("No point of Contact\n");
  }
  if(def<4400){
    Serial.print("Point of contact Detected\n");
  }

  delay(10); // Adjust the delay as needed
}
