#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor Motor4 = motor(PORT4, ratio18_1, false);
controller Controller1 = controller(primary);
pneumatics Pmachine1 = pneumatics(Brain.ThreeWirePort.A);
// extern pneumatics Pmachine1;
pneumatics Pmachine2 = pneumatics(Brain.ThreeWirePort.B);
//  while (1) {
//     if (Controller1.ButtonA.pressing()) {
//       Pmachine1.open();
//       Pmachine2.open();
//     }
//     else{
//       Pmachine1.close();
//       Pmachine2.close();
//     }
// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}