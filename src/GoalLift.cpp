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
void liftgoal::stop(){
    goalLift.stop(brake);

}

//Function to stop all the drive motors with a specified brake type
void liftgoal::stop(brakeType type){
    goalLift.stop(type);
}

void liftgoal::spin(float pwr){

    goalLift.spin(fwd,pwr,pct);
}

void liftgoal::spin(float lPwr, float rPwr){

    rLift.spin(fwd,rPwr,pct);
    lLift.spin(fwd,lPwr,pct);
}

double liftgoal::angle(){
    return goalLift.position(deg)/5;
}


void liftgoal::lift(float speed){
    spin(speed);
    waitUntil(angle() >= 130);
    stop(hold);
    
}

void liftgoal::lower(float speed){
    spin(-speed);
    waitUntil(angle() <= 0);
    stop(brake);
}

//Task to run the drive and associated mechanisms
int FerrisWheel(){
    goalLift.resetPosition();
    bool toggleferris = 0;
    std::cout << "test" << std::endl;
    while(true){
        
        if(Controller1.ButtonDown.pressing() && toggleferris == 0){
            
            choo.lift(100);
            toggleferris = 1;
            waitUntil(!Controller1.ButtonB.pressing());
            std::cout << "test2: " << choo.angle() << std::endl;
        }
        else if(Controller1.ButtonDown.pressing() && toggleferris){
            
            choo.lower(100);
            toggleferris = 0;
            waitUntil(!Controller1.ButtonB.pressing());
            std::cout << "test3: " << choo.angle() << std::endl;
        }
        else{
            choo.stop(brake);
        }
         //pto shift open button
        if(Controller1.ButtonR1.pressing() && !toggleferris && status == linkType::worker){
            clamp.open();
            toggleferris = 1;
            waitUntil(!Controller1.ButtonR1.pressing());
        }
        //pto shift close button
        else if(Controller1.ButtonR1.pressing() && toggleferris && status == linkType::worker){
            clamp.close();
            toggleferris = 0;
            waitUntil(!Controller1.ButtonR1.pressing());
        }

        //Shift Button
        while(Controller1.ButtonB.pressing()){
            if(Controller1.ButtonR1.pressing()){

                choo.spin(50);
                waitUntil(!Controller1.ButtonR1.pressing());
            }
            else if(Controller1.ButtonR2.pressing()){

                choo.spin(-50);
                waitUntil(!Controller1.ButtonR2.pressing());
            }
            else{
                choo.stop(brake);
            }
            if(Controller1.ButtonA.pressing()){
                goalLift.resetPosition();
                waitUntil(!Controller1.ButtonA.pressing());
            }
        }


        wait(10,msec);
    }
}
