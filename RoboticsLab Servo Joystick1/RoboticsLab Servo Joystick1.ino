/*
The goal of this program is to control a Servo motor by using a Joystick

Map function, servo motor, analog input
*/

#include <Servo.h> //include servo library

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the joystick (potentiometer)
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  val = analogRead(potpin);            // reads the value of the joystick (potentiometer) (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo
}