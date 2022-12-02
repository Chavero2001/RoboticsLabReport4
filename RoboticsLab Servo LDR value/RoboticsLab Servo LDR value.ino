/*
The goal of this program is to control the direction of a Servo motor by using a LDR while also printing its resistance value

Servo motor, map function, analog input.

*/

#include <Servo.h> // include Servo library

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to read voltage
int val;    // variable to read the value from the analog pin
float volt; // variable to store the value of the reading in volts
int voltS;  // variable to eliminate decimals from volts to use map function
float r1;   // variable to store calculated value for resistance

void setup() {
  Serial.begin(9600); //initialize serial monitor
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  volt = analogRead(potpin);            // reads the value of the LDR voltage (value between 0 and 1023)
  volt = volt/(1023/5);     // converte from bits to volts
  voltS = volt*100;         // The value in volts is multiply by 100 to eliminate decimals...
                            //... and being able to use the map function
            

  r1=(5-volt)/volt; // calculate the resitance of the LDR
  
  val=map(voltS,030,440,0,180); // use the map function to convert from volt to degrees

  Serial.print("LDR value: ");
  Serial.print(r1);             // print the resistance value
  Serial.print("k   ");

  Serial.print("Voltage value: ");
  Serial.print(volt);           // print volt value
  Serial.print("v   ");

   Serial.print("Degrees: ");
  Serial.print(val);            // print degrees value
  Serial.println();
  myservo.write(val);           // sets the servo position according to the voltage value
  delay(15);                    // waits for the servo to get there

  
}