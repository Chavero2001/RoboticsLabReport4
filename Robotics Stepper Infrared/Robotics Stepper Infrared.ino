/*
The goal of this program is to control a stepper motor by using and infrared remote control
The direction will be controlled with the arrows left and right, and the speed with the volume buttons

Reading infrared, stepper motor
  
*/
 
#include <Stepper.h> //Stepper Library

#include <IRremote.h> // Include IR Remote Library
 
//---------------------------------------------------------
//This part is for IR
const int RECV_PIN = 4; // Define sensor pin
 

IRrecv irrecv(RECV_PIN); // Define IR Receiver and Results Objects
decode_results results;

//--------------------------------------------------------
//This part is for the Stepper
const float STEPS_PER_REV = 32; // Number of steps per internal motor revolution 
 
const float GEAR_RED = 64; //  Amount of Gear Reduction 

const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED; // Number of steps per geared output rotation
 
int StepsRequired; // Number of Steps Required

Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11); //define the pins used for the stepper

//--------------------------------------------------------


// Define variable to store last code received
unsigned long lastCode; 

int speed=700; //initial speed
 
void setup(){
  
  Serial.begin(9600); //initialize Serial monitor
  // Enable the IR Receiver
  irrecv.enableIRIn();
}
 
void loop(){
  if (irrecv.decode(&results)){
    // Print Code to debug
        Serial.println(results.value, HEX); //print in HEX 
        
        if(results.value == 0xFFFFFFFF) //FFFFFFFF is used to indicate when a value is repated
        {
          // If Repeat then use last code received
          results.value = lastCode;        
        }
        
        if(results.value==0xFF629D){ //speed +
            lastCode = results.value;  //store the value of the code read in lastCode        
            speed=speed+10; //increase the speed by ten 
            if (speed>700){speed=700;} //the limit for the speed is 700, it cannot be passed
            Serial.print(" Speed:"); 
            Serial.println(speed); //print speed to debug
        }

        if(results.value==0xFFA857){ //speed -
            lastCode = results.value; //store the value of the code read in lastCode        
            speed=speed-10; //decrease the speed by 10
            if (speed<10){speed=10;} //it is possible to decrease the speed until 10
            Serial.print(" Speed:");
            Serial.println(speed); //print speed to debug
        }
             
        if(results.value==0xFFC23D){ //Clock wise
            lastCode = results.value; //store the value of the code read in lastCode      
            StepsRequired  = STEPS_PER_OUT_REV/15; //15 is the number that worked the best for this case
            steppermotor.setSpeed(speed); //move the stepper with x speed 

            //print to debug
            Serial.print("Clock wise ");
            Serial.print(" Speed:");
            Serial.println(speed); 
            steppermotor.step(StepsRequired); //move the stepper
        }
        if(results.value==0xFF22DD){ //Counter Clock wise
            lastCode = results.value;  //store the value of the code read in lastCode
            StepsRequired  = - STEPS_PER_OUT_REV/15; //in this case the value is negative to indicate that is ccw
            steppermotor.setSpeed(speed);  //move the stepper with x speed 
            
            //print to debug
            Serial.print("Counter clock wise ");
            Serial.print(" Speed:");
            Serial.println(speed); 
            steppermotor.step(StepsRequired); //move the stepper
        }
        
        irrecv.resume();
  }

}