/*
Project: AppCar Line Follower

Hardware Required: 
    - NodeMCU 1.0 (ESP-12E Module)
    - Motor Shield
    - Infra Red Sensors x 2
    - 2 Motors with Wheels
    *(The basic AppCar Kit)*

Software Required:
    - Arduino IDE 1.8.X
    - NodeMCU Drivers for Windows & Mac (http://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
    - Visual Studio Code (with Arduino IDE plugin - for Intellisence Code Editing)
*/

// Include application, user and local libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Define variables and constants
int pwmSpeed = 200; // This sets the motor speed for turning left or right

// Definning Inputs
#define LS 14     // left sensor
#define CS 12     // centre sensor
#define RS 13     // right sensor

// Definning Outputs
#define LM1 5     // left motor - forward
#define LM2 0     // left motor - reverse
#define RM1 4     // right motor - forward
#define RM2 2     // right motor - reverse

void setup()
{
    // Sensors
    pinMode(LS, INPUT);     // set LS pin to INPUT
    pinMode(RS, INPUT);     // set RS pin to INPUT
    pinMode(CS, INPUT);     // set CS pin to INPUT
    
    // Motors
    pinMode(LM1, OUTPUT);   // set LM1 pin to OUTPUT
    pinMode(LM2, OUTPUT);   // set LM2 pin to OUTPUT
    pinMode(RM1, OUTPUT);   // set RM1 pin to OUTPUT
    pinMode(RM2, OUTPUT);   // set RM2 pin to OUTPUT
    
    // Start Serial with Bitrate of 115200
    Serial.begin(115200);
}
void loop()
{
    
    if(!(digitalRead(LS)) && !(digitalRead(RS)))     // Drive Forward
    {
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
        Serial.println("Drive Forward");
    }
    
    if(!(digitalRead(LS)) && digitalRead(RS))     // Turn right
    {
        digitalWrite(LM1, HIGH);
        digitalWrite(LM2, LOW);
        analogWrite(RM1, pwmSpeed);
        digitalWrite(RM2, LOW);
        Serial.println("Turning Right");
    }
    
    if(digitalRead(LS) && !(digitalRead(RS)))     // Turn left
    {
        analogWrite(LM1, pwmSpeed);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, HIGH);
        digitalWrite(RM2, LOW);
        Serial.println("Turning Left");
    }
    
    if(digitalRead(LS) && digitalRead(RS))       // Stop
    {
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        Serial.println("Stop");
    }
    
}

// Now we need to adjust the sensors to work accurately.