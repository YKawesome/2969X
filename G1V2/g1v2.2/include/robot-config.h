using namespace vex;

extern brain Brain;

// VEXcode devices
extern smartdrive Drivetrain;
extern motor FBar;
extern motor CBar;
extern motor Mogo;
extern motor Intake;
extern controller Controller1;
extern controller Controller2;
extern pneumatics PMachine1;
extern pneumatics PMachine2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );