#include "vex.h"
#include "AutonSelection.h"
#include <iostream>
#include "rgbLED.h"

void gyroCalibrate()
{
Gyro.calibrate();
Brain.Screen.setFillColor(black);
Brain.Screen.setPenColor(red);
Brain.Screen.drawRectangle(20,20,100,70);
Brain.Screen.printAt(25,50,"Calibrate");
Brain.Screen.printAt(25,70,"Inertial");
lSideRail.clear(color(100,0,0));
wait(10,msec);
rSideRail.clear(color(100,0,0));
 

  while(Gyro.isCalibrating())
  {
    task::sleep(5);
  }
   Brain.Screen.setPenColor(green);
          Brain.Screen.drawRectangle(20,20,100,70);
Brain.Screen.printAt(25,70,"Calibrated");
Brain.Screen.printAt(25,50,"Inertial");
  Controller1.rumble(".");
  Controller1.Screen.print("Calibrated");
  lSideRail.clear(color(0,100,0));
  wait(10,msec);
  rSideRail.clear(color(0,100,0));
}

//Count for side menus
int menuCount;
//Menu Conditions
bool autonDone;
bool BotDone;
bool driverDone;
bool reviewDone;
//Count for autonomous chooser
short count;
//Count for side chooser

//Boolean for driver chooser
short driverCount = 1;
//String arrays for display text
const char *autonModes[7];
const char *Bots[3];
const char *drivers[5];

uint8_t   imageBuffer[ 240 * (128 * 1024) ];
uint32_t  imageBufferLen[240];

void
introInit() {
  char  filename[32];
  
  Brain.Screen.clearScreen();
  for(int file=0;file<140;file++) {
    int offset = file * (128 * 1024);
    sprintf(filename,"images/scene_%d.png", file );
    imageBufferLen[file] = Brain.SDcard.loadfile( filename, &imageBuffer[offset], 128 * 1024 );
    Brain.Screen.printAt( 10, 20, "Loading.. %3d", file );
  }    
}


void intro() {
  int   file = 0;

  introInit();

  repeat(140){
  Brain.Screen.clearScreen();
    int offset = file * (128 * 1024);
    
    Brain.Screen.drawImageFromBuffer(&imageBuffer[offset], 0, 0, imageBufferLen[file]);
    Brain.Screen.render();
    

    file ++;
    if(file == 239 )
      file = 3;
      wait(5,msec);
  }
  Brain.Screen.renderDisable();
}


int TestingMenu(){

    

   if(testing == false){
    auton = count + 7 * BotCount;
    }
  Brain.Screen.clearScreen(black);
  Brain.Screen.setPenColor(white);
  Brain.Screen.drawRectangle(20,20,100,70);
  Brain.Screen.printAt(25,50,"Calibrate");
  Brain.Screen.printAt(25,70,"Gyro");
  if(testing)
  {
  Brain.Screen.drawRectangle(20,100,110,70);
  Brain.Screen.printAt(25,130,"deactivate");
  Brain.Screen.printAt(25,150,"testing");
  }
  Brain.Screen.setPenColor(red);
  Brain.Screen.drawRectangle(300,175,75,50);
Brain.Screen.printAt(310,210,"Red");
Brain.Screen.setPenColor(blue);
  Brain.Screen.drawRectangle(400,175,75,50);
  Brain.Screen.printAt(410,210,"Blue");
  Brain.Screen.setPenColor(white);
  Brain.Screen.printAt(300,20,"count = %d", count);
  Brain.Screen.printAt(300,40,"Side = %d", BotCount);
  Brain.Screen.printAt(300,60,"driver = %d", driverCount);
  Brain.Screen.printAt(300,80,"Auton = %d", auton);
  if(testing){
        gyroCalibrate();
        
    }
  while(true)
  {
    
    waitUntil(Brain.Screen.pressing());
     waitUntil(!Brain.Screen.pressing() );

        waitUntil(!Brain.Screen.pressing());
    if(((Brain.Screen.xPosition() > 20) && (Brain.Screen.xPosition() < 120) && (Brain.Screen.yPosition() > 20) && (Brain.Screen.yPosition() < 100)))
    {
        
       
      gyroCalibrate();
      if(auton == 2)
      {
        
        startX = 88.5;
        startY = 16.5;

        Gyro.setRotation(90,deg);
      }
      else if(auton == 1 || auton == 3 || auton == 4)
      {
        startX = 17.5;
        startY = 102;
      }
      
      if(auton >= 5)
      {
        startX = 10;
        startY = 70;
        Gyro.setRotation(24,deg);
      }
      
        task asijasf(odomCalculations);
        
      
      Brain.Screen.setPenColor(white);
    }

    else  if(((Brain.Screen.xPosition() > 20) && (Brain.Screen.xPosition() < 120) && (Brain.Screen.yPosition() > 100) && (Brain.Screen.yPosition() < 220)) && testing == 1)
    {
        testing = 0;
        task asdiad(autonSelect);
        break;

    }

    else if((Brain.Screen.xPosition() > 300) && (Brain.Screen.xPosition() < 395) && (Brain.Screen.yPosition() > 175) && (Brain.Screen.yPosition() < 225))
    {
        Brain.Screen.setPenColor(blue);
        Brain.Screen.setFillColor(black);
        Brain.Screen.drawRectangle(400,175,75,50);
        Brain.Screen.printAt(410,210,"Blue");

        Brain.Screen.setPenColor(red);
        Brain.Screen.setFillColor(red);
        Brain.Screen.drawRectangle(300,175,75,50);
        Brain.Screen.setPenColor(white);
        Brain.Screen.printAt(310,210,"Red");
        lSideRail.clear(color(100,0,0));
        wait(10,msec);
        rSideRail.clear(color(100,0,0));
        rob = 1;
    }
    else if((Brain.Screen.xPosition() > 400) && (Brain.Screen.xPosition() < 495) && (Brain.Screen.yPosition() > 175) && (Brain.Screen.yPosition() < 225))
    {
        Brain.Screen.setPenColor(red);
        Brain.Screen.setFillColor(black);
        Brain.Screen.drawRectangle(300,175,75,50);
        Brain.Screen.printAt(310,210,"Red");

        Brain.Screen.setPenColor(blue);
        Brain.Screen.setFillColor(blue);
        Brain.Screen.drawRectangle(400,175,75,50);
        Brain.Screen.setPenColor(white);
        Brain.Screen.printAt(410,210,"Blue");
        lSideRail.clear(color(0,0,100));
        wait(10,msec);
        rSideRail.clear(color(0,0,100));
        rob = 2;
    }

   
  }
  return(0);
}


/**
    A function to get the 
    length of a string
*/
int strLen(const char *arr){
    int len = 0;
    while(arr[len] != '\0'){
        len++;
    }
    return len;
}

int autonSelect() {

   
    //Initialize strings
    /*
        ALL the values from here to the dashed
        line are values that can be changed. 
        These are the strings that are displayed
        when shifting through the choices.1
    */
    autonModes[0] = "Do Nothing";
    autonModes[1] = "";
    autonModes[2] = "Ball Rush";
    autonModes[3] = "Skills";
    autonModes[4] = "PID Tuning";
    autonModes[5] = "Do Nothing";
    autonModes[6] = "Do Nothing";

    Bots[0] = "Left";
    Bots[1] = "Right";

    drivers[0] = "Default(Left Arcade)";
    drivers[1] = "driver1(Shawn)";
    drivers[2] = "driver2(Jaden)";
    drivers[3] = "driver3(Left Split)";
    drivers[4] = "driver4(Right Split)";
    //--------------------------------
    //intro
    intro();
    //Initialize menu variables
    menuCount = 0;
    autonDone = false;
    BotDone = false;
    driverDone = false;
    reviewDone = false; 
    /* Sub-Menu Variable Initialization */
    //Autonomous Chooser
    count = 1;
    //side Chooser
    BotCount = 0;
    //driver Chooser
    driverCount = 0;
    //Run infinite loop
    while(true){
        switch(menuCount){
            //Autonomous chooser menu
            case 0:
                /*
                    In the case the "Start Over" button
                    was pressed, reset reviewDone.
                */
                reviewDone = false;
                //Clear screen
                Brain.Screen.clearScreen(vex::color::black);
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v2.0"); 
                //"Select Autonomous Mode" and selected mode display
                Brain.Screen.printAt(130, 50, "Select Autonomous Mode");
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(130, 70, 220, 50);
                //"Confirm" button
                Brain.Screen.setPenColor(vex::color::black);
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(380, 40, 80, 50);
                Brain.Screen.setPenColor(vex::color::black);
                Brain.Screen.printAt(385, 70, "Confirm");
                //"Previous" button
                Brain.Screen.setFillColor(vex::color::red);
                Brain.Screen.drawRectangle(130, 140, 100, 62);
                Brain.Screen.printAt(140, 175, "Previous");
                //"Next Button"
                Brain.Screen.drawRectangle(250, 140, 100, 62);
                Brain.Screen.printAt(280, 175, "Next");
                //"Nothing Button"
                Brain.Screen.setFillColor(vex::color::cyan);
                Brain.Screen.drawRectangle(370, 140, 100, 62);
                Brain.Screen.printAt(410, 165, "Do");
                Brain.Screen.printAt(385, 185, "Nothing");
                //Side Menus
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //Indicate current menu by showing a green square
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(10, 35, 15, 15);
                //side Sidemenu
                if(BotDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Side");
                //driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "Driver");
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27, 210, "Review");
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(!autonDone){
                    switch(count){
                        case 0:
                            //Clear out previous text in info box
                            Brain.Screen.setFillColor(vex::color::white);
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(185, 100, autonModes[count]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count = 6;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 1;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 1:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(195, 100, autonModes[count]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count = 6;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 2:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(185, 100, autonModes[count]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 3:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(200, 100, autonModes[count]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 4:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(180, 100, autonModes[count]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 5:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(180, 100, autonModes[count]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count++;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        case 6:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(190, 100, autonModes[count]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Previous" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                count--;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 1;
                            }
                            //"Nothing" box
                            else if(Brain.Screen.xPosition() > 370 && Brain.Screen.xPosition() < 470 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                count = 0;
                            } 
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                autonDone = true;
                                menuCount = 1;
                            }
                        break;
                        default:
                            count = 0;
                        break;
                    }//end auton switch   
                }//end auton while
            break;
            //Side chooser menu
            case 1:
                //Clear screen
                Brain.Screen.clearScreen(vex::color::black);
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //"Select side" and selected mode display
                Brain.Screen.printAt(170, 50, "Select Robot");
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(130, 70, 220, 50);
                //Set pen to black color
                Brain.Screen.setPenColor(vex::color::black);
                //"Confirm" button
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(380, 40, 80, 50);
                Brain.Screen.setPenColor(vex::color::black);
                Brain.Screen.printAt(385, 70, "Confirm");
                //"Previous" button
                Brain.Screen.setFillColor(vex::color::red);
                Brain.Screen.drawRectangle(130, 140, 100, 62);
                Brain.Screen.printAt(140, 175, "Left");
                //"Next Button"
                Brain.Screen.drawRectangle(250, 140, 100, 62);
                Brain.Screen.printAt(280, 175, "Right");
                //Side Menus
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //side Sidemenu
                if(BotDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Side");
                //Indicate current menu by showing a green square
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(10, 85, 15, 15);
                //driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "Driver");
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27, 210, "Review");
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(!BotDone){
                    switch(BotCount){
                        case 0:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(160, 100, Bots[BotCount]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Left" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                BotCount =0;
                            }
                            //"Right" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                BotCount = 1;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                BotDone = true;
                                menuCount = 2;
                            }
                        break;
                        case 1:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(160, 100, Bots[BotCount]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Left" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                BotCount = 0;
                            }
                            //"Right" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                BotCount = 1;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                BotDone = true;
                                menuCount = 2;
                            }
                        break;
                    }
                }
            break;
            //driver chooser menu
            case 2:
                //Clear screen
                Brain.Screen.clearScreen(vex::color::black);
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //"side side Control?" and selected mode display
                Brain.Screen.printAt(130, 50, "which Driver?");
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(130, 70, 220, 50);
                //Set pen to black color
                Brain.Screen.setPenColor(vex::color::black);
                //"Confirm" button
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(380, 40, 80, 50);
                Brain.Screen.setPenColor(vex::color::black);
                Brain.Screen.printAt(385, 70, "Confirm");
                //"Previous" button
                Brain.Screen.setFillColor(vex::color::red);
                Brain.Screen.drawRectangle(130, 140, 100, 62);
                Brain.Screen.printAt(145, 175, "Default");
                //"Next Button"
                Brain.Screen.drawRectangle(250, 140, 100, 62);
                Brain.Screen.printAt(290, 175, "Next");
                //Side Menus
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //side Sidemenu
                if(BotDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Side");
                //driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "driver");
                //Indicate current menu by showing a green square
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(10, 135, 15, 15);
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27, 210, "Review");
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(!driverDone){
                    switch(driverCount){
                        case 0:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(140, 100, drivers[driverCount]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Default" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                driverCount = 0;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                driverCount++;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                driverDone = true;
                                menuCount = 3;
                            }
                        break;
                        case 1:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(140, 100, drivers[driverCount]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Default" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                driverCount = 0;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                driverCount++;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                driverDone = true;
                                menuCount = 3;
                            }
                        break;
                        case 2:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(140, 100, drivers[driverCount]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Default" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                driverCount = 0;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                driverCount++;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                driverDone = true;
                                menuCount = 3;
                            }
                        break;
                        case 3:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(140, 100, drivers[driverCount]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Default" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                driverCount = 0;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                driverCount++;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                driverDone = true;
                                menuCount = 3;
                            }
                        break;
                        case 4:
                            //Clear out previous text in info box
                            Brain.Screen.drawRectangle(130, 70, 220, 50);
                            //Print out text
                            Brain.Screen.printAt(140, 100, drivers[driverCount]);
                            //Wait for press
                            waitUntil(Brain.Screen.pressing());
                            waitUntil(!Brain.Screen.pressing());//Wait for release
                            //"Default" box
                            if(Brain.Screen.xPosition() > 130 && Brain.Screen.xPosition() < 230 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){ 
                                driverCount = 0;
                            }
                            //"Next" box
                            else if(Brain.Screen.xPosition() > 250 && Brain.Screen.xPosition() < 350 && Brain.Screen.yPosition() > 140 && Brain.Screen.yPosition() < 202.5){
                                driverCount = 0;
                            }
                            //"Confirm" box
                            if(Brain.Screen.xPosition() > 380 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 40 && Brain.Screen.yPosition() < 90){
                                driverDone = true;
                                menuCount = 3;
                            }
                        break;
                        default:
                            driverCount = 0;
                        break;
                    }
                }
            break;
            //Review menu
            case 3:
                //Clear screen
                Brain.Screen.clearScreen(vex::color::black);
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //"Review" Text
                Brain.Screen.printAt(220, 50, "Review");
                //Information box headers
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.printAt(155, 90, "Autonomous Mode:");
                Brain.Screen.printAt(200, 140, "Side:");
                Brain.Screen.printAt(180, 190, "driver:");
                //Information boxes
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(145, 100, 180, 20);
                Brain.Screen.drawRectangle(145, 150, 180, 20);
                Brain.Screen.drawRectangle(145, 200, 180, 20);
                //Text in information boxes
                Brain.Screen.setPenColor(vex::color::black);
                /*------------Format to be in center-----------------*/
                //Display Autonomous Mode text
                //Initialize temporary string 
                const char *autonStr;
                //Set temp string
                autonStr = autonModes[count];
                //Initialize int for length of string
                int autonNumChar;
                //Set length of string
                autonNumChar = strLen(autonStr);
                //Initiaze int for padding
                int autonPadding;
                //Calculate the needed padding to center the string
                autonPadding = (180 - ((autonNumChar)*10))/2;
                //Print the string at a location with the offset of the padding
                Brain.Screen.printAt((145 + autonPadding), 116, autonModes[count]);
                //Display side text
                /* Format to be in center */
                //Initialize temporary string
                const char *BotStr;
                //Set temp string
                BotStr = Bots[BotCount];
                //Initialize int for length of string
                int BotNumChar;
                //Set length of string
                BotNumChar = strLen(BotStr);
                //Initiaze int for padding
                int BotPadding;
                //Calculate the needed padding to center the string
                BotPadding = (180 - ((BotNumChar)*10))/2;
                //Print the string at a location with the offset of the padding
                Brain.Screen.printAt((145 + BotPadding), 166, Bots[BotCount]);
                //Display driver text
                /* Format to be in center */
                //Initialize temporary string
                const char *driverStr;
                //Set temp string
                driverStr = drivers[driverCount];
                //Initialize int for length of string
                int driverNumChar;
                //Set length of string
                driverNumChar = strLen(driverStr);
                //Initiaze int for padding
                int driverPadding;
                //Calculate the needed padding to center the string
                driverPadding = (180 - ((driverNumChar)*10))/2;
                //Print the string at a location with the offset of the padding
                Brain.Screen.printAt((145 + driverPadding), 216, drivers[driverCount]);
                //Set pen to black color
                Brain.Screen.setPenColor(vex::color::black);
                //"Confirm" button
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(360, 60, 100, 50);
                Brain.Screen.printAt(375, 90, "Confirm");
                //"Start Over" Button
                Brain.Screen.setFillColor(vex::color::red);
                Brain.Screen.drawRectangle(360, 130, 100, 50);
                Brain.Screen.printAt(385, 152, "Start");
                Brain.Screen.printAt(390, 172, "Over");
                /*----------------Side Menus------------------*/
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //side Sidemenu
                if(BotDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Side");
                //driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "driver");
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27, 210, "Review");
                //Indicate current menu by showing a green square
                Brain.Screen.setFillColor(vex::color::green);
                Brain.Screen.drawRectangle(10, 185, 15, 15);
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(!reviewDone){
                    /*
                        These two lines of code seem counterintuitive,
                        but they are an effective way to wait for a press
                        and wait for a release.
                    */
                    waitUntil(Brain.Screen.pressing());
                    waitUntil(!Brain.Screen.pressing());//Wait for release
                    //"Confirm" box
                    if(Brain.Screen.xPosition() > 360 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 60 && Brain.Screen.yPosition() < 110){
                        reviewDone = true;
                        menuCount = 4;
                    } 
                    //"Start Over" button
                    if(Brain.Screen.xPosition() > 360 && Brain.Screen.xPosition() < 460 && Brain.Screen.yPosition() > 130 && Brain.Screen.yPosition() < 180){
                        //Default all values
                        autonDone = false;
                        BotDone = false;
                        driverDone = false;
                        count = 1;
                        BotCount = 0;
                        driverCount = 0;
                        menuCount = 0;
                        //Set reviewDone to true to escape loop
                        break;
                    }
                }
            break;
            //Post-Review Menu
            case 4:
                Brain.Screen.clearScreen();
                //Initial Text
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.setPenColor(vex::color::white);
                Brain.Screen.printAt(110, 20, "Pre-Autonomous Chooser v1.0"); 
                //Information box headers
                Brain.Screen.setFillColor(vex::color::black);
                Brain.Screen.printAt(155, 70, "Autonomous Mode:");
                Brain.Screen.printAt(200, 120, "Side:");
                Brain.Screen.printAt(180, 170, "driver:");
                //Information boxes
                Brain.Screen.setFillColor(vex::color::white);
                Brain.Screen.drawRectangle(145, 80, 180, 20);
                Brain.Screen.drawRectangle(145, 130, 180, 20);
                Brain.Screen.drawRectangle(145, 180, 180, 20);
                //Text in information boxes
                Brain.Screen.setPenColor(vex::color::black);
                /*----------Format to be in center-----------------*/
                //Display Autonomous Mode text
                Brain.Screen.printAt((145 + autonPadding), 96, autonModes[count]);
                //Display side text
                /* Format to be in center */
                Brain.Screen.printAt((145 + BotPadding), 146, Bots[BotCount]);
                //Display driver text
                /* Format to be in center */
                Brain.Screen.printAt((145 + driverPadding), 196, drivers[driverCount]);
                //Set pen to black color
                Brain.Screen.setPenColor(vex::color::black);
                /*----------------Side Menus------------------*/
                //Auton Selection Sidemenu
                if(autonDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 35, 100, 40);
                Brain.Screen.printAt(35, 60, "Auton");
                //side Sidemenu
                if(BotDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 85, 100, 40);
                Brain.Screen.printAt(30, 110, "Side");
                //driver Sidemenu
                if(driverDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 135, 100, 40);
                Brain.Screen.printAt(25, 160, "driver");
                //Review Sidemenu
                if(reviewDone){
                    Brain.Screen.setFillColor(vex::color::green);
                }else{
                    Brain.Screen.setFillColor(vex::color::orange);
                }
                Brain.Screen.drawRectangle(10, 185, 100, 40);
                Brain.Screen.printAt(27, 210, "Review");
                //Set default text color
                Brain.Screen.setFillColor(vex::color::white);
                while(true){}
            break;
            default:
                
            break;
        }//end menu switch
        if(reviewDone)
        {
        break;
        }
        wait(5,msec);
    }//end infinite loop
    task auauto(TestingMenu);
    return(0);
    //end main
}