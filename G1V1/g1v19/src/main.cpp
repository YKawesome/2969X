/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       codycgee                                                  */
/*    Created:      Sat Sep 14 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::controller Controller1 = vex::controller();
vex::motor FLWheel(vex::PORT1,vex::gearSetting::ratio18_1,false);
vex::motor FRWheel(vex::PORT2,vex::gearSetting::ratio18_1,true);
vex::motor BLWheel(vex::PORT3,vex::gearSetting::ratio18_1,false);
vex::motor BRWheel(vex::PORT4,vex::gearSetting::ratio18_1,true);
vex::motor Tilter(vex::PORT5,vex::gearSetting::ratio36_1,true);
vex::motor TwoBar(vex::PORT6,vex::gearSetting::ratio36_1,false);
vex::motor LIntake(vex::PORT7,vex::gearSetting::ratio18_1,false);
vex::motor RIntake(vex::PORT8,vex::gearSetting::ratio18_1,true);
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void moveForward(float rotations,float speed) { //This is to move forward.
        FLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        FRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BRWheel.rotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
}

void moveBackward(float rotations,float speed) { //This is to move backward.
        FLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        FRWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BRWheel.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
}

void turnRight(float rotations,float speed) { //This is to turn right.
        FLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        FRWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BRWheel.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
}

void turnLeft(float rotations,float speed) { //This is to turn left.
        FLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        FRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BRWheel.rotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
}

void Intake (float rotations,float speed) {
    RIntake.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
    LIntake.rotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
    
}

void Outtake (float rotations,float speed) {
    RIntake.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
    LIntake.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
}

void fwdTilt (float rotations,float speed) {
    Tilter.rotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
}

void revTilt (float rotations,float speed) {
    Tilter.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);

}

void fullTilt(){
    Tilter.rotateTo(2669,rotationUnits::raw,100,velocityUnits::pct);
}
    
void halfTilt(){
    Tilter.rotateTo(800,rotationUnits::raw,100,velocityUnits::pct);
    Tilter.stop(brakeType::brake);
}

void unTilt(){
    Tilter.rotateTo(0,rotationUnits::raw,100,velocityUnits::pct);
    Tilter.stop(brakeType::coast);
}

void Expand (float rotations,float speed) {
    TwoBar.rotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
}

void Contract (float rotations,float speed) {
    TwoBar.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);

}

void presetBrake () {
    TwoBar.stop(brakeType::hold);
    Tilter.stop(brakeType::coast);
    RIntake.stop(brakeType::brake);
    LIntake.stop(brakeType::brake);
}

void fwdIntake (float rotations, float speed) {
    FLWheel.startRotateFor(4,rotationUnits::rev,20,velocityUnits::pct);
    FRWheel.startRotateFor(4,rotationUnits::rev,20,velocityUnits::pct);
    BLWheel.startRotateFor(4,rotationUnits::rev,20,velocityUnits::pct);
    BRWheel.startRotateFor(4,rotationUnits::rev,20,velocityUnits::pct);
    RIntake.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
    LIntake.rotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
}

void autonomous( void ) {
//Parameters: rotations, speed
//Example: function(rotations,speed);
   presetBrake();
   fullTilt();
   unTilt(); 
    
    fwdIntake(30,100);
    
}

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                              User Control Task                             */
/*                                                                            */
/*  This task is used to control your robot during the user control phase of  */
/*  a VEX Competition.                                                        */
/*                                                                            */
/*  You must modify the code to add your own robot specific commands here.    */
/*----------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop
  while (1){
       FLWheel.spin(vex::directionType::fwd,
            Controller1.Axis2.position(vex::percentUnits::pct) + Controller1.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct);
       BLWheel.spin(vex::directionType::fwd,
            Controller1.Axis2.position(vex::percentUnits::pct) + Controller1.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct);
        //Right motor, vertical axis of left joystick minus horizontal axis of left joystick
       FRWheel.spin(vex::directionType::fwd,
            Controller1.Axis2.position(vex::percentUnits::pct) - Controller1.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct); 
       BRWheel.spin(vex::directionType::fwd,
            Controller1.Axis2.position(vex::percentUnits::pct) - Controller1.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct);  
      
      
      if (Controller1.ButtonL2.pressing()) {
            RIntake.spin(directionType::fwd,100,velocityUnits::pct);
            LIntake.spin(directionType::fwd,100,velocityUnits::pct);
      }
      
      else if (Controller1.ButtonR2.pressing()){
            RIntake.spin(directionType::rev,100,velocityUnits::pct);
            LIntake.spin(directionType::rev,100,velocityUnits::pct);
      }
      
      else if (Controller1.ButtonA.pressing()){
            RIntake.spin(directionType::rev,2,velocityUnits::pct);
            LIntake.spin(directionType::fwd,2,velocityUnits::pct);
      }
      
      else if (Controller1.ButtonUp.pressing()){
            RIntake.stop(brakeType::coast);
            LIntake.stop(brakeType::coast);
      }
      
      else {
           RIntake.stop(brakeType::brake);
           LIntake.stop(brakeType::brake);
      }
          
       
      if (Controller1.ButtonDown.pressing()) {
           Tilter.spin(directionType::rev,100,velocityUnits::pct);
            
      } 
      
      else if (Controller1.ButtonUp.pressing()){
           Tilter.spin(directionType::fwd,20,velocityUnits::pct);
      }
      
      else if (Controller1.ButtonLeft.pressing()){
           unTilt();
      }
      
      else {
            Tilter.stop(brakeType::coast);
      }
          
          
      if (Controller1.ButtonL1.pressing()) {
            halfTilt();
            TwoBar.spin(directionType::fwd,100,velocityUnits::pct);
      }
      else if (Controller1.ButtonR1.pressing()){
            halfTilt();
            TwoBar.spin(directionType::rev,100,velocityUnits::pct);
      }
     
      else {
            TwoBar.stop(brakeType::brake);
      }
     
          
      
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
     
    

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}