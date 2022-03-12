using namespace vex;

extern brain Brain;

// VEXcode devices
// extern drivetrain Drivetrain;
extern motor L1;
extern motor L2;
extern motor L3;
extern motor R1;
extern motor R2;
extern motor R3;
extern controller Controller1;
extern motor Mogo;
extern motor FBar1;

extern motor MogoClamp;
extern pneumatics PPmachine;
extern pneumatics Pclamp;
extern inertial IMU;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );