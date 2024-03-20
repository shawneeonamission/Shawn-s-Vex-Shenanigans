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
S::feeder intake;
S::link Link;
shooter Shooter;

timer Timer1 = timer();

//Vex Link Robot Status
linkType status = linkType::worker;

//variables
bool testing = false;

int auton = 1;

short sideCount = 0;

int rob = 0;

void pre_auton(void) {

  pos.setStartPos(0,0,0);

  task odom(odomCalculations);
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
  //Auton 1, Left Side
  if (auton == 1){
    Gyro.setRotation(-45,deg);
    wShooter.spin(fwd,100,pct);
    wait(400,msec);
    intakeOut.open();
    intakeTilt.open();
    wait(600,msec);
    wShooter.spin(reverse,50,pct);
 wait(400,msec);
    waitUntil(cataRot.angle(deg) > 95);
    Shooter.fire(100);
    int shot = 0;
      intake.in(65);
    while(Timer1.time(msec) < 45000 && shot <= 22){
      if(cataRot.angle(deg) > 95){
        Shooter.fire(100);
      }
      shot++;
      intakeTilt.close();
      wait(400,msec);
      intakeTilt.open();
      intake.in(100);
      wait(800,msec);
      while(intakeDie.objectDistance(mm) > 100){
        intakeTilt.close();
      wait(400,msec);
      intakeTilt.open();
      wait(1200,msec);
      }
      wait(200,msec);
      Shooter.fire(100);
    }
    waitUntil(Timer1.time(msec) > 45000);
    
    
    base.spin(-40,0);
    waitUntil(Gyro.rotation(deg) > 20);
    base.stop();
    base.move(-12,75);
    base.turn(-6,100);
    base.move(-76,100);
    base.spin(0,-20);
    waitUntil(Gyro.rotation(deg) < -36);
    base.stop();
    base.move(-16,50);
    base.spin(0,-20);
    waitUntil(Gyro.rotation(deg) < -88);
    base.spin(-40);
    wait(600,msec);
    base.stop();
    base.move(12,40);
    base.spin(-40);
    wait(600,msec);
    base.stop();
    base.spin(0,40);
    waitUntil(Gyro.rotation(deg) > -25);
    base.stop();
    base.move(34,75);
    base.turn(90,75);
    base.move(24,75);
    base.turn(0,75);
    
    base.spin(40);
    wait(500,msec);
    base.stop();
    rWing.open(); 
    base.spin(-40);
    wait(1000,msec);
    base.stop();
    base.move(24,75);
      base.spin(-40);
    wait(900,msec);
    base.stop(); 
  }
  //Auton 2, Left Side
  if (auton == 2){
    base.turn(90,100);
    base.turn(0,100);
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
    Gyro.setRotation(45,deg);
    
    intakeOut.open();
    intakeTilt.open();
    wait(600,msec);
    Shooter.fire(80);
    int shot = 0;
    if(!testing){
      intake.in(65);
    while(Timer1.time(msec) < 43000 && shot <= 22){

      shot++;
      intakeTilt.close();
      wait(400,msec);
      intakeTilt.open();
      intake.in(75);
      wait(800,msec);
      while(intakeDie.objectDistance(mm) > 100){
        intakeTilt.close();
      wait(400,msec);
      intakeTilt.open();
      wait(1200,msec);
      }
      wait(200,msec);
      Shooter.fire(80);
    }
    
    }
    waitUntil(Timer1.time(msec) > 43000);
    
    base.spin(0,-40);
    waitUntil(Gyro.rotation(deg) < -20);
    base.stop();
    base.move(-12,75);
    base.turn(8,100);
    base.move(-76,100);
    base.spin(-20,0);
    waitUntil(Gyro.rotation(deg) > 36);
    base.stop();
    base.move(-16,50);
    base.spin(-20,0);
    waitUntil(Gyro.rotation(deg) > 88);
    base.spin(-100);
    wait(600,msec);
    base.stop();
    base.move(12,40);
    base.spin(-100);
    wait(600,msec);
    base.stop();
    base.spin(40,0);
    waitUntil(Gyro.rotation(deg) < 25);
    base.stop();
    base.move(34,75);
    base.turn(-90,75);
    base.move(24,75);
    base.turn(0,75);
    
    base.spin(40);
    wait(500,msec);
    base.stop();
    rWing.open(); 
    base.spin(-100);
    wait(1000,msec);
    base.stop();
    base.move(24,75);
      base.spin(-100);
    wait(900,msec);
    base.stop(); 
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
  task shooot(Shoot);
  task intaker(intakeControl);
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
    sideRails.clear();
    wait(10,msec);
    underGlow.clear();
    wait(10,msec);
    underGlow2.clear();
    this_thread::sleep_for(1000);   
    testing = false; 
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  memset(data, 0, sizeof(data));
        for( int i=0;i<underGlow.max();i+=12 ) {
          vex::color c;
          // use low value to keep current down
          for(int j=0;j<12;j++)
            data[i+j] = c.hsv(  j*30, 1, 1);    // vex color will be converted to uint32_t
        }

        sideRails.set( data, 0, sideRails.max(), 0 );
        wait(10,msec);
        underGlow.set( data, 0, underGlow.max(), 0 );
        wait(10,msec);
        underGlow2.set( data, 0, underGlow.max(), 0 );
        wait(10,msec);

  // Prevent main from exiting with an infinite loop.
  while (true) {
   
         
         
        if(Gyro.isCalibrating()){
          waitUntil(!Gyro.isCalibrating());
      
        wait(1,sec);
          sideRails.set( data, 0, sideRails.max(), 0 );
        wait(10,msec);
        underGlow.set( data, 0, underGlow.max(), 0 );
        wait(10,msec);
        underGlow2.set( data, 0, underGlow.max(), 0 );
        wait(10,msec);
        }
          sideRails.rotate(1);
          sideRails.flush();
          wait(12.5,msec);
          underGlow.rotate(1);
          underGlow.flush();
          wait(12.5,msec);
          underGlow2.rotate(1);
          underGlow2.flush();

          
        
    wait(25, msec);
  }
}
