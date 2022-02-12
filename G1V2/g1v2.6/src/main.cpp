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
// Drivetrain           drivetrain    6, 16, 4, 5, 2  
// Controller1          controller                    
// Mogo                 motor         3               
// FBar1                motor         14              
// FBar2                motor         15              
// MogoClamp            motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

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
    {   30,  30, 60, 60,  false, 0x303030, 0xFF0000, "Left" },
    {  150,  30, 60, 60,  false, 0x303030, 0x0000FF, "Right" },
    {  270,  30, 60, 60,  false, 0x303030, 0xF700FF, "Desperation" },
    {  390,  30, 60, 60,  false, 0x303030, 0xDDDD00, "3-" },
    {   30, 150, 60, 60,  false, 0x404040, 0xffff00, "Piston" },
    {  150, 150, 60, 60,  false, 0x404040, 0xffff00, "Clamp" },
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

// void move(float left, float right) {
//   LeftDriveSmart.spin(forward,left,vex::velocityUnits::pct);
//   RightDriveSmart.spin(forward,right,vex::velocityUnits::pct);
// }

void moveForward(float tiles,float speed) { //This is to move forward.
        Drivetrain.driveFor(-(tiles)*24, inches, speed, velocityUnits::pct);
        Drivetrain.stop(coast);
}

void moveBackward(float tiles,float speed) { //This is to move backward.
        Drivetrain.driveFor( (tiles)*24, inches, speed, velocityUnits::pct);
        Drivetrain.stop(coast);
}

void turnRight(float dees,float speed) { //This is to turn right.
        // Drivetrain.turnFor( (dees), degrees, speed, velocityUnits::pct);
        // // vex::task::sleep(500);
        // Drivetrain.stop(coast);

        // Drivetrain.setHeading(0, degrees);
        // Drivetrain.turnToHeading(dees,degrees, speed, velocityUnits::pct);
        // Drivetrain.stop(coast);
        Drivetrain.setRotation(0, degrees);
        Drivetrain.turnToRotation(dees, degrees, speed, velocityUnits::pct);
}

void turnLeft(float dees,float speed) { //This is to turn left.
        // Drivetrain.turnFor( -(dees), degrees, speed, velocityUnits::pct);
        // // vex::task::sleep(500);
        // Drivetrain.stop(coast);

        // Drivetrain.setHeading(0, degrees);
        // Drivetrain.turnToHeading(dees,degrees, speed, velocityUnits::pct);
        // Drivetrain.stop(coast);

        Drivetrain.turnToRotation(-(dees), degrees, speed, velocityUnits::pct);
}

void mogo_clamp(float dees) {
  MogoClamp.rotateTo(dees,degrees,100,velocityUnits::pct);
}
void mogo_unclamp() {
  MogoClamp.rotateTo(0,degrees,100,velocityUnits::pct);
}
void mogo_down() {
  Mogo.rotateTo(-100,degrees,100,velocityUnits::pct);
}
void mogo_up() {
  Mogo.rotateTo(0,degrees,100,velocityUnits::pct);
}
void lift_up(float dees) {
  FBar1.rotateTo(dees,degrees,100,velocityUnits::pct,false);
  FBar2.rotateTo(dees,degrees,100,velocityUnits::pct);
}
void lift_down(float dees) {
  FBar1.rotateFor(-(dees),degrees,100,velocityUnits::pct,false);
  FBar2.rotateFor(-(dees),degrees,100,velocityUnits::pct);
}
void pmachineopen() {
  Pmachine.open();
  vex::task::sleep(100);
}

void pmachineclose() {
  Pmachine.close();
  vex::task::sleep(100);
}
// bool held = false;
// void chassisHold() {
//   Drivetrain.setStopping(hold);
//   Controller1.rumble(". . .");
//   // held = true;
// }
// void chassisCoast() {
//   Drivetrain.setStopping(coast);
//   Controller1.rumble("   ");
//   // held = false;
// }

