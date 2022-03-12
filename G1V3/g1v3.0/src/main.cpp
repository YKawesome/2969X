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
// MogoClamp            motor         17              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "string"
// #include "robot-config.cpp"
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
    {  270,  30, 60, 60,  false, 0x303030, 0xF700FF, "Middle" },
    {  390,  30, 60, 60,  false, 0x303030, 0xDDDD00, "42069" },
    {   30, 150, 60, 60,  false, 0x404040, 0xffff00, "owo" },
    {  150, 150, 60, 60,  false, 0x404040, 0xffff00, "HalfAWP" },
    {  270, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "6-" },
    {  390, 150, 60, 60,  false, 0x404040, 0xC0C0C0, "AWP" }
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


//PID

void drivePID(float target) {
  float Kp = 60;
  float Ki = 0.7;
  float Kd = 1;
  // bool notdone = true;

  R1.setPosition(0, rotationUnits::rev);
  R2.setPosition(0, rotationUnits::rev);
  R3.setPosition(0, rotationUnits::rev);
  L1.setPosition(0, rotationUnits::rev);
  L2.setPosition(0, rotationUnits::rev);
  L3.setPosition(0, rotationUnits::rev);
  float reading = 0;
  
  float integral = 0;
  float integralLimit = 40;
  float derivative = 0;
  float previous_error = target;
  float error;
  float pidspeed = 0;

  bool startedcounting = false;
  int count = 0;
  while (true) {
  //Proportion
  reading = (L1.position(rotationUnits::rev)+R1.position(rotationUnits::rev))/2;
  
  error = target - reading;

  printf("reading: %f, error: %f\n",reading,error);

  //Integral
  integral = integral + error;
  if (error == 0){
  integral = 0;
  }

  if ( fabs(error) > integralLimit){
  integral = 0;
  }

  //Derivative
  derivative = error - previous_error;
  previous_error = error;

  
  pidspeed = Kp*error + Ki*integral + Kd*derivative;
  // pidspeed=20;

  L1.spin(fwd, pidspeed, velocityUnits::pct);
  L2.spin(fwd, pidspeed, velocityUnits::pct);
  L3.spin(fwd, pidspeed, velocityUnits::pct);
  R1.spin(fwd, pidspeed, velocityUnits::pct);
  R2.spin(fwd, pidspeed, velocityUnits::pct);
  R3.spin(fwd, pidspeed, velocityUnits::pct);
  
  if(fabs(error)<0.05) {
    count++;
  }
  if(count>=1) {
    break;
  }

  else {
    startedcounting = false;
  }

  vex::task::sleep(20);

  }

  L1.stop();
  L2.stop();
  L3.stop();
  R1.stop();
  R2.stop();
  R3.stop();

}

void drivePIDfast(float target) {
  float Kp = 42069;
  float Ki = 0;
  float Kd = 0;
  // bool notdone = true;

  R1.setPosition(0, rotationUnits::rev);
  R2.setPosition(0, rotationUnits::rev);
  R3.setPosition(0, rotationUnits::rev);
  L1.setPosition(0, rotationUnits::rev);
  L2.setPosition(0, rotationUnits::rev);
  L3.setPosition(0, rotationUnits::rev);
  float reading = 0;
  
  float integral = 0;
  float integralLimit = 40;
  float derivative = 0;
  float previous_error = target;
  float error;
  float pidspeed;
  if (target>0) {
    pidspeed = 100;
  }
  else {
    pidspeed = -100;
  }

  

  bool startedcounting = false;
  int count = 0;
  while (true) {
  //Proportion
  reading = (L1.position(rotationUnits::rev)+R1.position(rotationUnits::rev))/2;
  
  error = target - reading;

  printf("reading: %f, error: %f\n",reading,error);

  //Integral
  integral = integral + error;
  if (error == 0){
  integral = 0;
  }

  if ( fabs(error) > integralLimit){
  integral = 0;
  }

  //Derivative
  derivative = error - previous_error;
  previous_error = error;

  
  // pidspeed = Kp*error + Ki*integral + Kd*derivative;

  L1.spin(fwd, pidspeed, velocityUnits::pct);
  L2.spin(fwd, pidspeed, velocityUnits::pct);
  L3.spin(fwd, pidspeed, velocityUnits::pct);
  R1.spin(fwd, pidspeed, velocityUnits::pct);
  R2.spin(fwd, pidspeed, velocityUnits::pct);
  R3.spin(fwd, pidspeed, velocityUnits::pct);
  
  if(fabs(error)<0.05) {
    count++;
  }
  if(count>=1) {
    break;
  }

  else {
    startedcounting = false;
  }

  vex::task::sleep(20);

  }

  L1.stop();
  L2.stop();
  L3.stop();
  R1.stop();
  R2.stop();
  R3.stop();

}

