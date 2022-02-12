/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    6, 7, 2, 3, 19  
// FBar                 motor         14              
// CBar                 motor         13              
// Mogo                 motor         11              
// Intake               motor         16              
// Controller1          controller                    
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.h"
// #include "robot-config.cpp"
using namespace vex;






// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

motor leftMotorA = motor(PORT6, ratio18_1, false);
motor leftMotorB = motor(PORT5, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT2, ratio18_1, true);
motor rightMotorB = motor(PORT3, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
inertial TurnGyroSmart = inertial(PORT19);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, TurnGyroSmart, 319.19, 320, 40, mm, 1);
motor Mogo = motor(PORT11, ratio36_1, false);
pneumatics Pmachine1 = pneumatics(Brain.ThreeWirePort.A);
pneumatics Pmachine2 = pneumatics(Brain.ThreeWirePort.B);


int   autonomousSelection = -1;

typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *label;
} button;


button buttons[] = {
    {   30,  30, 60, 60,  false, 0x303030, 0xFF0000, "Red" },
    {  150,  30, 60, 60,  false, 0x303030, 0x0000FF, "Blue" },
    {  270,  30, 60, 60,  false, 0x303030, 0xF700FF, "Desperation" },
    {  390,  30, 60, 60,  false, 0x303030, 0xDDDD00, "3-" },
    {   30, 150, 60, 60,  false, 0x404040, 0xffff00, "Big" },
    {  150, 150, 60, 60,  false, 0x404040, 0xffff00, "Small" },
    {  270, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "6-" },
    {  390, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "7-" }
};

//AUTON SELECTOR ORGANIZE
  void displayButtonControls( int index, bool pressed );

  /*-----------------------------------------------------------------------------*/
  /** @brief      Check if touch is inside button                                */
  /*-----------------------------------------------------------------------------*/
  int
  findButton(  int16_t xpos, int16_t ypos ) {
      int nButtons = sizeof(buttons) / sizeof(button);

      for( int index=0;index < nButtons;index++) {
        button *pButton = &buttons[ index ];
        if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
          continue;

        if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
          continue;

        return(index);
      }
      return (-1);
  }

  /*-----------------------------------------------------------------------------*/
  /** @brief      Init button states                                             */
  /*-----------------------------------------------------------------------------*/
  void
  initButtons() {
      int nButtons = sizeof(buttons) / sizeof(button);

      for( int index=0;index < nButtons;index++) {
        buttons[index].state = false;
      }
  }

  /*-----------------------------------------------------------------------------*/
  /** @brief      Screen has been touched                                        */
  /*-----------------------------------------------------------------------------*/
  void
  userTouchCallbackPressed() {
      int index;
      int xpos = Brain.Screen.xPosition();
      int ypos = Brain.Screen.yPosition();

      if( (index = findButton( xpos, ypos )) >= 0 ) {
        displayButtonControls( index, true );
      }

  }

  /*-----------------------------------------------------------------------------*/
  /** @brief      Screen has been (un)touched                                    */
  /*-----------------------------------------------------------------------------*/
  void
  userTouchCallbackReleased() {
      int index;
      int xpos = Brain.Screen.xPosition();
      int ypos = Brain.Screen.yPosition();

      if( (index = findButton( xpos, ypos )) >= 0 ) {
        // clear all buttons to false, ie. unselected
        //      initButtons(); 

        // now set this one as true
        if( buttons[index].state == true) {
        buttons[index].state = false; }
        else    {
        buttons[index].state = true;}

        // save as auton selection
        autonomousSelection = index;

        displayButtonControls( index, false );
      }
  }

  /*-----------------------------------------------------------------------------*/
  /** @brief      Draw all buttons                                               */
  /*-----------------------------------------------------------------------------*/
  void
  displayButtonControls( int index, bool pressed ) {
      vex::color c;
      Brain.Screen.setPenColor( vex::color(0xe0e0e0) );

      for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {

        if( buttons[i].state )
          c = buttons[i].onColor;
        else
          c = buttons[i].offColor;

        Brain.Screen.setFillColor( c );

        // button fill
        if( i == index && pressed == true ) {
          Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c );
        }
        else
          Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

        // outline
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, vex::color::transparent );

  // draw label
        if(  buttons[i].label != NULL )
          Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].label );
      }
  }


