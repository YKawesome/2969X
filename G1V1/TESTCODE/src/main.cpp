/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       yousef                                                    */
/*    Created:      Sun Nov 10 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Tilter               motor         8               
// RIntake              motor         11              
// LIntake              motor         13              
// Controller1          controller                    
// Drivetrain           drivetrain    2, 3, 20        
// LLift                motor         5               
// RLift                motor         6               
// Strafe               motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.h"
#include <iostream>

using namespace vex;


vex::competition    Competition;



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


//ORGANIZE
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

void pre_auton( void ) {
    // All activities that occur before the competition starts
    // Example: clearing encoders, setting servo positions, ...

}
//

//Functions
    
    
    void moveForward(float tiles,float speed) { //This is to move forward.
            Drivetrain.driveFor( -(tiles * 27.5), inches, speed, velocityUnits::pct);
    }

    void moveBackward(float tiles,float speed) { //This is to move backward.
            Drivetrain.driveFor( (tiles * 27.5), inches, speed, velocityUnits::pct);
    }

    void turnRight(float dees,float speed) { //This is to turn right.
            Drivetrain.turnFor( (dees), degrees, speed, velocityUnits::pct);
    }

    void turnLeft(float dees,float speed) { //This is to turn left.
            Drivetrain.turnFor( -(dees), degrees, speed, velocityUnits::pct);
    }

    void Intake (float time) {
        RIntake.spin(vex::directionType::fwd,100,velocityUnits::pct);
        LIntake.spin(vex::directionType::fwd,100,velocityUnits::pct);
        vex::task::sleep(time);
        RIntake.stop(brakeType::brake);
        LIntake.stop(brakeType::brake);
        
    }

    void Outtake (float time) {
        RIntake.spin(vex::directionType::rev,100,velocityUnits::pct);
        LIntake.spin(vex::directionType::rev,100,velocityUnits::pct);
        vex::task::sleep(time);
        RIntake.stop(brakeType::brake);
        LIntake.stop(brakeType::brake);

    }

    void keepSlowOuttake () {
      RIntake.spin(vex::directionType::rev,50,velocityUnits::pct);
        LIntake.spin(vex::directionType::rev,50,velocityUnits::pct);
    }
    
    

    void fwdTilt (float rotations, float speed) {
        Tilter.rotateTo(rotations,rotationUnits::deg,speed,velocityUnits::pct);
    }

    void revTilt (float rotations,float speed) {
        Tilter.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);

    }

    void unTilt () {
      Tilter.startRotateTo(0, rotationUnits::raw, 100, velocityUnits::pct);
    }

    void Deploy() {
      Tilter.rotateTo(1230, rotationUnits::deg, 100, velocityUnits::pct);
      Outtake(500);
      wait(75, msec);
      unTilt();


      
    }
    
    void Expand (float rotations,float speed) {
        LLift.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
        RLift.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
    }

    void Contract (float rotations,float speed) {
        LLift.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
        RLift.rotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);

    }

    void presetBrake () {
        LLift.stop(brakeType::hold);
        RLift.stop(brakeType::hold);
        Tilter.stop(brakeType::coast);
        RIntake.stop(brakeType::brake);
        LIntake.stop(brakeType::brake);
    }


    void keepIntake () {
      RIntake.spin(directionType::fwd,100,velocityUnits::pct);
      LIntake.spin(directionType::fwd,100,velocityUnits::pct);
    }

    void keepLiftDown  () {
      RLift.spin(directionType::fwd,20,velocityUnits::pct);
      LLift.spin(directionType::fwd,20,velocityUnits::pct);
    }
    void stopLiftDown  () {
      LLift.stop(brakeType::hold);
      RLift.stop(brakeType::hold);
    }

    void stopIntake () {
      RIntake.stop(brakeType::coast);
      LIntake.stop(brakeType::coast);
    }

    void keepOuttake () {
      RIntake.spin(directionType::rev,100,velocityUnits::pct);
      LIntake.spin(directionType::rev,100,velocityUnits::pct);
    }

    void stopOuttake () {
      RIntake.stop(brakeType::coast);
      LIntake.stop(brakeType::coast);

    }
      

    // void forTilt (float rotations, float speed, float time) {
    //   FLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
    //         FRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
    //         BLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
    //         BRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
    //         Tilter.spin(directionType::fwd,40,velocityUnits::pct);

    //         vex::task::sleep(time);
    //         Tilter.stop(brakeType::coast);

    // }

    // void backTilt (float rotations, float speed, float time) {
    //   FLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
    //         FRWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
    //         BLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
    //         BRWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
    //         Tilter.spin(directionType::rev,60,velocityUnits::pct);
    //         RIntake.spin(vex::directionType::rev,speed,velocityUnits::pct);
    //         LIntake.spin(vex::directionType::rev,speed,velocityUnits::pct);

    //         vex::task::sleep(time);
    //         Tilter.stop(brakeType::coast);
    //         RIntake.stop(brakeType::brake);
    //       LIntake.stop(brakeType::brake);

    // }

    // void Tilt () {
    //   while(true) {
    //       if (Controller1.ButtonUp.pressing()){
    //           Tilter.rotateTo(0.731,rotationUnits::rev,100,velocityUnits::pct);
    //           Tilter.rotateTo(2700,rotationUnits::raw,20,velocityUnits::pct);
              
              
    //       }
          
        
    //   }
    // } 




 

//

void autonomous( void ) {

    /* initialize capabilities from buttons */
   //Booleans
     bool Red = buttons[0].state;
     bool Blue = buttons[1].state;
     bool Desperation = buttons[2].state;
     bool Big = buttons[4].state;
     bool Small = buttons[5].state;
   //
 
    /* lower flag bumping code - only if near flag start tile */
 
     if(Red == true){          // Starting tile nearest to the flags/net

        if(Big == true) { //bigred
          presetBrake();
          Deploy();
          keepIntake();

          


        } 
        
        
        if(Small == true) { //smallred
          presetBrake();
          Deploy();
          keepIntake();
          keepLiftDown();
          moveForward(1.6,25);
          wait(200,msec);
          turnLeft(22,40);
          moveForward(0.6,50);
          moveBackward(1,50);
          turnRight(163,50);
          moveForward(0.875,45);
          vex::task::sleep(500);
          stopIntake();
          Outtake(125);
          fwdTilt(1600,50);
          keepSlowOuttake();
          moveBackward(0.75,50);
          
          

        } 

    }

    if(Blue == true){          // Starting tile nearest to the flags/net

        if(Big == true) { //BigBlue
          presetBrake();
          Deploy();

        } 

        if(Small == true) { //SmallBlue
          presetBrake();
          Deploy();
          keepIntake();
          moveForward(2,60);
          stopIntake();
          turnLeft(153,60);
          moveForward(2.2,60);
          fwdTilt(1630, 44);
        } 

    }

    if (Desperation == true) {
      presetBrake();
      Deploy(); 
   
    } 

    

}
  
