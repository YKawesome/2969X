using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Tilter;
extern motor RIntake;
extern motor LIntake;
extern controller Controller1;
extern smartdrive Drivetrain;
extern motor LLift;
extern motor RLift;
extern motor Strafe;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );