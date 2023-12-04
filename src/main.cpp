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
#include "intake.h"
#include "VexLink.h"
#include "shooter.h"
#include "AutonSelection.h"
#include <iostream>
#include <array>
#include <thread>

using namespace S;
using namespace vex;

// A global instance of competition
competition Competition;

drive base;
odom pos;
feeder intake;
S::link Link;
shooter Shooter;

//Vex Link Robot Status
linkType status = linkType::manager;

//variables
bool testing = false;

int auton = 0;

short sideCount = 0;

int rob = 0;

void pre_auton(void) {

  pos.setStartPos(0,0,0);

  task odom(odomCalculations);
  task startLink(vexLink);

  if((Competition.isFieldControl() || Competition.isCompetitionSwitch()) && !(Competition.isEnabled())){
    task autoselect(autonSelect);
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
  //Auton 1, Left Side
  if (auton == 1){

  }
  //Auton 2, Left Side
  if (auton == 2){
    
  }
  //Auton 3, Left Side
  if (auton == 3){

  }
  //Auton 4, Left Side
  if (auton == 4){
    
  }
  //Auton 5, Left Side
  if (auton == 5){

  }
  //Auton 6, Left Side
  if (auton == 6){
    
  }
  //Secret, Do Nothing Right Side
  if (auton == 7){

  }
  //Auton 1, Right Side
  if (auton == 8){
    
  }
   //Auton 2, Right Side
  if (auton == 9){

  }
   //Auton 3, Right Side
  if (auton == 10){
    
  }
   //Auton 4, Right Side
  if (auton == 11){

  }
   //Auton 5, Right Side
  if (auton == 12){
    
  }
    //Auton 6, Right Side
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
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
