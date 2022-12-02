/*
The goal of this program is to control the direction of a stepper motor by using 
one axis of a joystick

Stepper motor, analog reading

*/

#include <Stepper.h> //include stepper Library
 
const float STEPS_PER_REV = 32; // Number of steps per internal motor revolution 
 

const float GEAR_RED = 64; //  Amount of Gear Reduction
 

const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;//steps per geared output rotation
 

int StepsRequired; // Number of Steps Required

Stepper steppermotor(STEPS_PER_REV, 8, 10, 9, 11);//define the pins that are used for the stepper

int val;//variable to store the value for analog reading
 
void setup()
{
 Serial.begin(9600); //initialize Serial monitor
}
 
void loop()
{
  val=analogRead(A0); //read the value of the joystick
  
  if(val<490){ //if the joystick goes to the left, the value will be less than 490...
              //...if that is the case, the stepper motor will spn counter clock wise
  StepsRequired  =  -STEPS_PER_OUT_REV / 10; //the value is negative to indicate that is conter cw
                                      //10 is the number that work the best to move the motor
  steppermotor.setSpeed(700);  //max speed
  steppermotor.step(StepsRequired); //move the motor the Steps required
  
  //Serial print the values to debug
  Serial.print(val);
  Serial.print("    ");         
  Serial.print(StepsRequired);
  Serial.println();
  };
  if(val>=490||val<=500){ //do not move the stepper if the joystick is not moved
  steppermotor.setSpeed(0);  //no speed
  steppermotor.step(0); //no steps
  };  
  if(val>500){//if the joystick goes to the right, move the motor clock wise
  StepsRequired  =  STEPS_PER_OUT_REV / 10;  //the value is positive since it is clock wise  
  steppermotor.setSpeed(700);  //max speed
  steppermotor.step(StepsRequired); //move the motor the Steps required

  //Serial print the values to debug
  Serial.print(val);
  Serial.print("    ");
  Serial.print(StepsRequired);
  Serial.println();
  };
  
 
}