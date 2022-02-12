#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FBar = motor(PORT14, ratio36_1, false);
motor CBar = motor(PORT13, ratio36_1, false);
motor Intake = motor(PORT16, ratio18_1, false);
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);




/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
