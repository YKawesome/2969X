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
// FLWheel              motor         17              
// FRWheel              motor         15              
// BRWheel              motor         14              
// BLWheel              motor         13              
// Tilter               motor         5               
// TwoBar               motor         4               
// RIntake              motor         8               
// LIntake              motor         6               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.h"

using namespace vex;


vex::competition    Competition;

motor_group   leftDrive( FLWheel, BLWheel );

motor_group   rightDrive( FRWheel, BRWheel );

drivetrain    robotDrive( leftDrive, rightDrive, 12.56, 12, 12, distanceUnits::in );


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
//Functions
    void moveForward(float ins,float speed) { //This is to move forward.
            robotDrive.driveFor( (ins * 24), inches, speed, velocityUnits::pct);
    }

    void moveBackward(float ins,float speed) { //This is to move backward.
            robotDrive.driveFor( -(ins * 24), inches, speed, velocityUnits::pct);
    }

    void moveBackwardTime(float time, float speed) { //This is to move backward.
            FLWheel.spin(directionType::rev,speed,velocityUnits::pct);
            BLWheel.spin(directionType::rev,speed,velocityUnits::pct);
            FRWheel.spin(directionType::rev,speed,velocityUnits::pct);
            BRWheel.spin(directionType::rev,speed,velocityUnits::pct);
            vex::task::sleep(time);
            FLWheel.stop(brakeType::brake);
            FRWheel.stop(brakeType::brake);
            BLWheel.stop(brakeType::brake);
            BRWheel.stop(brakeType::brake);
            

    }

    void moveForwardTime(float time, float speed) { //This is to move backward.
            FLWheel.spin(directionType::fwd,speed,velocityUnits::pct);
            BLWheel.spin(directionType::fwd,speed,velocityUnits::pct);
            FRWheel.spin(directionType::fwd,speed,velocityUnits::pct);
            BRWheel.spin(directionType::fwd,speed,velocityUnits::pct);
            vex::task::sleep(time);
            FLWheel.stop(brakeType::brake);
            FRWheel.stop(brakeType::brake);
            BLWheel.stop(brakeType::brake);
            BRWheel.stop(brakeType::brake);
            

    }

    void turnRight(float dees,float speed) { //This is to turn right.
            robotDrive.turnFor( (dees / 2), degrees, speed, velocityUnits::pct);
    }

    void turnLeft(float dees,float speed) { //This is to turn left.
            robotDrive.turnFor( -(dees / 2), degrees, speed, velocityUnits::pct);
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

    void fwdTilt (float time) {
        Tilter.spin(directionType::fwd,30,velocityUnits::pct);
        vex::task::sleep(time);
        Tilter.stop(brakeType::coast);
    }

    void revTilt (float rotations,float speed) {
        Tilter.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);

    }

    void fullTilt(){
        Tilter.rotateTo(2669,rotationUnits::raw,60,velocityUnits::pct);
    }
        
    void fullerTilt(float time){
      Tilter.spin(directionType::fwd,100,velocityUnits::pct);
      vex::task::sleep(time);
      Tilter.stop(brakeType::coast);
    }

    void halfTilt(){
        Tilter.rotateTo(550,rotationUnits::raw,100,velocityUnits::pct);
        Tilter.stop(brakeType::coast);
    }

    void unTilt(){
        Tilter.rotateTo(0,rotationUnits::raw,100,velocityUnits::pct);
      
    }
    void unnerTilt(){
        TwoBar.spin(directionType::rev,50,velocityUnits::pct);
        Tilter.rotateTo(0,rotationUnits::raw,100,velocityUnits::pct);
        TwoBar.stop(brakeType::brake);

        

    }
    
    void Expand (float rotations,float speed) {
        TwoBar.rotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
    }

    void Contract (float rotations,float speed) {
        TwoBar.rotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);

    }

    void presetBrake () {
        TwoBar.stop(brakeType::hold);
        Tilter.stop(brakeType::coast);
        RIntake.stop(brakeType::brake);
        LIntake.stop(brakeType::brake);
    }



    void keepIntake () {
      RIntake.spin(directionType::fwd,100,velocityUnits::pct);
      LIntake.spin(directionType::fwd,100,velocityUnits::pct);
    }

    void stopIntake () {
      RIntake.stop(brakeType::coast);
      LIntake.stop(brakeType::coast);
      RIntake.spin(directionType::fwd,50,velocityUnits::pct);
      LIntake.spin(directionType::fwd,50,velocityUnits::pct);
      vex::task::sleep(300);
      RIntake.stop(brakeType::coast);
      LIntake.stop(brakeType::coast);

    }

    void keepOuttake () {
      RIntake.spin(directionType::rev,100,velocityUnits::pct);
      LIntake.spin(directionType::rev,100,velocityUnits::pct);
    }

       void keepLiftDown () {
      TwoBar.spin(directionType::rev,30,velocityUnits::pct);

    }

        void stopLiftDown () {
          TwoBar.stop(brakeType::hold);
        }
      

    void stopOuttake () {
      RIntake.stop(brakeType::coast);
      LIntake.stop(brakeType::coast);

    }
    void forIntake (float rotations, float speed, float time) {
            FLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
            FRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
            BLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
            BRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
            RIntake.spin(directionType::fwd,100,velocityUnits::pct);
      LIntake.spin(directionType::fwd,100,velocityUnits::pct);
            vex::task::sleep(time);
            RIntake.stop(brakeType::coast);
            LIntake.stop(brakeType::coast);



    }

    void forTilt (float rotations, float speed, float time) {
      FLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
            FRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
            BLWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
            BRWheel.startRotateFor(rotations,rotationUnits::rev,speed,velocityUnits::pct);
            Tilter.spin(directionType::fwd,40,velocityUnits::pct);

            vex::task::sleep(time);
            Tilter.stop(brakeType::coast);

    }

    void backTilt (float rotations, float speed, float time) {
      FLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
            FRWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
            BLWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
            BRWheel.startRotateFor(-rotations,rotationUnits::rev,speed,velocityUnits::pct);
            Tilter.spin(directionType::rev,60,velocityUnits::pct);
            RIntake.spin(vex::directionType::rev,speed,velocityUnits::pct);
            LIntake.spin(vex::directionType::rev,speed,velocityUnits::pct);

            vex::task::sleep(time);
            Tilter.stop(brakeType::coast);
            RIntake.stop(brakeType::brake);
          LIntake.stop(brakeType::brake);

    }

    void Tilt () {
      while(true) {
          if (Controller1.ButtonUp.pressing()){
              Tilter.rotateTo(0.731,rotationUnits::rev,100,velocityUnits::pct);
              Tilter.rotateTo(2700,rotationUnits::raw,20,velocityUnits::pct);
              
              
          }
          
        
      }
    } 





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
                    //Parameters: rotations, speed
          //Example: function(rotations,speed);
          presetBrake();
            keepLiftDown();
              fullerTilt(900);
              Outtake(450);
              unTilt();
              stopLiftDown();

              


              
              
              keepIntake();
              moveForward(1.625,60);
              moveForward(2,20);
              moveBackward(2.05,60);
              stopIntake();
              Intake(300);

              turnLeft(0.71,60);
              

              vex::task::sleep(200);
              forIntake(1.35,50,1100);
              
              vex::task::sleep(300);
              turnLeft(0.315,30);
                            Intake(400);
              Outtake(260);
              forTilt(0.868,50,1600);
              fwdTilt(1350);
              vex::task::sleep(50);
              backTilt(1,30,1000);

        } 

        if(Small == true) { //smallred
          presetBrake();
          keepLiftDown();
          fullerTilt(900);
          Outtake(450);
          unTilt();
          
          keepIntake();
          moveForward(3.8,55);
          
          moveBackward(1.4,87);
          vex::task::sleep(200);
          turnLeft(0.335,75); 
          moveBackward(2.48,70);
          turnRight(0.31,69);
          
          moveForward(3.3,40);
          turnRight(1.14,85);
          moveForward(2.03,50);
          stopLiftDown();
          stopIntake();
           
        
          
          forTilt(1.05,45,1100);

          fwdTilt(1350);
          vex::task::sleep(50);
          backTilt(1,30,1000);
        } 

    }

    if(Blue == true){          // Starting tile nearest to the flags/net

        if(Big == true) { //BigBlue
                    //Parameters: rotations, speed
          //Example: function(rotations,speed);
          presetBrake();
            keepLiftDown();
              fullerTilt(900);
              Outtake(450);
              unTilt();
              stopLiftDown();

              


              
              
              keepIntake();
              moveForward(1.625,60);
              moveForward(2,20);
              moveBackward(2.05,60);
              stopIntake();
              Intake(300);

              turnRight(0.71,60);
              

              vex::task::sleep(200);
              forIntake(1.35,50,1100);
              
              vex::task::sleep(300);
              turnRight(0.32,30);
                            Intake(400);
              Outtake(175);
              forTilt(0.87,50,1600);
              fwdTilt(1350);
              vex::task::sleep(50);
              backTilt(1,30,1000);

        } 

        if(Small == true) { //SmallBlue
          //Parameters: rotations, speed
          //Example: function(rotations,speed);


          presetBrake();
          keepLiftDown();
          fullerTilt(900);
          Outtake(450);
          unTilt();
           stopLiftDown();
          keepIntake();
          moveForward(2,55);
          
          // moveBackward(1.35,87);
          // vex::task::sleep(200);
          // turnRight(0.35,69); 
          // moveBackward(2.45,60);
          // turnLeft(0.32,69);
          
          // moveForward(3.5,40);
          // turnLeft(1.3,69);
          // moveForward(2,55);
          // stopIntake();
        
          // Outtake(100);
          // forTilt(1.05,45,1100);

          // fwdTilt(1350);
          // vex::task::sleep(50);
          // backTilt(1,30,1000);

        } 

    }

    if (Desperation == true) {
    /*       moveForwardTime(1500,30);
      moveBackwardTime(5000,30);
      presetBrake();
            keepLiftDown();
              fullerTilt(900);
              Outtake(450);
              unTilt();
              stopLiftDown(); */
        turnRight(90,69);
   
    }

    

}
   
