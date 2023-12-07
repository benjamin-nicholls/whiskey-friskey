// Sensor includes.
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90393.h>
// Wifi/server includes.
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
 

Adafruit_MLX90393 sensor = Adafruit_MLX90393();
const char* SSID = "Galaxy M12 7ED0";
const char* PASSWORD = "tiaq1076";
WebServer server(80);


volatile float mag_x, mag_y, mag_z;

#define INTERRUPT_PIN 25
#define I2C_PIN 0X18



void setup() {
    // Wire.begin(YOUR_SDA_PIN, YOUR_SCL_PIN);
    //Serial.begin(115200);  // baud rate = 115200
    setupSensor();
    setupWifi();
     
    // https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), readSensor, RISING);      
}


void setupSensor() {
    //Serial.println("Starting Adafruit MLX90393 Demo");
    bool printFlag = false;
    while (!sensor.begin_I2C(I2C_PIN)) {
        if (!printFlag) {
            //Serial.print("No sensor found... check wiring?\n");
            printFlag = true;
        }
        delay(10);
    }
    //Serial.print("Found a MLX90393 sensor.\n"); 
}

void setupWifi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    //Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        //Serial.print(".");
    }
/*
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    */
}
void loop() {
    //readSensor();
    /*
    Serial.print("X: "); 
    Serial.print(mag_x); 
    Serial.print(" uT\t");
    Serial.print("Y: "); 
    Serial.print(mag_y); 
    Serial.print(" uT\t");
    Serial.print("Z: "); 
    Serial.print(mag_z); 
    Serial.println(" uT\t");
    */
    
    //if (deflection > 4500){
      //  Serial.print("No point of Contact\n");
   // } else {
      //  Serial.print("Point of contact Detected\n");
   // }

    //delay(1000); // Adjust the delay as needed
}

void readSensor() {
    sensors_event_t event;
    sensor.getEvent(&event);

    //Magnetic Field 
    mag_x = event.magnetic.x;
    mag_y = event.magnetic.y;
    mag_z = event.magnetic.z;

    //atan2 is the arctangent2 function, which takes two arguments and returns the angle in radians from 0 to 2π radians
    int pi =  3.14159;
    Angle_x = atan2(mag_y, mag_z) * 180 / pi;
    Angle_y = atan2(mag_z, mag_x) * 180 / pi;
    Angle_z = 90 - atan2(sqrt(mag_x^2 + mag_y^2), z) * 180 / pi;
}
