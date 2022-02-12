/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       yousef                                                    */
/*    Created:      Sun Dec 08 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FRWheel              motor         15              
// FLWheel              motor         17              
// BRWheel              motor         14              
// BLWheel              motor         13              
// LIntake              motor         6               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

vex::competition    Competition;

motor_group   leftDrive( FLWheel, BLWheel );

motor_group   rightDrive( FRWheel, BRWheel );

drivetrain    robotDrive( leftDrive, rightDrive, 12.56, 12, 12, distanceUnits::in );

void autonomous( void ) {
  
}

void usercontrol( void ) {
  while(1) {
    if (Controller1.ButtonL2.pressing()) {
            robotDrive.driveFor( 24, inches );
      }
    vex::task::sleep(20);
  }
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //Run the pre-autonomous function. 


    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );
    
}
