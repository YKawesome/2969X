/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// L1                   motor         1               
// L2                   motor         2               
// L3                   motor         3               
// R1                   motor         4               
// R2                   motor         5               
// R3                   motor         6               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  vexcodeInit();

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
void drivePIDbetter(float target) {
  float lKp = 60;
  float lKi = 5;
  float lKd = 0;
  float rKp = 60;
  float rKi = 0.7;
  float rKd = 1;
  // bool notdone = true;

  R1.setPosition(0, rotationUnits::rev);
  R2.setPosition(0, rotationUnits::rev);
  R3.setPosition(0, rotationUnits::rev);
  L1.setPosition(0, rotationUnits::rev);
  L2.setPosition(0, rotationUnits::rev);
  L3.setPosition(0, rotationUnits::rev);
  float lreading = 0;
  float rreading = 0;
  
  float lintegral = 0;
  float rintegral = 0;
  float integralLimit = 200;
  float lderivative = 0;
  float rderivative = 0;
  float lprevious_error = target;
  float rprevious_error = target;
  float lerror;
  float rerror;
  float error;
  float lpidspeed = 0;
  float rpidspeed = 0;

  bool startedcounting = false;
  int count = 0;
  while (true) {
  //Proportion
  lreading = L1.position(rotationUnits::rev);
  rreading = R1.position(rotationUnits::rev);
  
  lerror = target - lreading;
  rerror = target - rreading;

  // printf("reading: %f, error: %f\n",reading,error);

  //Integral
  lintegral = lintegral + lerror;
  rintegral = rintegral + rerror;
  
  if (rerror == 0){
  rintegral = 0;
  }
  if (lerror == 0){
    lintegral = 0;
  }

  if ( fabs(lerror) > integralLimit){
  lintegral = 0;
  }
  if ( fabs(rerror) > integralLimit){
  rintegral = 0;
  }

  //Derivative
  lderivative = lerror - lprevious_error;
  lprevious_error = lerror;
  rderivative = rerror - rprevious_error;
  rprevious_error = rerror;

  
  lpidspeed = lKp*lerror + lKi*lintegral + lKd*lderivative;
  rpidspeed = rKp*rerror + rKi*rintegral + rKd*rderivative;
  // pidspeed=20;

  L1.spin(fwd, lpidspeed, velocityUnits::pct);
  L2.spin(fwd, lpidspeed, velocityUnits::pct);
  L3.spin(fwd, lpidspeed, velocityUnits::pct);
  R1.spin(fwd, rpidspeed, velocityUnits::pct);
  R2.spin(fwd, rpidspeed, velocityUnits::pct);
  R3.spin(fwd, rpidspeed, velocityUnits::pct);
  error = (lerror+rerror)/2;
  if(fabs(error)<0.05) {
    count++;
  }
  if(count>=1) {
    break;
  }

  else {
    startedcounting = false;
  }

  vex::task::sleep(20);

  }

  L1.stop(brake);
  L2.stop(brake);
  L3.stop(brake);
  R1.stop(brake);
  R2.stop(brake);
  R3.stop(brake);

}


void drivePIDbad(float error) {
  float Kp = 0.8;
  float Ki = 0.0;
  float Kd = 0.0;
  // bool notdone = true;

  R1.setPosition(0, rotationUnits::rev);
  R2.setPosition(0, rotationUnits::rev);
  R3.setPosition(0, rotationUnits::rev);
  L1.setPosition(0, rotationUnits::rev);
  L2.setPosition(0, rotationUnits::rev);
  L3.setPosition(0, rotationUnits::rev);
  float reading = 0;
  
  float integral = 0;
  float integralLimit = 40;
  float derivative = 0;
  float previous_error = error;

  float pidspeed = 0;

  bool startedcounting = false;
  int count = 0;
  while (true) {
  //Proportion
  reading = (L1.position(rotationUnits::rev)+R1.position(rotationUnits::rev))/2;
  
  error = error - reading;

  printf("%f\n",error);

  //Integral
  integral = integral + error;
  if (error == 0){
  integral = 0;
  }

  if ( fabs(error) > integralLimit){
  integral = 0;
  }

  //Derivative
  derivative = error - previous_error;
  previous_error = error;

  
  pidspeed = Kp*error + Ki*integral + Kd*derivative;
  // pidspeed=20;

  L1.spin(fwd, pidspeed, velocityUnits::pct);
  L2.spin(fwd, pidspeed, velocityUnits::pct);
  L3.spin(fwd, pidspeed, velocityUnits::pct);
  R1.spin(fwd, pidspeed, velocityUnits::pct);
  R2.spin(fwd, pidspeed, velocityUnits::pct);
  R3.spin(fwd, pidspeed, velocityUnits::pct);
  
  if(fabs(error)<3) {
    count++;
  }
  if(count>=1) {
    break;
  }

  else {
    startedcounting = false;
  }

  vex::task::sleep(20);

  }

  L1.stop(brake);
  L2.stop(brake);
  L3.stop(brake);
  R1.stop(brake);
  R2.stop(brake);
  R3.stop(brake);

}