// void thend() {
//   while(true) {
//     if (chassis_is_held == true) {
//       Mogo.spin(fwd, 5, velocityUnits::pct);
//     }
//   }
// }








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
  bool Left = buttons[0].state;
  bool Right = buttons[1].state;
  bool Desperation = buttons[2].state;
  bool Piston = buttons[4].state;
  bool Clamp = buttons[5].state;
  
  

  
    if(Left == true){

        if(Piston == true) { 
           
        } 

        if(Clamp == true) {
            MogoClamp.setRotation(0, degrees);
            Mogo.setRotation(0, degrees);
            MogoClamp.setStopping(hold);
            Mogo.setStopping(hold);
            Drivetrain.setStopping(coast);
            FBar1.setStopping(hold);
            FBar2.setStopping(hold);
            moveBackward(1.42,100);
            moveBackward(0.55,80);
            mogo_clamp(110);
            vex::task::sleep(500);
            moveForward(1.2,100);
            mogo_unclamp();
            moveForward(0.4,60);
        } 

    }

    if(Right == true) {

        if(Piston == true) { 
          pmachineopen();
          Drivetrain.setStopping(coast);
          // moveForward(1,45);
          moveForward(1.92,65);
          vex::task::sleep(500);
          pmachineclose();
          vex::task::sleep(200);
          moveBackward(1.2,45);
          pmachineopen();
          moveBackward(0.6,45);
          vex::task::sleep(200);
          turnLeft(124,45);
          vex::task::sleep(300);
          lift_up(90);
          moveBackward(0.825,45);
          MogoClamp.setRotation(110, degrees);
          mogo_unclamp();
          lift_down(105);
          moveBackward(0.3,45);
          mogo_clamp(105);
          vex::task::sleep(200);
          turnRight(100,45);
          mogo_unclamp();
          moveBackward(0.5,45);



        } 

        if(Clamp == true) { 
          MogoClamp.setRotation(0, degrees);
          Mogo.setRotation(0, degrees);
          MogoClamp.setStopping(hold);
          Mogo.setStopping(hold);
          Drivetrain.setStopping(coast);
          FBar1.setStopping(hold);
          FBar2.setStopping(hold);
          moveBackward(1.42,100);
          moveBackward(0.54,70);
          mogo_clamp(110);
          vex::task::sleep(750);
          moveForward(1.2,100);
          mogo_unclamp();
          moveForward(0.6,60);
        } 

    }

    if (Desperation == true) {
        lift_up(90);
        MogoClamp.setRotation(110, degrees);
        mogo_unclamp();
        moveForward(0.3,45);
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
bool chassis_is_held = false;
bool pneumatics_is_held = true;
bool mogobool = true;
void usercontrol(void) {
  Drivetrain.setStopping(coast);
  // FBar.setStopping(brake);
  MogoClamp.setStopping(hold);
  Mogo.setStopping(hold);
  Pmachine.open();
  // thread end_sequence(thend);
  while (1) {
    

    //FourBar
    if (Controller1.ButtonR1.pressing()) {
      FBar1.spin(directionType::fwd,100,velocityUnits::pct);
      FBar2.spin(directionType::fwd,100,velocityUnits::pct);
    }
    else if (Controller1.ButtonL1.pressing()) {
      FBar1.spin(directionType::rev,100,velocityUnits::pct);
      FBar2.spin(directionType::rev,100,velocityUnits::pct);
    }
    else {
      FBar1.stop(brakeType::brake);
      FBar2.stop(brakeType::brake);
    }    


 

    //Mogo
    // if (Controller1.ButtonX.pressing()) {
    //   Mogo.spin(directionType::fwd,100,velocityUnits::pct);
    // }
    // else if (Controller1.ButtonA.pressing()) {
    //   Mogo.spin(directionType::rev,100,velocityUnits::pct);
    // }
    // else {
    //   Mogo.stop(brakeType::hold);
    // }


    if (Controller1.ButtonX.pressing() and mogobool==false) {
      mogobool=true;
      Mogo.spinFor(directionType::fwd, 370, degrees, 100, velocityUnits::pct);
      Mogo.stop(brakeType::hold);
      vex::task::sleep(500);
    }
    
    if (Controller1.ButtonA.pressing() and mogobool==true) {
      mogobool=false;
      Pmachine.close();
      Mogo.spinFor(directionType::rev, 370, degrees, 100, velocityUnits::pct);
      Pmachine.open();
      Mogo.stop(brakeType::hold);
      vex::task::sleep(500);
    }



    //MogoClamp
    if (Controller1.ButtonR2.pressing()) {
      MogoClamp.spin(directionType::fwd,100,velocityUnits::pct);
    }
    else if (Controller1.ButtonL2.pressing()) {
      MogoClamp.spin(directionType::rev,100,velocityUnits::pct);
    }
    else {
      MogoClamp.stop(brakeType::hold);
    }

    



    //Pneumatics
    if (Controller1.ButtonUp.pressing() and pneumatics_is_held==true) {
      Pmachine.close();
      pneumatics_is_held=false;
      vex::task::sleep(500);
    }
    else if (Controller1.ButtonUp.pressing() and pneumatics_is_held==false) {
      Pmachine.open();
      pneumatics_is_held=true;
      vex::task::sleep(500);
    } 
    // if (Controller1.ButtonUp.pressing()) {
    //   Pmachine.close();

    // }
    // else{
    //   Pmachine.open();
    // }


    //Legacy of Partner Drive
    // float left = -(Controller1.Axis2.position() - Controller1.Axis4.position());
    // float right = -(Controller1.Axis2.position() + Controller1.Axis4.position());
    // move(left,right);

    // if (Controller1.ButtonA.pressing()) {
    //   Pmachine1.open();
    //   Pmachine2.open();
    // }
    // else{
    //   Pmachine1.close();
    //   Pmachine2.close();
    // }

    if (chassis_is_held == true) {
      Controller1.rumble("...");
      Mogo.spin(fwd, 5, velocityUnits::pct);
    }
    else {
      Controller1.rumble("   ");
      Mogo.stop(hold);
    }

    if (Controller1.ButtonRight.pressing() and chassis_is_held==true) {
      Drivetrain.setStopping(coast);
      chassis_is_held=false;
      // thend();
      vex::task::sleep(500);
    }
    else if (Controller1.ButtonRight.pressing() and chassis_is_held==false) {
      Drivetrain.setStopping(hold);
      chassis_is_held=true;
      vex::task::sleep(500);
    } 

    // }
    























  }
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

