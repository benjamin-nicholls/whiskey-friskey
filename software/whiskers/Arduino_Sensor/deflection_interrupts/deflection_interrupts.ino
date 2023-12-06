// Sensor includes.
#include <Wire.h>
#include "MLX90393.h"
//#include <Adafruit_Sensor.h>
//#include <Adafruit_MLX90393.h>
// Wifi/server includes.
#include <WiFi.h>
#include <WiFiClient.h>
#include "WebServer.h"
#include "mainpage.h"
#include "jscript.h"
// Make your own 'credentials.h'. See example.
#include "credentials.h"  

#define INTERRUPT_PIN 5
#define I2C_PIN 0X18
#define SDA_PIN 21  // Data pin.
#define SCL_PIN 22 // Clock pin.

MLX90393 mlx;
const byte axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG;
float mag_x, mag_y, mag_z;
volatile bool dataReady = false;

//WebServer server(80);


void setup() {
    Wire.begin(SDA_PIN, SCL_PIN);
    Wire.setClock(400000);
    Wire.begin();
    Serial.begin(115200);  // baud rate = 115200
    delay(1000);

    setupSensor();
    //setupWifi();
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), readSensor, RISING);      
}


void setupSensor() {
    bool printFlag = false;
    byte status = mlx.begin(0, 0, INTERRUPT_PIN, Wire);
    Serial.print(status);
    Serial.print("Found a MLX90393 sensor.\n"); 
    // gain
    // oversampling
    // digitalfiltering
    // resolution
    //temperature compenstation
    // sparkfun MLX... hookup guide
    mlx.startBurst(axisFlags);
    return;
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
    Serial.println(SSID);

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    //server.on("/", []() {server.send(200, "text/html", page);});
    //server.on("/jscript.js", []() {server.send(200, "text/javascript", javascript);});
    
   return;
}

void loop() {
    MLX90393::txyzRaw data;
    if (dataReady) {
        Serial.read();
        mlx.readMeasurement(axisFlags, data);
        mag_x = data.x;
        mag_y = data.y;
        mag_z = data.z;

        Serial.print("\nX: ");
        Serial.print(mag_x);
        Serial.print("\nY: ");
        Serial.print(mag_y);
        Serial.print("\nZ: ");
        Serial.print(mag_z);

        dataReady = false;
    }
}

void readSensor() {
    dataReady = true;
}