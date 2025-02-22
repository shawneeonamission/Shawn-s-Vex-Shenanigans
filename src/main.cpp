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

int rob = 1;


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
  uint8_t     myTestData[ s.length() ];
  for(int i=0; i < s.length(); i++)
  {
    
    myTestData[i] = t[i];
  }
  myTestData[s.length()] = 0x0A;

        
  //use your object and function
  if(!Brain.SDcard.exists("data_logging/testdatalogging.txt")){
    Brain.SDcard.savefile( "data_logging/testdatalogging.txt", myTestData, sizeof(myTestData) );
  } else{
    Brain.SDcard.appendfile("data_logging/testdatalogging.txt", myTestData,sizeof(myTestData));
  }
  
}

void pre_auton(void) {
  if(!chainRot.installed()){
    intakeLift.open();
  }
  
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

int test = 0;
int autoLoad(){
  
  test = 0;
  belt.spin(75);
  waitUntil(ringColor.isNearObject());
    belt.stop();
    wait(200,msec);
    belt.loadThingy();
    test = 1;
  return 0;
}
int autoHold(){
    belt.spin(100);
    waitUntil(ringColor.isNearObject());
    belt.stop();
  return 0;
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
  chainBar.resetPosition();
  Timer1.clear();
  ringColor.setLightPower(50,pct);
  ringColor.setLight(ledState::on);
  //Auton 1, Big Bot
  if (auton == 1){
    Gyro.setRotation(-22,deg);
    
    base.move(40,20);
    doink.open();
    wait(200,msec);
    base.move(-18,100);
    doink.close();
    wait(200,msec);
    base.turn(125,50);
    //Get the goal or not
    if(goalDie.objectDistance(mm) < 400){
      base.spin(-30);
      waitUntil(goalDie.objectDistance(mm) < 75);
      clamp.open();
      base.stop();
      messageToSend = "Got Goal";
      
      base.turn(180,50);
      belt.spin(100);
      base.move(40,50);
      base.turn(260,50);
      
      


    }
    else{
      base.move(8,50);
      base.turn(40,50);
      base.move(20,50);
      doink.open();
      wait(200,msec);
      base.move(-18,100);
    doink.close();
    wait(200,msec);
    base.turn(-135,50);
    //Get second goal or not
    if(goalDie.objectDistance(mm) < 400){
      base.spin(-40);
      waitUntil(goalDie.objectDistance(mm) < 75);
      clamp.open();
      messageToSend = "Got Goal";
    }
    else{
      messageToSend = "No Goal";
    }

    }
    
    doink.open();
      base.move(8,20);
      belt.stop();
      base.turn(270,50);
      doink.open();
      belt.spin(100);
      base.move(2,50);
   std::cout << Timer1.time(msec) << std::endl;
  }
  //Auton 2, Big Bot Testing
  if (auton == 2){

    base.turnToRing(100);

  }
  //Auton 3, Big Bot Skills
  if (auton == 3){
    Gyro.setRotation(0,deg);
    
    base.move(-24,40);
    wait(200,msec);
    base.turn(-45,50);
    base.spin(-20);
    waitUntil(goalDie.objectDistance(mm) < 65);

    clamp.open();
    wait(200,msec);
    base.stop();
    wait(200,msec);
    base.turn(-180,50);
    belt.spin(100);
    base.move(24,50);
    wait(200,msec);
    base.move(-24,50);
    base.turn(-90,50);
    base.move(24,50);
    wait(200,msec);
    base.move(-24,50);
    base.turn(0,50);
    base.move(24,50);
    base.turn(45,50);
    doink.open();
    base.move(34,50);
    
    wait(400,msec);
    base.turn(90,50);
     doink.close();
     wait(200,msec);
     base.spin(40);
     wait(600,msec);
     base.move(-4,50);
     base.turn(225,50);
    base.spin(-40);
    wait(600,msec);
    base.stop();
    belt.stop();
    clamp.close();
    base.move(16,50);
    base.turn(180,50);
    task asduiafsas(autoHold);
    base.move(69,50);
    base.turn(270,50);
    base.move(-24,50);
    clamp.open();
    wait(200,msec);
    base.turn(180,50);
    belt.spin(100);
    base.move(24,50);
    wait(200,msec);
    base.turn(270,50);
    base.move(24,50);
    wait(400,msec);
    base.turn(315,50);
    belt.stop();
    clamp.close();
    base.spin(-50);
    wait(2000,msec);
    base.move(12,50);
    base.turn(360,50);
    task asfhiusdfhsidf(autoLoad);
    base.move(54,50);
    waitUntil(test == 1);
    chain.spin(100);
    intakeLift.open();
    base.turn(450,50);
    base.spin(40);
    wait(800,msec);
    chain.spin(-40);
    intakeLift.close();
    wait(500,msec);
    base.move(-10,20);
    chain.stop(coast);

  }
  //Auton 4, Big Bot HS 2 Ring
  if (auton == 4){
    base.move(-24,30);
    clamp.open();
    base.turn(-90);
    belt.spin(100);
    base.move(24);
    base.turn(90);
    base.spin(60);
    wait(2000,msec);
    base.stop(brake);
  }
  //Auton 5, Big Bot HS MultiRing 
  if (auton == 5){
    base.move(-24,50);
    clamp.open();
    base.turn(-90);
    belt.spin(100);
    base.move(24,50);
    base.move(-24,50);
    base.turn(-150,50);
    base.spin(10,50);
    waitUntil(Gyro.rotation(deg) > -90);
    base.move(12,50);
    base.move(-24,50);
  }
  //Auton 6, Big Bot MultiStake
  if (auton == 6){
    chain.lift(20);
    intakeLift.open();
    base.move(4,20);
    intakeLift.close();
    belt.spin(60);
    waitUntil(ringColor.isNearObject());
    belt.stop(coast);
    base.move(8,50);
    base.turn(-90,50);
    base.move(9,20);
    chain.spin(-40);
    hang.close();
    wait(500,msec);
    base.move(-10,20);
    base.turn(-45,50);
    base.move(-24,50);
    clamp.close();
    wait(400,msec);
    base.turn(-180,50);
    belt.spin(100);
    base.move(24,50);
    base.move(-40,30);
  }
  chain.lift(80);
  //Secret, Do Nothing Push Bot
  if (auton == 7){

  }
  //Auton 1, Smol Bot Main Auton
  if (auton == 8){

    if(rob == 1){
      base.strafe(12,20);
      base.spin(-10);
      wait(200,msec);
      belt.spinFor(725,deg,100);
      base.move(16,50);
      base.move(-10,50);
      base.turn(180,50);
      base.move(-16,50);
      clamp.open();
      
      intakeLift.close();
      base.turn(220,50);
      belt.spin(100);
      base.move(16,50);
      base.move(-4,50);
      base.turn(92,50);
      base.move(52,50);
      base.turn(0,50);
      belt.stop();
      intakeLift.open();
      base.move(10,20);
      intakeLift.close();
      wait(200,msec);
      belt.spin(100);
      wait(800,msec);
      intakeLift.open();
      waitUntil(messageRecieved);
      if(recievedMessage == "Got Goal"){
      base.strafe(28,50);
      clamp.close();
      base.turn(135,50);
      base.spin(-40);
      wait(1400,msec);
      chain.spin(-100);
      waitUntil(chainBar.position(deg) < 5);
      hang.open();
      base.spin(10);
      }else if(recievedMessage == "No Goal"){
        base.move(-24,50);
        base.turn(92,50);
        base.move(-96,50);
        base.strafe(-14,20);
        base.spin(-40);
        clamp.close();
        wait(1000,msec);
        base.stop();
      }
    }
   /*Gyro.setRotation(0,deg);
    clamp.close();
    
    base.move(-44.5,40);
    belt.stop();
    clamp.open();
    belt.spin(80);
    base.move(24,40);
    belt.spin(-40);
    clamp.close();
    base.turn2(100,40);
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
    waitUntil(Timer1.time(msec) > 28000);
    hang.close();*/
  }
   //Auton 2, Smol Bot Testing
  if (auton == 9){
    hang.open();
    base.spin(20);
    waitUntil(!Competition.isEnabled());
    hang.close();
  }
   //Auton 3, Smol Bot Skills
  if (auton == 10){
    //Pick up ring
    intakeLift.close();
    wait(400,msec);
    belt.spinFor(725,deg,100);
    //backup to alliance stake
    base.spin(-20);
    wait(600,msec);
    base.stop();
    //score on alliance stake
    belt.spinFor(725,deg,100);
    //drive forward to tile grid
    base.move(12,50);
    //strafe over one tile
    base.strafe(24,50);
    //turn toward goal
    base.turn(135,50);
    //back up to goal
    base.move(-34,50);
    //clamp goal
    clamp.open();
    //turn to first ring
    base.turn(0,50);
    //Pick up ring
    belt.spin(100);
    base.move(24,50);
    //back up to other ring
    base.move(-24,50);
    //turn to next ring
    base.turn(90,50);
    //pick up next ring
    base.move(24,50);
    base.move(-24,50);
    //pick up third ring
    base.turn(180,50);
    base.move(24,50);
    //turn toward corner
    base.turn(225,50);
    //drive into corner
    base.spin(50);
    wait(600,msec);
    base.stop();
    //place goal in corner
    base.move(-4,50);
    base.turn(45,50);
    belt.stop();
    base.spin(-25);
    wait(600,msec);
    base.stop();
    clamp.close();
    //drive to next ring
    base.move(2,50);
    base.turn(0,50);
    base.move(52,50);
    //Pick up next ring
    belt.spinFor(725,deg,100);
    //pick up next goal
    base.strafe(-12,50);
    base.turn(-135,50);
    base.move(-34,50);
    clamp.open();
    wait(200,msec);
    //Pick up next ring
    base.turn(-90,50);
    belt.spin(100);
    base.move(24,50);
    base.move(-24,50);
    //Pick up 3rd ring
    base.turn(0,50);
    base.move(24,50);
    //pick up 4th ring
    base.turn(-90,50);
    base.move(24,50);
    //pick up ring in corner
    base.turn(-45,50);
    base.spin(50);
    wait(600,msec);
    base.stop();
    //place goal in corner
    base.move(-4,50);
    base.turn(135,50);
    belt.stop();
    base.spin(-25);
    wait(600,msec);
    base.stop();
    clamp.close();
    //blue alliance stake
    base.move(2,100);
    base.turn(90,50);
    base.move(52,50);
    belt.spinFor(725,deg,100);
    base.turn(180,50);
    //backup to alliance stake
    base.spin(-20);
    wait(600,msec);
    base.stop();
    //score on alliance stake
    belt.spinFor(725,deg,100);
    //hang
    base.strafe(-24,50);
    base.move(36,50);
    base.turn(135,50);
    hang.open();
    base.spin(20);
    waitUntil(!Competition.isEnabled());
    hang.close();


    
  }
   //Auton 4, Smol bot HS 2 Ring
  if (auton == 11){
    //Red
    if(rob < 2){
    base.strafe(-44,50);
    base.move(-4,100);
    clamp.open();
    intakeLift.close();
    wait(200,msec);
    belt.spin(100);
    base.move(12,50);
    base.turn(-180,50);
    base.spin(60);
    wait(2,sec);
    base.stop(brake);
    }
    //Blue
    else if(rob == 2){
    base.strafe(38,50);
    base.move(-4,100);
    clamp.open();
    wait(200,msec);
    belt.spin(100);
    base.move(12,50);
    base.turn(-180,50);
    base.spin(60);
    wait(2,sec);
    base.stop(brake);
    }
  }
   //Auton 5, Smol bot HS MultiRing
  if (auton == 12){
    //Red
    if(rob < 2){
     base.strafe(38,50);
    base.move(-4,100);
    clamp.open();
    wait(200,msec);
    belt.spin(100);
    base.move(12,50);
    base.move(-4,50);
    base.turn(-90,50);
    base.move(12,50);
    base.strafe(-6,50);
    base.move(-24,50);
    base.turn(-180,50);
    base.spin(60);
    wait(3,sec);
    base.stop(brake);
    }
    //Blue
    else if(rob == 2){
     base.strafe(-38,50);
    base.move(-4,100);
    clamp.open();
    wait(200,msec);
    belt.spin(100);
    base.move(12,50);
    base.move(-4,50);
    base.turn(90,50);
    base.move(12,50);
    base.strafe(-6,50);
    base.move(-24,50);
    base.turn(180,50);
    base.spin(60);
    wait(3,sec);
    base.stop(brake);
    }
  }
    //Auton 6, Smol Bot HS Alliance Stake
  if (auton == 13){
    if(rob < 2){
    base.strafe(-11.875,20);
    base.spin(-20);
    wait(400,msec);
    belt.spinFor(725,deg,100);
    intakeLift.open();
    base.move(6,20);
    intakeLift.close();
    wait(200,msec);
    belt.spinFor(725,deg,100);
    intakeLift.open();
    base.strafe(42,50);
    base.turn(-90,50);
    wait(200,msec);
    base.strafe(-32,50);
    base.move(-4,100);
    clamp.open();
    wait(200,msec);
    belt.spin(100);
    base.move(12,50);
    base.turn(-180,50);
    base.spin(60);
    wait(2,sec);
    base.stop(brake);
    }
    else if(rob == 2){
    base.strafe(7.375,20);
    base.spin(-20);
    wait(400,msec);
    belt.spinFor(725,deg,100);
    intakeLift.open();
    base.move(6,20);
    intakeLift.close();
    wait(200,msec);
    belt.spinFor(725,deg,100);
    intakeLift.open();
    base.strafe(-36,50);
    base.turn(90,50);
    wait(200,msec);
    base.strafe(32,50);
    base.move(-4,100);
    clamp.open();
    wait(200,msec);
    belt.spin(100);
    base.move(12,50);
    base.turn(180,50);
    base.spin(60);
    wait(2,sec);
    base.stop(brake);
    }
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
        Brain.Screen.printAt(20,210,"chainState: %d", chainState);
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
    if(status == linkType::worker){
      
    }

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
    logtoSDCard("testee");



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
