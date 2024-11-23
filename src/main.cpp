/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       shawn                                                     */
/*    Created:      5/14/2023, 9:00:30 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/



#include "vex.h"
#include "drive.h"
#include "odom.h"
#include "ChainBar.h"
#include "RingBelt.h"
#include "VexLink.h"
#include "GoalLift.h"
#include "AutonSelection.h"
#include "controllerScreen.h"
#include <iostream>
#include <array>
#include <thread>
#include <rgbLED.h>

using namespace S;
using namespace vex;

// A global instance of competition
competition Competition;

// instance of the addressable led on external 3wire extender port A
// we limit to 144 leds max for this strip


// local storage for some pixel data
uint32_t data[RGB::MAX_LEDS];

drive base;
odom pos;
S::ringBar chain;
S::link Link;
liftgoal ferriswheel;
S::hooks belt;

timer Timer1 = timer();



//variables
bool testing = false;

int auton = 1;

short BotCount = 0;

int rob = 0;

void pre_auton(void) {
  testing = true;
  pos.setStartPos(0,0,0);

  
  task startLink(vexLink);


  if((Competition.isFieldControl() || Competition.isCompetitionSwitch()) && !(Competition.isEnabled()) && !testing){
    task autoselect(autonSelect);
  }
  else{
    task asidasd(TestingMenu);
  }

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  
  Timer1.clear();
  testing = false;
  //Auton 1, Hook Bot
  if (auton == 1){
   
  }
  //Auton 2, hook Bot
  if (auton == 2){
 
  }
  //Auton 3, hook Bot
  if (auton == 3){
    
  }
  //Auton 4, hook Bot
  if (auton == 4){
    
  }
  //Auton 5, hook Bot
  if (auton == 5){

  }
  //Auton 6, hook Bot
  if (auton == 6){
    
  }
  //Secret, Do Nothing Push Bot
  if (auton == 7){

  }
  //Auton 1, Push Bot
  if (auton == 8){
    
  }
   //Auton 2, Push Bot
  if (auton == 9){
    
  }
   //Auton 3, Push Bot
  if (auton == 10){
    
  }
   //Auton 4, Push Bot
  if (auton == 11){
    
  }
   //Auton 5, Push Bot
  if (auton == 12){
    
  }
    //Auton 6, Push Bot
  if (auton == 12){
    
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
  // User control code here, inside the loop
  task driver(Drive);
  task liftdagoal(FerrisWheel);
  task chaine(chainBarControl);
  task Ringer(ringBeltControl);
  task infoscreen(ControllerScreen);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
 

    // set all led black
    // probably need some initial delay, TBD
    this_thread::sleep_for(200);    
    lSideRail.clear();
    wait(10,msec);
    rSideRail.clear();
    this_thread::sleep_for(1000);   
    testing = false; 
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  memset(data, 0, sizeof(data));
        for( int i=0;i<rSideRail.max();i+=12 ) {
          vex::color c;
          // use low value to keep current down
          for(int j=0;j<12;j++)
            data[i+j] = c.hsv(  j*30, 1, 0.75);    // vex color will be converted to uint32_t
        }

        lSideRail.set( data, 0, lSideRail.max(), 0 );
        wait(10,msec);
        rSideRail.set( data, 0, rSideRail.max(), 0 );
        wait(10,msec);


  // Prevent main from exiting with an infinite loop.
  while (true) {
   
         
         
        if(Gyro.isCalibrating()){
          waitUntil(!Gyro.isCalibrating());
      
        wait(1,sec);
          lSideRail.set( data, 0, lSideRail.max(), 0 );
        wait(10,msec);
        rSideRail.set( data, 0, rSideRail.max(), 0 );
        wait(10,msec);
        }
          lSideRail.rotate(1);
          lSideRail.flush();
          wait(12.5,msec);
          rSideRail.rotate(1);
          rSideRail.flush();
        
    wait(25, msec);
  }
}
