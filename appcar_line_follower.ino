/*
Project: AppCar Line Follower
Company: AppShed 
*/

// Include application, user and local libraries
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Definning Inputs
#define LS 14     // left sensor
#define CS 12     // centre sensor
#define RS 13     // right sensor

// PWM Inputs
#define POT A0 // Analog Input A0
int potReadValue = 0;
int PWM = 0;

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
    
    // Analog Inputs
    pinMode(POT, INPUT);    // set POT pin to INPUT

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
    // Reading the Analog Signal
    potReadValue = analogRead(POT);

    // Basic Calculation (0-1000)
    PWM = 1000 - potReadValue;
    
    // Print PWM Values to Serial Console
    Serial.println(PWM);

    if(!(digitalRead(LS)) && !(digitalRead(RS)))     // Drive Forward
    {
        analogWrite(LM1, PWM);
        digitalWrite(LM2, HIGH);
        analogWrite(RM1, PWM);
        digitalWrite(RM2, HIGH);
        Serial.println("Drive Forward");
    }
    
    if(!(digitalRead(LS)) && digitalRead(RS))     // Turn right
    {
        analogWrite(LM1, PWM);
        digitalWrite(LM2, HIGH);
        digitalWrite(RM1, LOW);
        digitalWrite(RM2, LOW);
        Serial.println("Turning Right");
    }
    
    if(digitalRead(LS) && !(digitalRead(RS)))     // Turn left
    {
        digitalWrite(LM1, LOW);
        digitalWrite(LM2, LOW);
        analogWrite(RM1, PWM);
        digitalWrite(RM2, HIGH);
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