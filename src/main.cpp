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
bool testing = true;

int auton = 3;

short BotCount = 0;

int rob = 1;
int rush = 1;


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
  }else if(Competition.isFieldControl()){
    testing = false;
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
  belt.spin(50);
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
int antiJam(){
  while(1){
    if(ringBelt.velocity(rpm) < 5){
      belt.spin(-50);
      wait(300,msec);
      belt.spin(100);
      wait(200,msec);
    }
  }
  return(0);
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
  //Main Auton Big Bot
  if (auton == 1){
    Gyro.setRotation(-22,deg);
    doink.open();
    LDrive.resetPosition();
    RDrive.resetPosition();
    if(rush == 1){
    base.spin(100);
    waitUntil(goalDie.objectDistance(mm) < 400 || (((LDrive.position(rev) + RDrive.position(rev))/2) * (0.6)) * (3.25 * pi) > 34);
    base.stop(brake);
    }
    else{
    base.move(40,100);
    }
    doink.close();
    wait(300,msec);
    base.move(-18,100);
    doink.open();
    wait(400,msec);
    
    //Get the goal or not
    if(goalDie.objectDistance(mm) < 300){
      base.turn(-215,50);
      doink.close();
      base.move(-22,50);
      base.stop();
      clamp.open();
      messageToSend = "Got Goal";
      
      base.turn(-200,50);
      belt.spin(100);
      base.move(38,50);
      base.turn(-100,50);
      base.move(24,50);
      base.turn(-120,50);
      
      


    }
    else{
      base.move(-10,50);
      base.turn(55,50);
      doink.open();
      wait(600,msec);
      base.move(22,50);
      doink.close();
      wait(200,msec);
      base.move(-18,100);
    
    wait(200,msec);
    base.turn(235,50);
    //Get second goal or not
    if(goalDie.objectDistance(mm) < 600){
      base.spin(-40);
      waitUntil(goalDie.objectDistance(mm) < 75);
      clamp.open();
      messageToSend = "Got Goal";
    }
    else{
      messageToSend = "No Goal";
    }

    }
    //base.turn(270,50);
    doink.open();
    wait(400,msec);
    //base.move(12,20);
    base.spin(20);
    waitUntil(goalDie.objectDistance(mm) < 100);
    base.stop();
    base.turn(45,50);
    doink.close();
    base.move(24,50);
    base.move(-24,50);
    wait(400,msec);
    base.turn(200,50);
    doink.open();
      belt.stop();
      base.turn(290,100);
      doink.close();
      base.move(-2,50);
      belt.spin(100);
      base.move(12,50);
      base.move(-12,50);
      base.turn(45,50);
      clamp.close();
      if(rob == 1){
      base.spin(-20);
      wait(2000,msec);
      base.stop();
      } 
      base.move(4,50);
      base.turn(45,50);
      chain.lift(90);
      base.spin(20);
      wait(4000,msec);
      base.stop();
   std::cout << Timer1.time(msec) << std::endl;
  }
  //Auton 2, Big Bot Testing
  if (auton == 2){
    /* int n;
    while(1){
    std::cout << "Enter n: "; // no flush needed
        std::cin >> n;
        std::cout << std::endl;
        Controller1.Screen.print("n: %d", n);
        chain.goTo(n);
    }
 */
    //base.turnToRing(100);
    Gyro.setRotation(90,deg);
    pos.setStartPos(0,0,90);
    task sidasd(odomCalculations);
    base.moveToPoint(48,48,90,50);

  }
  //Auton 3, Big Bot Skills
  if (auton == 3){
    //Gyro.setRotation(-35,deg);
    
    base.move(-26,20);


    clamp.open();
    wait(200,msec);
    base.stop();
    wait(200,msec);
    base.turn(-174,50);
    belt.spin(100);
    base.move(24,50);
    wait(200,msec);
    base.move(-8,50);
    base.turn(-220,50);
    base.move(8,50);
    wait(200,msec);
    
    base.move(-18,50);
    base.turn(-90,50);
    base.move(18,50);
    wait(200,msec);
    base.move(-24,50);
    base.turn(-5,50);
    base.move(30,50);
    base.turn(48,50);
    chain.stop(coast);
    doink.open();
    base.move(14,50);
    
    wait(400,msec);
    base.turn(90,50);
    base.move(-4,50);
     doink.close();
     wait(400,msec);
     base.spin(40);
     wait(600,msec);
     base.move(-4,50);
     base.turn(225,50);
    base.spin(-40);
    wait(600,msec);
    base.stop();
    belt.spin(-50);
    clamp.close();
    wait(200,msec);
    base.move(14,50);
    base.turn(180,50);
    chain.lift(1);
    task asduiafsas(autoHold);
    base.move(74,50);
    base.turn(90,50);
    base.move(-22,50);
    chain.spin(-10);
    clamp.open();
    wait(200,msec);
    base.turn(180,50);
    chain.stop(coast);
    belt.spin(100);
    base.move(24,50);
    wait(200,msec);
    base.turn(90,50);
    base.move(24,50);
    wait(400,msec);
    base.turn(-45,50);
    belt.stop();
    clamp.close();
    base.move(4,50);
    clamp.open();
    base.spin(-50);
    wait(2000,msec);
    base.move(14,50);
    base.turn(86,50);
    clamp.close();
    base.move(-46,50);
    clamp.open();
    wait(200,msec);
    base.turn(45,50);
    base.move(32,50);
    base.turn(-42,50);
    belt.spin(100);
    //drive under ladder
    base.move(40,50);
    base.move(-40,50);
    clamp.close();
   
   

  }
  //Auton 4, Big Bot HS 2 Ring
  if (auton == 4){
    
    base.move(-24,30);
    clamp.open();
    base.turn(-130);
    belt.spin(100);
    base.move(24);
    base.turn(45);
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
    if(rob == 1){
      doink.open();
    LDrive.resetPosition();
    RDrive.resetPosition();
    if(rush == 1){
    base.spin(100);
    waitUntil(goalDie.objectDistance(mm) < 400 || (((LDrive.position(rev) + RDrive.position(rev))/2) * (0.6)) * (3.25 * pi) > 34);
    base.stop(brake);
    }
    else{
    base.move(40,100);
    }
    doink.close();
    wait(200,msec);

    }else{
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
  }
  if(status == linkType::worker){
  chain.lift(80);
  }
  //Secret, Do Nothing Push Bot
  if (auton == 7){

  }
  //Auton 1, Smol Bot Main Auton
  if (auton == 8){

    if(rob == 1){
      base.strafe(15.5,30);
      base.spin(-20,-10);
      wait(500,msec);
      belt.spinFor(725,deg,100);
      base.move(12,50);
      base.move(-6,50);
      base.turn(180,50);
      base.move(-14,50);
      clamp.open();
      
      intakeLift.close();
      base.turn(220,50);
      belt.spin(100);
      base.move(16,50);
      base.move(-12,50);
      base.turn(92,50);
      base.move(54,50);
      intakeLift.open();
      belt.stop();
      base.move(-6,50);
      base.turn(0,50);
      belt.stop();
      belt.spin(100);
      base.move(15,20);
      intakeLift.close();
      wait(200,msec);
      belt.spin(100);
      wait(800,msec);
      intakeLift.open();
      base.move(-14,50);
      intakeLift.close();
      base.turn(135,50);
      base.spin(40);
      wait(2000,msec);
      base.stop();
      base.move(-24,50);
      wait(500,msec);
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
      if(rob == 2){
        base.strafe(16.5,30);
      base.spin(-20,-10);
      wait(500,msec);
      belt.spinFor(725,deg,100);
      base.move(12,50);
      base.move(-6,50);
      base.turn(180,50);
      base.move(-14,50);
      clamp.open();
      
      intakeLift.close();
      base.turn(220,50);
      belt.spin(100);
      base.move(16,50);
      base.move(-12,50);
        base.turn(92,50);
        base.move(54,50);
        base.move(-8,50);
        intakeLift.open();
        base.turn(2,50);
        belt.stop();
        
        base.move(15,20);
        intakeLift.close();
        wait(200,msec);
        belt.spin(100);
        wait(800,msec);
        intakeLift.open();
        base.move(-14,50);
        intakeLift.close();
        base.turn(135,50);
        base.spin(40);
        wait(1500,msec);
        intakeLift.open();
        wait(250,msec);
        intakeLift.close();
        wait(250,msec);
        base.stop();
        base.move(-24,50);
        base.turn(-45,50);
        clamp.close();
        base.spin(-40);
        wait(2000,msec);
        base.stop();
        wait(200,msec);
        base.move(18,50);
        

        
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
    intakeLift.open();
    //base.spin(20);
    waitUntil(!Competition.isEnabled());
    intakeLift.close();
  }
   //Auton 3, Smol Bot Skills
  if (auton == 10){
    //Pick up ring
    intakeLift.close();
    wait(200,msec);
    belt.spin(100);
    //backup to alliance stake
    base.spin(-20);
    wait(600,msec);
    base.stop();
    //score on alliance stake
    belt.spin(100);
    wait(1000,msec);
    base.spin(-50);
    wait(200,msec);
    belt.stop();
    //drive forward to tile grid
    base.move(16,75);
    //readjust
    base.turn(-5,100);
    //strafe over one tile
    base.strafeSkills(-26,50);
    //turn toward goal
    base.turn(-135,50);
    //back up to goal
    base.move(-34,75);
    //clamp goal
    clamp.open();
    //turn to first ring
    belt.spin(100);
    base.turn(0,75);
    //Pick up ring
    task asdsd(antiJam);
    base.move(24,75);
   
    //back up to other ring
    base.move(-20,50);
    //turn to next ring
    base.turn(-84,75);
    //pick up next ring
    base.move(24,50);
    base.move(-24,75);
    //pick up third ring
    base.turn(-180,75);
    base.move(24,75);
    //turn toward corner
    base.turn(-225,75);
    task::stop(antiJam);
    //drive into corner
    base.spin(50);
    wait(600,msec);
    base.stop();
    //place goal in corner
    base.move(-4,75);
    base.turn(-45,75);
    
    belt.stop();
    base.spin(-25);
    wait(600,msec);
    base.stop();
    clamp.close();
    //drive to next ring
    base.move(4,100);
    base.turn(0,75);
    belt.spin(100);
    base.move(52,75);
    
    //Pick up next ring
    belt.stop();
    //pick up next goal
    base.strafeSkills(14,50);
    base.turn(135,50);
    base.move(-34,50);
    clamp.open();
    wait(200,msec);
    //Pick up next ring
    base.turn(90,50);
    belt.spin(100);
    base.move(24,50);
    task asdasd(antiJam);
    base.move(-24,50);
    //Pick up 3rd ring
    base.turn(0,50);
    base.move(24,50);
    //pick up 4th ring
    base.turn(90,50);
    base.move(24,50);
    //pick up ring in corner
    /*base.turn(45,50);
    base.spin(50);
    wait(600,msec);
    base.stop();
    base.move(-4,50);*/
    //place goal in corner
    
    base.turn(225,50);
    task::stop(antiJam);
    belt.stop();
    clamp.close();
    base.spin(-40);
    wait(1000,msec);
    base.stop();
    
    //blue alliance stake
    base.move(4,100);
    base.turn(270,50);
    belt.spin(100);
    base.move(49,50);
    belt.stop();
    base.turn(180,50);
    //backup to alliance stake
    base.spin(-20);
    wait(600,msec);
    base.stop();
    //score on alliance stake
    belt.spinFor(1450,deg,100);
    //hang
    base.strafe(24,50);
    base.move(36,50);
    base.turn(45,50);
    hang.open();
    base.spin(-40);
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
  //task asdsid(odomCalculations);
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
         if(Controller1.ButtonRight.pressing() && !togglehang && status == linkType::worker){
            hang.open();
            togglehang = 1;
            waitUntil(!Controller1.ButtonRight.pressing());
        }
        //pto shift close button
        else if(Controller1.ButtonRight.pressing() && togglehang && status == linkType::worker){
            hang.close();
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
  Timer1.clear();
    if(status == linkType::worker){
      
    }

    // set all led black
    // probably need some initial delay, TBD
    this_thread::sleep_for(200);    
    lSideRail.clear();
    wait(10,msec);
    rSideRail.clear();
    this_thread::sleep_for(1000);   
    
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