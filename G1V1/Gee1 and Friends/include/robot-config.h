using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FLWheel;
extern motor FRWheel;
extern motor BRWheel;
extern motor BLWheel;
extern motor Tilter;
extern motor TwoBar;
extern motor RIntake;
extern motor LIntake;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );