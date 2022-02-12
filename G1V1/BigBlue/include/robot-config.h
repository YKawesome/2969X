using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor FLWheel;
extern controller Controller1;
extern motor FRWheel;
extern motor BLWheel;
extern motor BRWheel;
extern motor Tilter;
extern motor TwoBar;
extern motor LIntake;
extern motor RIntake;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );