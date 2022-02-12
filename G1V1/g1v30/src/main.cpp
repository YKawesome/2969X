// To complete the VEXcode Pro V5 project upgrade process, please follow the
// steps below.
// 
// 1. You can use the Robot Configuration window to recreate your V5 devices
//   - including any motors, sensors, 3-wire devices, and controllers.
// 
// 2. All previous code located in main.cpp has now been commented out. You
//   will need to migrate this code to the new "int main" structure created
//   below and keep in mind any new device names you may have set from the
//   Robot Configuration window. 
// 
// If you would like to go back to your original project, a complete backup
// of your original (pre-upgraded) project was created in a backup folder
// inside of this project's folder.

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}

// /*----------------------------------------------------------------------------*/
// /*                                                                            */
// /*    Module:       main.cpp                                                  */
// /*    Author:       codycgee                                                  */
// /*    Created:      Sat Sep 14 2019                                           */
// /*    Description:  V5 project                                                */
// /*                                                                            */
// /*----------------------------------------------------------------------------*/
#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ---- END VEXCODE CONFIGURED DEVICES ----

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
// /*---------------------------------------------------------------------------*/
// /*                          Pre-Autonomous Functions                         */
// /*                                                                           */
// /*  You may want to perform some actions before the competition starts.      */
// /*  Do them in the following function.  You must return from this function   */
// /*  or the autonomous and usercontrol tasks will not be started.  This       */
// /*  function is only called once after the cortex has been powered on and    */
// /*  not every time that the robot is disabled.                               */
// /*---------------------------------------------------------------------------*/
// 
void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}
// 
// /*---------------------------------------------------------------------------*/
// /*                                                                           */
// /*                              Autonomous Task                              */
// /*                                                                           */
// /*  This task is used to control your robot during the autonomous phase of   */
// /*  a VEX Competition.                                                       */
// /*                                                                           */
// /*  You must modify the code to add your own robot specific commands here.   */
// /*---------------------------------------------------------------------------*/
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

void Intake (float time) {
    RIntake.spin(vex::directionType::fwd,100,velocityUnits::pct);
    LIntake.spin(vex::directionType::fwd,100,velocityUnits::pct);
    vex::task::sleep(time);
    RIntake.stop(brakeType::brake);
    LIntake.stop(brakeType::brake);
    
}

void Outtake (float time) {
    RIntake.spin(vex::directionType::rev,100,velocityUnits::pct);
    LIntake.spin(vex::directionType::rev,100,velocityUnits::pct);
    vex::task::sleep(time);
    RIntake.stop(brakeType::brake);
    LIntake.stop(brakeType::brake);

}

void fwdTilt (float time) {
    Tilter.spin(directionType::fwd,30,velocityUnits::pct);
    vex::task::sleep(time);
    Tilter.stop(brakeType::coast);
}

void revTilt (float rotations,float speed) {
    Tilter.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);

}

void fullTilt(){
    Tilter.rotateTo(2669,rotationUnits::raw,60,velocityUnits::pct);
}
    
void fullerTilt(float time){
  Tilter.spin(directionType::fwd,100,velocityUnits::pct);
  vex::task::sleep(time);
  Tilter.stop(brakeType::coast);
}

void halfTilt(){
    Tilter.rotateTo(550,rotationUnits::raw,100,velocityUnits::pct);
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
    TwoBar.stop(brakeType::brake);
    Tilter.stop(brakeType::coast);
    RIntake.stop(brakeType::brake);
    LIntake.stop(brakeType::brake);
}



void keepIntake () {
  RIntake.spin(directionType::fwd,100,velocityUnits::pct);
  LIntake.spin(directionType::fwd,100,velocityUnits::pct);
}

void stopIntake () {
  RIntake.stop(brakeType::coast);
  LIntake.stop(brakeType::coast);
  RIntake.spin(directionType::fwd,50,velocityUnits::pct);
  LIntake.spin(directionType::fwd,50,velocityUnits::pct);
  vex::task::sleep(300);
  RIntake.stop(brakeType::coast);
  LIntake.stop(brakeType::coast);

}

void keepOuttake () {
  RIntake.spin(directionType::rev,100,velocityUnits::pct);
  LIntake.spin(directionType::rev,100,velocityUnits::pct);
}

