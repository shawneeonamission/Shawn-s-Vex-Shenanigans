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
liftgoal choo;
S::hooks belt;

timer Timer1 = timer();



//variables
bool testing = false;

int auton = 1;

short BotCount = 0;

int rob = 0;

uint8_t     myTestData[ 1000 ];
uint8_t     myReadBuffer[ 1000 ];

std::array<unsigned char,100> convertToASCII(std::string s)
{
  std::array<unsigned char,100> result;
    for (int i = 0; i < s.length(); i++)
    {
        result[i] = (int)s[i];
    }
    return result;
}
void logtoSDCard(std::string s)
{
  std::array<unsigned char,100> t = convertToASCII(s);
  for(int i=0; i < s.length(); i++)
  {
    
    myTestData[i] = t[i];
  }
  myTestData[s.length() + 1] = 0x0A;
        
  //use your object and function
  if(!Brain.SDcard.exists("data_logging/testdatalogging.txt")){
    Brain.SDcard.savefile( "data_logging/testdatalogging.txt", myTestData, sizeof(myTestData) );
  } else{
    Brain.SDcard.appendfile("data_logging/testdatalogging.txt", myTestData,sizeof(myTestData));
  }
  
}

void pre_auton(void) {
  if(Competition.isCompetitionSwitch()){
    std::cout << "Comp Switch" << std::endl;
  testing = true;
  }
  pos.setStartPos(0,0,0);

  if((Competition.isFieldControl()) && !(Competition.isEnabled()) && !testing){
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
  chainRot.resetPosition();
  Timer1.clear();
  //Auton 1, Hook Bot
  if (auton == 1){
    Gyro.setRotation(-33,deg);
    
    base.move(-18,20);
    chain.lift(60);
    hang.open();
    choo.lift(100);
    base.turn(-92,40);
    base.move(10,20);
    chain.spin(-20);
    wait(500,msec);
    base.move(-10,20);
    chain.stop(coast);
    base.turn(-130,40);
    belt.spin(100);
    base.move(10,40);
    base.move(-10,40);
    base.turn(0,50);
    base.move(48,75);
    base.turn(90,40);
    chain.lift(80);
    hang.open();
    base.move(20,30);
    chain.spin(-40);
    wait(200,msec);
    base.move(-24,40);
   std::cout << Timer1.time(msec) << std::endl;
  }
  //Auton 2, hook Bot
  if (auton == 2){

    base.turn(90,50);
    wait(200,msec);
    base.turn(0,50);

  }
  //Auton 3, hook Bot Skills
  if (auton == 3){
    Gyro.setRotation(50,deg);
    base.move(-40,40);
    choo.lift(100);
    base.turn(0,50);
    belt.spin(100);
    base.move(24,50);
    wait(200,msec);
    base.move(-24,50);
    base.turn(180,50);
    base.move(24,50);
    wait(200,msec);
    base.move(-24,50);
    base.turn(170,50);
    base.move(-34,50);

  }
  //Auton 4, hook Bot HS 2 Ring
  if (auton == 4){
    base.move(-24,30);
    choo.lift(100);
    base.turn(-90);
    belt.spin(100);
    base.move(24);
    base.turn(90);
    base.spin(60);
    wait(2000,msec);
    base.stop(brake);
  }
  //Auton 5, hook Bot HS MultiRing Left
  if (auton == 5){

  }
  //Auton 6, hook Bot
  if (auton == 6){
    
  }
  //Secret, Do Nothing Push Bot
  if (auton == 7){

  }
  //Auton 1, Push Bot Main Auton
  if (auton == 8){
    Gyro.setRotation(-69,deg);
    clamp.close();
    belt.spin(100);
    base.move(-62,100);
    belt.stop();
    clamp.open();
    base.move(12,40);
    clamp.close();
    base.turn(0,40);
    base.move(32,50);
    base.turn(-135,40);
    base.move(-12,20);
    clamp.open();
    base.move(12,40);
    base.turn(-90,40);
    base.move(36,50);
    base.turn(-180,50);
    base.move(36,50);
    belt.spin(100);
    wait(1,sec);
    belt.stop();
    base.move(-100,100);
    clamp.open();
    base.turn(-225,40);
    hang.open();
    base.spin(40);
    waitUntil(Gyro.pitch(deg) > 15);
    hang.close();
  }
   //Auton 2, Push Bot PID Tuning
  if (auton == 9){
    
  }
   //Auton 3, Push Bot Skills
  if (auton == 10){
    
  }
   //Auton 4, Hook bot HS 2 Ring
  if (auton == 11){
    base.move(-24,30);
    choo.lift(100);
    base.turn(-90);
    belt.spin(100);
    base.move(24);
    base.turn(90);
    base.spin(60);
    wait(2,sec);
    base.stop(brake);
  }
   //Auton 5, Hook bot HS MultiRing
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
bool togglehang = false;
void usercontrol(void) {
  // User control code here, inside the loop
  task driver(Drive);
  task liftdagoal(FerrisWheel);
  task chaine(chainBarControl);
  task Ringer(ringBeltControl);
  task infoscreen(ControllerScreen);
  task linker(vexLink);
  while (1) {
        Brain.Screen.printAt( 20, 190, true, "%d Link: %s", status, linkA.isLinked() ? "ok" : "--" );
    if(Controller1.ButtonUp.pressing() && !togglehang && status == linkType::worker){
            hang.open();
            togglehang = 1;
            waitUntil(!Controller1.ButtonUp.pressing());
        }
        //pto shift close button
        else if(Controller1.ButtonUp.pressing() && togglehang && status == linkType::worker){
            hang.close();
            togglehang = 0;
            waitUntil(!Controller1.ButtonUp.pressing());
        }
         if(Controller1.ButtonRight.pressing() && !togglehang && status == linkType::manager){
            doink.open();
            togglehang = 1;
            waitUntil(!Controller1.ButtonRight.pressing());
        }
        //pto shift close button
        else if(Controller1.ButtonRight.pressing() && togglehang && status == linkType::manager){
            doink.close();
            togglehang = 0;
            waitUntil(!Controller1.ButtonRight.pressing());
        }


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
    logtoSDCard("test");
    logtoSDCard("test");



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
