//include vex.h and the header file you created
#include "vex.h"
#include "ChainBar.h"
#include "GoalLift.h"
#include "AutonSelection.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

int ringBarAngle = 0;

void ringBar::spin(float prct){
  chainBar.spin(fwd,prct,pct);
}

void ringBar::stop(){
    chainBar.stop(brake);
}
void ringBar::stop(brakeType type){
    chainBar.stop(type);
}

void ringBar::lift(double angle){
    spin(100);
    waitUntil(chainRot.position(deg) > angle - 135);
    stop(hold);
}


int chainState = 0;
int staketoggle = 0;

int chainBarControl(){
    while(true){
        if(!staketoggle){
            if(Controller1.ButtonR1.pressing() && chainState != 1){
            chain.spin(100);
            chainState = 1;
            waitUntil(!(Controller1.ButtonR1.pressing()));
        }
        else if(Controller1.ButtonR2.pressing() && chainState != 2){
            chain.spin(-100);
            waitUntil(!(Controller1.ButtonR2.pressing()));
            if(chainState == 1){
                chain.spin(100);
            }
            else{
                chain.stop();
            }
        }
        else if(((Controller1.ButtonR1.pressing()  && driverCount == 1) || (Controller1.ButtonL1.pressing()  && driverCount == 2)) && chainState == 1){
            chain.stop();
            chainState = 0;
            waitUntil(!(Controller1.ButtonR1.pressing()) && !(Controller1.ButtonL1.pressing()));
        }
        }
        
        else {
            if(Controller1.ButtonR1.pressing()){
                chain.lift(90);
                waitUntil(!(Controller1.ButtonR1.pressing()));
                
            }
            else if(Controller1.ButtonR2.pressing()){
                chain.stop(coast);
                waitUntil(!(Controller1.ButtonR2.pressing()));
            }
        }
        //Shift Key
        while(Controller1.ButtonB.pressing()){
        if(Controller1.ButtonL1.pressing()){
            chain.spin(50);
            waitUntil(!Controller1.ButtonL1.pressing());
        }
        else if(Controller1.ButtonL2.pressing()){
            chain.spin(-50);
            waitUntil(!Controller1.ButtonL2.pressing());
        }
        else{
            chain.stop(hold);
        }
        //pto shift open button
        if(Controller1.ButtonLeft.pressing() && !staketoggle){
            shift.open();
            staketoggle = 1;
            waitUntil(!Controller1.ButtonLeft.pressing());
        }
        //pto shift close button
        else if(Controller1.ButtonLeft.pressing() && staketoggle){
            shift.close();
            staketoggle = 0;
            waitUntil(!Controller1.ButtonLeft.pressing());
        }
        }

       
        
        wait(10,msec);
    }
    return 0;
}            