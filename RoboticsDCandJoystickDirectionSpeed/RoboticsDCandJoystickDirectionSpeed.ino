/*
The goal of this program is to control the direction and speed of a DC motor
by using L293D and a joystick. 

DC motor controlled by L293D, and analog and digital input 
*/

int in; // variable that stores the value read
float in2; // this is to convert the value in bits from integer to float

int out1; // variable to convert from bits to speed to move clock wise


float b1; //variables to calculate b from y=mx+b 
float b2; //there are multiple variables since I have troubles putting everything in one equation
float b3;

int out2; //variables to convert from bits to speed to move counter clock wise
float out2_1; //multiple variables to debug
float out2_2;

void setup() {

pinMode(5,OUTPUT);
pinMode(4,OUTPUT); //define pins 
pinMode(3,OUTPUT);
Serial.begin(9600); //initialize serial monitor

}

void loop() {
  
in=analogRead(A0); //reads the value given by the joystick
Serial.print("in: "); 
Serial.println(in); //print that value to debug

//If the joystick goes to the left the motor will spin in one direction
//If the joystick goes to the right the motor will spin in the opposite direction
//If the joystick is not moved, the motor will not spin
//The farther the joystick is moved, the faster the motor will spin in that direction

//to the left the value will range from 0 to 499
out1=(-in*255/499)+255; //converts the analog reading from 0 to 499 to analog writing (0-255) 
Serial.print("out1: ");
Serial.println(out1); //print that value to debug

//b from y=mx+b is calculated for the speed formula when the value is from 501 to 1023
b1=1023-501;
Serial.print("b1: ");
Serial.print(b1); 
b2=255/b1;
b3=b2*501;
Serial.print("  b2: "); //all the values of b are printed to debug
Serial.print(b2);
Serial.print("b3: ");
Serial.println(b3);

//to the right the value will range from 501 to 1023
in2=in;
out2_1=in2*b2; //b2 is equal to 1023-501, and was previosly calculated above
Serial.print("out2.1: ");
Serial.print(out2_1);
out2_2=out2_1-b3; //the value previosly calculated of b is used 
Serial.print("  out2.2: ");
Serial.print(out2_2); // the values of all the steps are printed to debug
out2=out2_2;
Serial.print("  out2: ");
Serial.println(out2);
//delay(1000);


if(in<490){ //move the motor clock wise 
digitalWrite(3,LOW); //set the motor to move in clock wise direction 
digitalWrite(4,HIGH);
analogWrite(5,out1); //use the velocity calculated for this direction
Serial.println("Forward"); //print to debug
};

if(in>=499||in<=501){ //stop the motor if the joystick doesn't move
analogWrite(5,0);
digitalWrite(3,0); 
digitalWrite(4,0);
};

if(in>501){ //move the motor counter clock wise 
digitalWrite(3,HIGH); //set the motor to move in counter clock wise direction 
digitalWrite(4,LOW);
analogWrite(5,out2); //use the velocity calculated for this direction
Serial.println("Backwards"); //print to debug
};

}