void drivePID(float target) {
  float Kp = 60;
  float Ki = 0.7;
  float Kd = 1;
  // bool notdone = true;

  R1.setPosition(0, rotationUnits::rev);
  R2.setPosition(0, rotationUnits::rev);
  R3.setPosition(0, rotationUnits::rev);
  L1.setPosition(0, rotationUnits::rev);
  L2.setPosition(0, rotationUnits::rev);
  L3.setPosition(0, rotationUnits::rev);
  float reading = 0;
  
  float integral = 0;
  float integralLimit = 40;
  float derivative = 0;
  float previous_error = target;
  float error;
  float pidspeed = 0;

  bool startedcounting = false;
  int count = 0;
  while (true) {
  //Proportion
  reading = (L1.position(rotationUnits::rev)+R1.position(rotationUnits::rev))/2;
  
  error = target - reading;

  printf("reading: %f, error: %f\n",reading,error);

  //Integral
  integral = integral + error;
  if (error == 0){
  integral = 0;
  }

  if ( fabs(error) > integralLimit){
  integral = 0;
  }

  //Derivative
  derivative = error - previous_error;
  previous_error = error;

  
  pidspeed = Kp*error + Ki*integral + Kd*derivative;
  // pidspeed=20;

  L1.spin(fwd, pidspeed, velocityUnits::pct);
  L2.spin(fwd, pidspeed, velocityUnits::pct);
  L3.spin(fwd, pidspeed, velocityUnits::pct);
  R1.spin(fwd, pidspeed, velocityUnits::pct);
  R2.spin(fwd, pidspeed, velocityUnits::pct);
  R3.spin(fwd, pidspeed, velocityUnits::pct);
  
  if(fabs(error)<0.05) {
    count++;
  }
  if(count>=1) {
    break;
  }

  else {
    startedcounting = false;
  }

  vex::task::sleep(20);

  }

  L1.stop(brake);
  L2.stop(brake);
  L3.stop(brake);
  R1.stop(brake);
  R2.stop(brake);
  R3.stop(brake);

}

void turnPID(float target) {
  float Kp = 0.75;
  float Ki = 0.006;
  float Kd = 0.0;
  // bool notdone = true;

  IMU.resetHeading();
  IMU.resetRotation();
  float reading = 0;
  
  float integral = 0;
  float integralLimit = 40;
  float derivative = 0;
  float previous_error = target;

  float pidspeed = 0;
  float error;
  bool startedcounting = false;
  int count = 0;
  while (true) {
  //Proportion
  reading = IMU.heading(degrees);
  if (fabs(reading)>350) {
    reading = -(360-fabs(reading));
    printf("%s","sadge");
  }
  error = target - reading;

  printf("reading: %f, error: %f\n",reading,error);

  //Integral
  integral = integral + error;
  if (error == 0){
  integral = 0;
  }

  if ( fabs(error) > integralLimit){
  integral = 0;
  }

  //Derivative
  derivative = error - previous_error;
  previous_error = error;

  
  pidspeed = Kp*error + Ki*integral + Kd*derivative;
  // pidspeed=10;

  L1.spin(fwd, pidspeed, velocityUnits::pct);
  L2.spin(fwd, pidspeed, velocityUnits::pct);
  L3.spin(fwd, pidspeed, velocityUnits::pct);
  R1.spin(fwd, -pidspeed, velocityUnits::pct);
  R2.spin(fwd, -pidspeed, velocityUnits::pct);
  R3.spin(fwd, -pidspeed, velocityUnits::pct);
  
  if(fabs(error)<2) {
    count++;
  }
  if(count>=2) {
    break;
  }

  else {
    startedcounting = false;
  }

  vex::task::sleep(10);

  }

  L1.stop(brake);
  L2.stop(brake);
  L3.stop(brake);
  R1.stop(brake);
  R2.stop(brake);
  R3.stop(brake);

}



void autonomous(void) {
  // 113 is 2 tiles
  // 56 is a tile
  // 4.3/3 is 1 tile
  // 2.6 is 2 tiles
  // 4.0 is 3 tiles
  // drivePID(4);
  // vex::task::sleep(100);
  // drivePID(-2.6);
  // vex::task::sleep(100);
  // drivePID(4.3/3);
  // vex::task::sleep(100);
  IMU.startCalibration(); 
  waitUntil(IMU.isCalibrating()==false);

  turnPID(90);
  Controller.rumble(". . .");
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.


  if(Controller.ButtonA.pressing()) {
    R1.spin(fwd,100,velocityUnits::pct);
    R2.spin(fwd,100,velocityUnits::pct);
    R3.spin(fwd,100,velocityUnits::pct);
  }
  else {
    R1.stop(brake);
    R2.stop(brake);
    R3.stop(brake);
  }










  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