void turnPID(float target) {
  float Kp = 0.75;
  float Ki = 0.001;
  float Kd = 0.001;
  // bool notdone = true;

  IMU.resetHeading();
  IMU.resetRotation();
  float reading = 0;
  
  float integral = 0;
  float integralLimit = 40;
  float derivative = 0;
  float previous_error = target;

  float pidspeed = 0;
  float error;
  bool startedcounting = false;
  int count = 0;
  while (true) {
  //Proportion
  reading = IMU.heading(degrees);
  if (fabs(reading)>350) {
    reading = -(360-fabs(reading));
    printf("%s","caught");
  }
  error = target - reading;

  printf("reading: %f, error: %f\n",reading,error);

  //Integral
  integral = integral + error;
  if (error == 0){
  integral = 0;
  }

  if ( fabs(error) > integralLimit){
  integral = 0;
  }

  //Derivative
  derivative = error - previous_error;
  previous_error = error;

  
  pidspeed = Kp*error + Ki*integral + Kd*derivative;
  // pidspeed=10;

  L1.spin(fwd, pidspeed, velocityUnits::pct);
  L2.spin(fwd, pidspeed, velocityUnits::pct);
  L3.spin(fwd, pidspeed, velocityUnits::pct);
  R1.spin(fwd, -pidspeed, velocityUnits::pct);
  R2.spin(fwd, -pidspeed, velocityUnits::pct);
  R3.spin(fwd, -pidspeed, velocityUnits::pct);
  
  if(fabs(error)<0.5) {
    count++;
  }
  if(count>=2) {
    break;
  }

  else {
    startedcounting = false;
  }

  vex::task::sleep(10);

  }

  L1.stop();
  L2.stop();
  L3.stop();
  R1.stop();
  R2.stop();
  R3.stop();

}

void setstop(std::string typy) {
  if(typy=="brake") {
    L1.stop(brake);
    L2.stop(brake);
    L3.stop(brake);
    R1.stop(brake);
    R2.stop(brake);
    R3.stop(brake);
  }
  if(typy=="coast") {
    L1.stop(coast);
    L2.stop(coast);
    L3.stop(coast);
    R1.stop(coast);
    R2.stop(coast);
    R3.stop(coast);
  }
  if(typy=="hold") {
    L1.stop(hold);
    L2.stop(hold);
    L3.stop(hold);
    R1.stop(hold);
    R2.stop(hold);
    R3.stop(hold);
  }
}

