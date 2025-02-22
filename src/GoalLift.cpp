//include vex.h and the header file you created
#include "vex.h"
#include "GoalLift.h"
#include "AutonSelection.h"
#include <math.h>
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

//Catapult rotation sensor values-------------------------------------------------------------------------
int upAngle = 139;
int downAngle = 234;
int midAngle = 180;

bool cata = false;

//int upAngle = 95;
//int downAngle = 12;
//int midAngle = 180;

//Function to stop the motors
void liftgoal::stop(){}

//Function to stop all the drive motors with a specified brake type
void liftgoal::stop(brakeType type){}

void liftgoal::spin(float pwr){}

void liftgoal::spin(float lPwr, float rPwr){}

double liftgoal::angle(){return 0;}


void liftgoal::lift(float speed){}

void liftgoal::lower(float speed){
}

//Task to run the drive and associated mechanisms
int FerrisWheel(){
    
    bool toggleferris = 0;
    std::cout << "test" << std::endl;
    while(true){
         //pto shift open button
        if(Controller1.ButtonDown.pressing() && !toggleferris){
            clamp.open();
            toggleferris = 1;
            waitUntil(!Controller1.ButtonR1.pressing() & !Controller1.ButtonDown.pressing());
        }
        //pto shift close button
        else if(Controller1.ButtonDown.pressing() && toggleferris){
            clamp.close();
            toggleferris = 0;
            waitUntil(!Controller1.ButtonR1.pressing() & !Controller1.ButtonDown.pressing());
        }

        


        wait(10,msec);
    }
}
