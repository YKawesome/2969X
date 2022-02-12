using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Launcher;
extern motor Roller;
extern motor LIntake;
extern motor RIntake;
extern smartdrive Drivetrain;
extern encoder LENC;
extern encoder RENC;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );