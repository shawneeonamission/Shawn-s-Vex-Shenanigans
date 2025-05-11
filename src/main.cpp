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
#include "VexLink.h"
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

// local storage for some pixel data
uint32_t data[RGB::MAX_LEDS];

drive base;
odom pos;
S::link Link;

timer Timer1 = timer();



//variables
bool testing = true;

int auton = 3;

short BotCount = 0;

int rob = 1;

uint8_t     myReadBuffer[ 1000 ];
//Convert the input string to an array of ascii numbers
std::array<unsigned char,100> convertToASCII(std::string s)
{
  std::array<unsigned char,100> result;
    for (int i = 0; i < s.length(); i++)
    {
        result[i] = (int)s[i];
    }
    return result;
}

//Function to save the string parameter to a text file on the sd card
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
  //Enable Testing mode if using a Compition Switch  
  if(Competition.isCompetitionSwitch()){
    std::cout << "Comp Switch" << std::endl;
    testing = true;
  }else if(Competition.isFieldControl()){
    testing = false;
  }

  //Place holder command to set the odom position
  pos.setStartPos(0,0,0);

  //run the auton selection menu if plugged into a field
  if((Competition.isFieldControl()) && !(Competition.isEnabled()) && !testing){
    task autoselect(autonSelect);
  }
  else{
    task asidasd(TestingMenu);
  }
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
  //Main Auton Big Bot
  if (auton == 1){
    //Red
    if(rob == 1){

    }
    //Blue
    else if(rob == 2){

    }
   
  }
  //Auton 2, Big Bot Testing
  if (auton == 2){
   
  }
  //Auton 3, Big Bot Skills
  if (auton == 3){
    
  }
  //Auton 4, Big Bot
  if (auton == 4){
    
  }
  //Auton 5, Big Bot
  if (auton == 5){
    
  }
  //Auton 6, Big Bot
  if (auton == 6){

  }
  //Secret, Do Nothing Smol Bot
  if (auton == 7){

  }
  //Auton 1, Smol Bot Main Auton
  if (auton == 8){
    //Red
    if(rob == 1){
      
    }
    //blue
    if(rob == 2){
        
    }
  }
   //Auton 2, Smol Bot Testing
  if (auton == 9){
    
  }
   //Auton 3, Smol Bot Skills
  if (auton == 10){
    
  }
   //Auton 4, Smol bot
  if (auton == 11){

  }
   //Auton 5, Smol bot
  if (auton == 12){

  }
    //Auton 6, Smol Bot
  if (auton == 13){

  }
  std::cout << Timer1.time(msec) << std::endl;
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
  task infoscreen(ControllerScreen);
  task linker(vexLink);
  while (1) {
    //Display the status of the vexLink Connection
    Brain.Screen.printAt( 20, 190, true, "%d Link: %s", status, linkA.isLinked() ? "ok" : "--" );

    wait(20, msec); // Sleep the task for a short amount of time to
    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  Timer1.clear();

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