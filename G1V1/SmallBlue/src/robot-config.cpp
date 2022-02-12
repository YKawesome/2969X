#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FLWheel = motor(PORT11, ratio18_1, false);
controller Controller1 = controller(primary);
motor FRWheel = motor(PORT2, ratio18_1, true);
motor BLWheel = motor(PORT3, ratio18_1, false);
motor BRWheel = motor(PORT4, ratio18_1, true);
motor Tilter = motor(PORT5, ratio36_1, true);
motor TwoBar = motor(PORT6, ratio18_1, false);
motor LIntake = motor(PORT12, ratio18_1, false);
motor RIntake = motor(PORT8, ratio18_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}