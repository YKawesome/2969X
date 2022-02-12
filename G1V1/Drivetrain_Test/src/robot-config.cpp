#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FRWheel = motor(PORT15, ratio18_1, true);
motor FLWheel = motor(PORT17, ratio18_1, false);
motor BRWheel = motor(PORT14, ratio18_1, true);
motor BLWheel = motor(PORT13, ratio18_1, false);
motor LIntake = motor(PORT6, ratio18_1, false);
controller Controller1 = controller(primary);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}