//Non-PID
void moveForward(float rots,float speed) {
  L1.rotateFor(fwd,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  L2.rotateFor(fwd,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  L3.rotateFor(fwd,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  R1.rotateFor(fwd,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  R2.rotateFor(fwd,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  R3.rotateFor(fwd,rots,rotationUnits::rev,speed,velocityUnits::pct);
  L1.stop(brake);
  L2.stop(brake);
  L3.stop(brake);
  R1.stop(brake);
  R2.stop(brake);
  R3.stop(brake);
}
void moveBackward(float rots,float speed) {
  L1.rotateFor(reverse,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  L2.rotateFor(reverse,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  L3.rotateFor(reverse,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  R1.rotateFor(reverse,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  R2.rotateFor(reverse,rots,rotationUnits::rev,speed,velocityUnits::pct,false);
  R3.rotateFor(reverse,rots,rotationUnits::rev,speed,velocityUnits::pct);
  L1.stop(brake);
  L2.stop(brake);
  L3.stop(brake);
  R1.stop(brake);
  R2.stop(brake);
  R3.stop(brake);
}




//Old Movement Functions- Cringe and Unbased

// void moveForward(float tiles,float speed) { //This is to move forward.
//         Drivetrain.driveFor(-(tiles)*24, inches, speed, velocityUnits::pct);
//         Drivetrain.stop(coast);
// }

// void moveBackward(float tiles,float speed) { //This is to move backward.
//         Drivetrain.driveFor( (tiles)*24, inches, speed, velocityUnits::pct);
//         Drivetrain.stop(coast);
// }


// void turnRight(float dees,float speed) { //This is to turn right.
//         // Drivetrain.setRotation(0, degrees);
//         // Drivetrain.turnToRotation(dees, degrees, speed, velocityUnits::pct);
//         // vex::task::sleep(timee);
//         // Drivetrain.stop(coast);
//         Drivetrain.turnFor((dees*0.55), degrees, speed, velocityUnits::pct);

// }

// void turnLeft(float dees,float speed) { //This is to turn left.
//         Drivetrain.turnFor((-dees*0.55), degrees, speed, velocityUnits::pct);
// }



void mogo_clamp(float dees) {
  // MogoClamp.rotateTo(dees,degrees,100,velocityUnits::pct);
  Pclamp.open();
}
// void mogo_clamp_time(float times) {
//   MogoClamp.spin(fwd,100,velocityUnits::pct);
  
//   // vex::task::sleep(times);
//   // MogoClamp.stop(hold);
// }
void mogo_unclamp() {
  // MogoClamp.rotateTo(0,degrees,100,velocityUnits::pct);
  Pclamp.close();
}
void mogo_down(float time) {
  Mogo.spin(reverse,100,velocityUnits::pct);
  vex::task::sleep(time);
  Mogo.stop();
}
void mogo_up(float time) {
  Mogo.spin(fwd,100,velocityUnits::pct);
  vex::task::sleep(time);
  Mogo.stop();
}

void mogo_upreset() {
  Mogo.rotateTo(0,rotationUnits::rev,100,velocityUnits::pct);
}
void lift_up(float dees) {
  FBar1.rotateTo(dees,degrees,100,velocityUnits::pct,false);

}
void lift_down(float dees) {
  FBar1.rotateFor(-(dees),degrees,100,velocityUnits::pct,false);

}
void lift_down_wait(float dees) {
  FBar1.rotateFor(-(dees),degrees,100,velocityUnits::pct,true);

}
void ppmachineopen() {
  PPmachine.open();
  vex::task::sleep(100);
}

void ppmachineclose() {
  PPmachine.close();
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
  Pclamp.open();
  PPmachine.open();
  setstop("brake");
  
  // setstop("hold");
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
  bool Middle = buttons[2].state;
  bool mogorush = buttons[3].state;
  bool owo = buttons[4].state;
  bool halfAWP = buttons[5].state;
  bool AWP = buttons[7].state;
  
  //PID Values
  // 4.3/3 is 1 tile
  // 2.6 is 2 tiles
  // 4.0 is 3 tiles

  // turnPID(180);

  // Left = true;
  // Middle = true;
  owo = true;
  // halfAWP = true;
  // AWP = true;


  if(AWP!=true) {
    Pclamp.close();
  }
  
  if (owo) {
    FBar1.setRotation(0, rotationUnits::deg);
    FBar1.stop(hold);
    Mogo.stop(hold);
    drivePIDfast(2.55);
    Pclamp.open();
    vex::task::sleep(100);
    // vex::task::sleep(100);
    drivePID(-1.53);
    vex::task::sleep(100);
    turnPID(140);
    moveForward(0.3,60);
    Pclamp.close();
    mogo_down(1000);
    // drivePID(-2.35);
    moveBackward(2.35,50);
    moveBackward(0.38,21);
    mogo_upreset();
    drivePID(2.5);


  }

  if (Middle) {
    FBar1.setRotation(0, rotationUnits::deg);
    FBar1.stop(hold);
    drivePIDfast(3.31);
    Pclamp.open();
    // vex::task::sleep(100);
    drivePIDfast(-3);
  }

  if (mogorush) {
    FBar1.setRotation(0, rotationUnits::deg);
    FBar1.stop(hold);
    drivePIDfast(2.55);
    Pclamp.open();
    // vex::task::sleep(100);
    drivePIDfast(-2.3);
  }
  
  
  if(Left == true){

      if(halfAWP == true) {
        Mogo.setRotation(0, degrees);
        Mogo.setStopping(hold);
        FBar1.stop(hold);
        FBar1.setStopping(hold);
        setstop("brake");
        printf("%s","testing in progress");

        mogo_down(1000);
        mogo_upreset();
        moveForward(0.35,60);
        vex::task::sleep(100);
        turnPID(101);
        vex::task::sleep(100);
        drivePID(2.7);
        Pclamp.open();
        drivePID(-2);


      } 

  }

  if(Right == true) {

      if(halfAWP == true) { 
        Mogo.setRotation(0, degrees);
        Mogo.setStopping(hold);
        FBar1.stop(hold);
        FBar1.setStopping(hold);
        FBar1.setRotation(0, rotationUnits::deg);
        setstop("brake");
        printf("%s","testing in progress");
      
        moveBackward(0.35,60);
        mogo_down(1000);
        mogo_upreset();

        moveForward(0.17,60);
        PPmachine.close();
        mogo_down(1000);
        drivePID(-1);
        mogo_upreset();
        drivePID(0.4);
        vex::task::sleep(100);
        turnPID(114);
        vex::task::sleep(100);
        lift_up(160);
        // drivePID(3.22);
        drivePID(2.60);
        vex::task::sleep(100);
        lift_down(250);
        vex::task::sleep(100);
        // turnPID(10);
        // drivePID(.92);
        turnPID(10);
        drivePID(0.9);
        // vex::task::sleep(100);
        // vex::task::sleep(200);
        Pclamp.open();
        vex::task::sleep(300);
        // turnPID(20);
        drivePID(-3);
        mogo_down(1000);
        PPmachine.open();
        drivePID(0.5);
      } 

      // if(AWP==true ) {

    
      // }

  }

  if (AWP == true) {
    Mogo.setRotation(0, degrees);
    Mogo.setStopping(hold);
    FBar1.stop(hold);
    FBar1.setStopping(hold);
    FBar1.setRotation(0, rotationUnits::deg);
    setstop("brake");
    printf("%s","testing in progress");

    mogo_down(1000);
    mogo_upreset();
    moveForward(0.23,60);
    turnPID(20);
    moveForward(0.2,60);
    vex::task::sleep(100);
    turnPID(70);
    vex::task::sleep(100);
    drivePID(1.3);
    vex::task::sleep(100);
    turnPID(81.5); //mayb 84.5
    lift_up(500);
    // drivePID(5.25);
    drivePID(5.025);
    
    vex::task::sleep(400);
    Pclamp.close();
    moveBackward(0.275,40);
    turnPID(171);
    
    // lift_down_wait(300);
    lift_down(550);
    drivePID(-0.5);
    // lift_down_wait(250);
    drivePID(-0.35);
    PPmachine.close();
    vex::task::sleep(300);
    moveForward(1.5,70);
    // Pclamp.close();
    turnPID(70);






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
bool ppheld = true;
bool pclampheld = true;
bool mogobool = true;
bool resetavailable = true;
void usercontrol(void) {
  setstop("coast");
  // FBar.setStopping(brake);
  // MogoClamp.setStopping(hold);
  Mogo.setStopping(hold);
  PPmachine.open();
  // FBar1.stop(brake);
  // thread end_sequence(thend);
  while (1) {
    
    // if (Controller1.ButtonDown.pressing()) {
    //   autonomous();
    // }


    //FourBar
    if (Controller1.ButtonR1.pressing()) {
      FBar1.spin(directionType::fwd,100,velocityUnits::pct);
    }
    else if (Controller1.ButtonL1.pressing()) {
      FBar1.spin(directionType::rev,100,velocityUnits::pct);
    }
    else {
      FBar1.stop(brakeType::brake);
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
      Mogo.spinFor(directionType::fwd, 369, degrees, 100, velocityUnits::pct);
      Mogo.stop(brakeType::hold);
      vex::task::sleep(500);
    }
    else if (Controller1.ButtonX.pressing() and mogobool == true){
      Mogo.spin(fwd, 7, velocityUnits::pct);
    }
    
    if (Controller1.ButtonA.pressing() and mogobool==true) {
      mogobool=false;
      PPmachine.close();
      Mogo.spinFor(directionType::rev, 369, degrees, 100, velocityUnits::pct);
      PPmachine.open();
      Mogo.stop(brakeType::hold);
      vex::task::sleep(500);
    }
    else if (Controller1.ButtonA.pressing() and mogobool == false){
      Mogo.spin(fwd, -7, velocityUnits::pct);
    }

    if (Controller1.ButtonDown.pressing() and resetavailable==true) {
      resetavailable=false;
      Mogo.spin(fwd,100,velocityUnits::pct);
      vex::task::sleep(1500);
      Mogo.stop();
      Mogo.setRotation(0, rotationUnits::deg);
      vex::task::sleep(1000);
      resetavailable=false;
    }

    // //MogoClamp
    // if (Controller1.ButtonR2.pressing()) {
    //   MogoClamp.spin(directionType::fwd,100,velocityUnits::pct);
    // }
    // else if (Controller1.ButtonL2.pressing()) {
    //   MogoClamp.spin(directionType::rev,100,velocityUnits::pct);
    // }
    // else {
    //   MogoClamp.stop(brakeType::hold);
    // }

    



    //Pneumatics
    if (Controller1.ButtonL2.pressing() and ppheld==true) {
      PPmachine.close();
      ppheld=false;
      vex::task::sleep(500);
    }
    else if (Controller1.ButtonL2.pressing() and ppheld==false) {
      PPmachine.open();
      ppheld=true;
      vex::task::sleep(500);
    } 
    
    if (Controller1.ButtonR2.pressing() and pclampheld==true) {
      Pclamp.close();
      pclampheld=false;
      vex::task::sleep(500);
    }
    else if (Controller1.ButtonR2.pressing() and pclampheld==false) {
      Pclamp.open();
      pclampheld=true;
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
    }
    else {
      Controller1.rumble("   ");
      Mogo.stop(hold);
    }

    if (Controller1.ButtonRight.pressing() and chassis_is_held==true) {
      setstop("coast");
      chassis_is_held=false;
      // thend();
      vex::task::sleep(500);
    }
    else if (Controller1.ButtonRight.pressing() and chassis_is_held==false) {
      setstop("hold");
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
  // printf("%s","inertial ready");
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