void usercontrol( void ) {
  int error = 0;
  int targetValue = 1600;
  double kP = 0.015;
  Tilter.resetPosition();
  while (1){
      error = targetValue - Tilter.rotation(degrees);
      if(Controller1.ButtonX.pressing()) {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(2, 3);
        Controller1.Screen.print(error);
        Controller1.Screen.print(" Degrees Left");
      }
      
      Strafe.spin(vex::directionType::fwd, Controller1.Axis1.position(vex::percentUnits::pct), vex::velocityUnits::pct);  
       
      
      
      if (Controller1.ButtonL2.pressing()) {
            RIntake.spin(directionType::fwd,100,velocityUnits::pct);
            LIntake.spin(directionType::fwd,100,velocityUnits::pct);
      }
      
      else if (Controller1.ButtonR2.pressing()){
            RIntake.spin(directionType::rev,100,velocityUnits::pct);
            LIntake.spin(directionType::rev,100,velocityUnits::pct);
      }
      
      else if (Controller1.ButtonUp.pressing()){
            RIntake.stop(brakeType::coast);
            LIntake.stop(brakeType::coast);
      }
      
      else {
           RIntake.stop(brakeType::brake);
           LIntake.stop(brakeType::brake);
      }
          
      
      
     

      if ( Controller1.ButtonUp.pressing()) {
        Tilter.spin( directionType::fwd, error * kP, voltageUnits::volt );
      
        

        // task::sleep(15);
      }
      // if ( Controller1.ButtonUp.pressing()) {
      //   Tilter.spin( directionType::fwd, error * 1.75 * (kPs), velocityUnits::pct );
      
        

      //   // task::sleep(15);
      // }

      else if ( Controller1.ButtonLeft.pressing()) {
        Tilter.startRotateTo(0, rotationUnits::raw, 100, velocityUnits::pct);
      }
      else {
        Tilter.stop(brakeType::hold);
      }



      if (Controller1.ButtonDown.pressing()) {
        Tilter.spin(directionType::rev, 60, velocityUnits::pct);
        Tilter.resetPosition();
      }
          
          
      if (Controller1.ButtonL1.pressing()) {
            LLift.spin(directionType::fwd,100,velocityUnits::pct);
            RLift.spin(directionType::fwd,100,velocityUnits::pct);
      }
      else if (Controller1.ButtonR1.pressing()) {
            LLift.spin(directionType::rev,100,velocityUnits::pct);
            RLift.spin(directionType::rev,100,velocityUnits::pct);
      }
     
      else {
            LLift.stop(brakeType::brake);
            RLift.stop(brakeType::brake);
      }

      if(Controller1.ButtonA.pressing()) {
       LLift.spin(directionType::rev,100,velocityUnits::pct);
       RLift.spin(directionType::rev,100,velocityUnits::pct);
        
      }
    

    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }
}

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
