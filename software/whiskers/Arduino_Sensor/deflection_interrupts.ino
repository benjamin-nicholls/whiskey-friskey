// Sensor includes.
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90393.h>
// Wifi/server includes.
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "mainpage.h"
#include "jscript.h"
// Make your own 'credentials.h'. See example.
#include "credentials.h"  

Adafruit_MLX90393 sensor = Adafruit_MLX90393();
sensors_event_t event;
float mag_x, mag_y, mag_z;
const int PIN = 0X18
const int INTERRUPT_PIN = 2;

WebServer server(80);


void setup() {
    // Wire.begin(YOUR_SDA_PIN, YOUR_SCL_PIN);
    Serial.begin(115200);
    delay(1000);
    Serial.print("Magnetometer Test\n\n");
    
    setupSensor()
    // https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), readSensor, CHANGE)                
}


void setupSensor() {
    //Serial.println("Starting Adafruit MLX90393 Demo");
    bool printFlag = false;
    while (!sensor.begin_I2C(PIN)) { 
        if (!printFlag) {
            Serial.print("No sensor found ... check your wiring?\n");
            printFlag = true;
        }
        delay(10);
    }
    Serial.print("Found a MLX90393 sensor\n"); 
}


void setupWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
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
}


void loop() {
    //Serial.print("X: "); 
    //Serial.print(a); 
    //Serial.print(" uT\t");
    //Serial.print("Y: "); 
    //Serial.print(b); 
    //Serial.print(" uT\t");
    //Serial.print("Z: "); 
    //Serial.print(c); 
    // Serial.println(" uT\t");

    int deflection = sqrt((mag_x*mag_x) + (mag_y*mag_y) + (mag_z*mag_z));
    Serial.print(deflection);
    Serial.print("\t");
    if (deflection > 4500){
        Serial.print("No point of Contact\n");
    } else {
        Serial.print("Point of contact Detected\n");
    }

    delay(10); // Adjust the delay as needed
}

void readSensor() {
    sensor.getEvent(&event);
    mag_x = event.magnetic.x;
    mag_y = event.magnetic.y;
    mag_z = event.magnetic.z;
}