//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            FUNCTION Declarations                          */
/*                                                                           */
/*  Declare functions here to be used in User Control or Autonomous during   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void move(float left, float right) {
  LeftDriveSmart.spin(forward,left,vex::velocityUnits::pct);
  RightDriveSmart.spin(forward,right,vex::velocityUnits::pct);
}

void moveForward(float tiles,float speed) { //This is to move forward.
        Drivetrain.driveFor( (tiles), inches, speed, velocityUnits::pct);
}

void moveBackward(float tiles,float speed) { //This is to move backward.
        Drivetrain.driveFor( -(tiles), inches, speed, velocityUnits::pct);
}

void turnRight(float dees,float speed) { //This is to turn right.
        Drivetrain.turnFor( (dees), degrees, speed, velocityUnits::pct);
}

void turnLeft(float dees,float speed) { //This is to turn left.
        Drivetrain.turnFor( -(dees), degrees, speed, velocityUnits::pct);
}


bool held = false;
void chassisHold() {
  Drivetrain.setStopping(hold);
  Controller1.rumble(". . .");
  held = true;
}
void chassisCoast() {
  Drivetrain.setStopping(coast);
  Controller1.rumble("   ");
  held = false;
}














void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  /* initialize capabilities from buttons */
   //Booleans
     bool Red = buttons[0].state;
     bool Blue = buttons[1].state;
     bool Desperation = buttons[2].state;
     bool Big = buttons[4].state;
     bool Small = buttons[5].state;
   //
    CBar.setRotation(0,degrees);
    CBar.setVelocity(90,percent);
    CBar.rotateFor(forward,340*3,degrees);
    CBar.setBrake(hold);
 
     if(Red == true){

        if(Big == true) { 
           
        } 

        if(Small == true) {
          
        } 

    }

    if(Blue == true) {

        if(Big == true) { 
        } 

        if(Small == true) { 
        } 

    }

    if (Desperation == true) {
   
    }

    

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  Drivetrain.setStopping(coast);
  while (1) {
    // Drivetrain.setStopping(coast);


    //FourBar
    int FBarSpeed = Controller2.Axis3.position();
    
    if (FBarSpeed < 3 && FBarSpeed > -3) {
      FBar.stop(brakeType::brake);
    }
    else {
      FBar.spin(directionType::fwd,FBarSpeed,velocityUnits::pct);
    }


    //ChainBar
    int CBarSpeed = Controller2.Axis2.position();
    
    if (CBarSpeed < 3 && CBarSpeed > -3) {
      CBar.stop(brakeType::brake);
    }
    else {
      CBar.spin(directionType::fwd,CBarSpeed,velocityUnits::pct);
    }

    //Mogo
    if (Controller1.ButtonR1.pressing()) {
      Mogo.spin(directionType::fwd,100,velocityUnits::pct);
    }
    else if (Controller1.ButtonL1.pressing()) {
      Mogo.spin(directionType::rev,100,velocityUnits::pct);
    }
    else {
      Mogo.stop(brakeType::brake);
    }

    //Intake
    if (Controller2.ButtonR1.pressing()) {
      Intake.spin(directionType::fwd,100,velocityUnits::pct);
    }
    else if (Controller2.ButtonL1.pressing()) {
      Intake.spin(directionType::rev,100,velocityUnits::pct);
    }
    else {
      Intake.stop(brakeType::brake);
    }


    if (Controller1.ButtonA.pressing()) {
      Pmachine1.open();
      Pmachine2.open();
    }
    else {
      Pmachine1.close();
      Pmachine2.close();
    }


    float left = Controller1.Axis2.position() + Controller1.Axis4.position();
    float right = Controller1.Axis2.position() - Controller1.Axis4.position();
    move(left,right);

























  }
}



void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}




// Main will set up the competition functions and callbacks.
int main() {
 // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  //Run the pre-autonomous function. 
  pre_auton();

  //Set up callbacks for autonomous and driver control periods.
  Competition.autonomous( autonomous );
  Competition.drivercontrol( usercontrol );

  // register events for button selection
  Brain.Screen.pressed( userTouchCallbackPressed );
  Brain.Screen.released( userTouchCallbackReleased );

  // make nice background
  Brain.Screen.setFillColor( vex::color(0x404040) );
  Brain.Screen.setPenColor( vex::color(0x404040) );
  Brain.Screen.drawRectangle( 0, 0, 480, 120 );
  Brain.Screen.setFillColor( vex::color(0x808080) );
  Brain.Screen.setPenColor( vex::color(0x808080) );
  Brain.Screen.drawRectangle( 0, 120, 480, 120 );

  // initial display
  displayButtonControls( 0, false );

  while(1) {
      // Allow other tasks to run
      if( !Competition.isEnabled() )
          Brain.Screen.setFont(fontType::mono40);
      Brain.Screen.setFillColor( vex::color(0xFFFFFF) );

      Brain.Screen.setPenColor( vex::color(0xc11f27));
      Brain.Screen.printAt( 0,  135, "      G1    Robotics    " );
      this_thread::sleep_for(10);
  }
}