void usercontrol( void ) {
  thread Tilt_Sequence(Tilt); 
  // User control code here, inside the loop
  while (1){
       FLWheel.spin(vex::directionType::fwd,
            Controller1.Axis2.position(vex::percentUnits::pct) + Controller1.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct);
       BLWheel.spin(vex::directionType::fwd,
            Controller1.Axis2.position(vex::percentUnits::pct) + Controller1.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct);
        //Right motor, vertical axis of left joystick minus horizontal axis of left joystick
       FRWheel.spin(vex::directionType::fwd,
            Controller1.Axis2.position(vex::percentUnits::pct) - Controller1.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct); 
       BRWheel.spin(vex::directionType::fwd,
            Controller1.Axis2.position(vex::percentUnits::pct) - Controller1.Axis4.position(vex::percentUnits::pct),
            vex::velocityUnits::pct);  
      
      
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
          
      
     


    
          
          
      if (Controller1.ButtonL1.pressing()) {
            halfTilt();
            TwoBar.spin(directionType::fwd,100,velocityUnits::pct);
      }
      else if (Controller1.ButtonR1.pressing()){
            halfTilt();
            TwoBar.spin(directionType::rev,100,velocityUnits::pct);
      }
     
      else {
            TwoBar.stop(brakeType::brake);
      }
     
      if (Controller1.ButtonRight.pressing()) {
            if(Controller1.ButtonL1.pressing()) {
              halfTilt();
              TwoBar.rotateTo(1.565,rotationUnits::rev,100,velocityUnits::pct);
            }
      }

      if (Controller1.ButtonDown.pressing()) {
            if(Controller1.ButtonL1.pressing()) {
              halfTilt();
              TwoBar.rotateTo(01.142,rotationUnits::rev,100,velocityUnits::pct);
            }
      }

      if(Controller1.ButtonA.pressing()) {
       TwoBar.spin(directionType::rev,100,velocityUnits::pct);
        
      }


  if (Controller1.ButtonLeft.pressing()){
           unTilt();
      }


      if(Controller1.ButtonB.pressing()) {
  
    FLWheel.stop(brakeType::coast);
    FRWheel.stop(brakeType::coast);
    BLWheel.stop(brakeType::coast);
    BRWheel.stop(brakeType::coast);
      }
      if(Controller1.ButtonY.pressing()) {
  
    FLWheel.stop(brakeType::brake);
    FRWheel.stop(brakeType::brake);
    BLWheel.stop(brakeType::brake);
    BRWheel.stop(brakeType::brake);
      }
      if(Controller1.ButtonX.pressing()) {
  
   
      }
    

      //2700,rotationUnits::raw,20,velocityUnits::pct
       
      
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