void stopOuttake () {
  RIntake.stop(brakeType::coast);
  LIntake.stop(brakeType::coast);

}
void forIntake (float rotations, float speed, float time) {
        FLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        FRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        RIntake.spin(directionType::fwd,100,velocityUnits::pct);
  LIntake.spin(directionType::fwd,100,velocityUnits::pct);
        vex::task::sleep(time);
        RIntake.stop(brakeType::coast);
        LIntake.stop(brakeType::coast);



}

void forTilt (float rotations, float speed, float time) {
  FLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        FRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        Tilter.spin(directionType::fwd,40,velocityUnits::pct);

        vex::task::sleep(time);
        Tilter.stop(brakeType::coast);

}

void backTilt (float rotations, float speed, float time) {
  FLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        FRWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        BRWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        Tilter.spin(directionType::rev,30,velocityUnits::pct);

        vex::task::sleep(time);
        Tilter.stop(brakeType::coast);

}

void autonomous( void ) {
//Parameters: rotations, speed
//Example: function(rotations,speed);
    presetBrake();
    fullerTilt(900);
    Outtake(450);
    unTilt();

    


    
    
    keepIntake();
    moveForward(1.625,60);
    moveForward(2.23,20);
    moveBackward(2.28,60);
    stopIntake();
    turnLeft(0.73,60);
    

    vex::task::sleep(200);
    forIntake(1.25,50,1000);
     
     vex::task::sleep(300);
     turnLeft(0.19,30);
     forTilt(1,60,1600);
    fwdTilt(1350);
    vex::task::sleep(50);
    backTilt(1,30,1000);


}

// /*----------------------------------------------------------------------------*/
// /*                                                                            */
// /*                              User Control Task                             */
// /*                                                                            */
// /*  This task is used to control your robot during the user control phase of  */
// /*  a VEX Competition.                                                        */
// /*                                                                            */
// /*  You must modify the code to add your own robot specific commands here.    */
// /*----------------------------------------------------------------------------*/

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
            RIntake.spin(directionType::fwd,2,velocityUnits::pct);
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
          
      
      if (Controller1.ButtonUp.pressing()){
           Tilter.rotateTo(0.731,rotationUnits::rev,100,velocityUnits::pct);
           Tilter.rotateTo(2700,rotationUnits::raw,20,velocityUnits::pct);
           
           
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
     
      if (Controller1.ButtonRight.pressing()) {
            if(Controller1.ButtonL1.pressing()) {
              halfTilt();
              TwoBar.rotateTo(1.565,rotationUnits::rev,100,velocityUnits::pct);
            }
      }

      if (Controller1.ButtonDown.pressing()) {
            if(Controller1.ButtonL1.pressing()) {
              halfTilt();
              TwoBar.rotateTo(01.142,rotationUnits::rev,100,velocityUnits::pct);
            }
      }

      if(Controller1.ButtonA.pressing()) {
       TwoBar.stop(brakeType::brake);
    Tilter.stop(brakeType::coast);
    RIntake.stop(brakeType::brake);
    LIntake.stop(brakeType::brake);
    FLWheel.stop(brakeType::brake);
    FRWheel.stop(brakeType::brake);
    BLWheel.stop(brakeType::brake);
    BRWheel.stop(brakeType::brake);
        
      }

      if(Controller1.ButtonB.pressing()) {
  
    FLWheel.stop(brakeType::coast);
    FRWheel.stop(brakeType::coast);
    BLWheel.stop(brakeType::coast);
    BRWheel.stop(brakeType::coast);
      }
      if(Controller1.ButtonY.pressing()) {
  
    FLWheel.stop(brakeType::brake);
    FRWheel.stop(brakeType::brake);
    BLWheel.stop(brakeType::brake);
    BRWheel.stop(brakeType::brake);
      }
      if(Controller1.ButtonX.pressing()) {
  
    FLWheel.stop(brakeType::hold);
    FRWheel.stop(brakeType::hold);
    BLWheel.stop(brakeType::hold);
    BRWheel.stop(brakeType::hold);
      }
    

      //2700,rotationUnits::raw,20,velocityUnits::pct
       
      
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


