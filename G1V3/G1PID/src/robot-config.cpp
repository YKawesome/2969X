#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor L1 = motor(PORT6, ratio18_1, false);
motor L2 = motor(PORT15, ratio18_1, true);
motor L3 = motor(PORT16, ratio18_1, false);
motor R1 = motor(PORT5, ratio18_1, true);
motor R2 = motor(PORT17, ratio18_1, false);
motor R3 = motor(PORT4, ratio18_1, true);
motor_group RightDrive = motor_group(R1, R2, R3);
motor_group LeftDrive = motor_group(L1, L2, L3);
motor_group Drivetrain = motor_group(R1, R2, R3, L1, L2, L3);
controller Controller;
inertial IMU = inertial(PORT2);


// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}