/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/

/***
This code is to be bootloaded on the arduino prior to the "Arduno_Sensor.ino". After this, make the necessary hardware connections
and setup the arduino with the serial monitor on the Arduino IDE. This will give us the I2C address of the magnetosensor
on the serial monitor.
Please be informed that the SDA_PIN and SCL_PIN have been defined in accordance with the Arduino Uno R3 schematic pin diagram
and if anyother MCU is to be used,then the respective pins have to be defined according to the schematics of the new MCU
 
#include "I2CScanner.h"
#include <Wire.h>

I2CScanner scanner;

//if you use ESP8266-01 with not default SDA and SCL pins, define these 2 lines, else delete them	
#define SDA_PIN 27 //define pin by refering to pin-schematics of the board being used
#define SCL_PIN 28 //define pin by refering to pin-schematics of the board being used

void setup() 
{	
	//uncomment the next line if you use custom sda and scl pins for example with ESP8266-01 (sda = 4, scl = 5)
	//Wire.begin(SDA_PIN, SCL_PIN);
	
	Serial.begin(9600);
	while (!Serial) {};

	scanner.Init();
}

void loop() 
{
	scanner.Scan();
	delay(5000);
}/***************************************************
Copyright (c) 2018 Luis Llamas
(www.luisllamas.es)
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
 ****************************************************/
 
 #include "I2CScanner.h"
#include <Wire.h>

I2CScanner scanner;

//if you use ESP8266-01 with not default SDA and SCL pins, define these 2 lines, else delete them	
#define SDA_PIN 27 //define pin by refering to pin-schematics of the board being used
#define SCL_PIN 28 //define pin by refering to pin-schematics of the board being used

void setup() 
{	
	//uncomment the next line if you use custom sda and scl pins for example with ESP8266-01 (sda = 4, scl = 5)
	//Wire.begin(SDA_PIN, SCL_PIN);
	
	Serial.begin(9600);
	while (!Serial) {};

	scanner.Init();
}

void loop() 
{
	scanner.Scan();
	delay(5000);
}
***/


#include "I2CScanner.h"
#include <Wire.h>

I2CScanner scanner;

//if you use ESP8266-01 with not default SDA and SCL pins, define these 2 lines, else delete them	
#define SDA_PIN 27 //define pin by refering to pin-schematics of the board being used
#define SCL_PIN 28 //define pin by refering to pin-schematics of the board being used

void setup() 
{	
	//uncomment the next line if you use custom sda and scl pins for example with ESP8266-01 (sda = 4, scl = 5)
	//Wire.begin(SDA_PIN, SCL_PIN);
	
	Serial.begin(9600);
	while (!Serial) {};

	scanner.Init();
}

void loop() 
{
	scanner.Scan();
	delay(5000);
}
