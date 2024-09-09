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
void ringBar::autoStakeLift(){
    if(chainRot.position(deg) > 85){
        spin(-100);
    waitUntil(chainRot.position(deg) <= 85 || Controller1.ButtonB.pressing());
    stop(hold);
    }
    else{
        spin(100);
    waitUntil(chainRot.position(deg) >= 85 || Controller1.ButtonB.pressing());
    stop(hold);
    }
}
void ringBar::autoLower(){
    if(chainRot.position(deg) > 18){
        spin(-100);
    waitUntil(chainRot.position(deg) <= 25 || Controller1.ButtonR1.pressing() || Controller1.ButtonB.pressing());
    stop(hold);
    }
    else{
        spin(100);
    waitUntil(chainRot.position(deg) >= 25 || Controller1.ButtonR1.pressing() || Controller1.ButtonB.pressing());
    stop(hold);
    }
}
void ringBar::autoPickup(){
    spin(-100);
    waitUntil(chainRot.position(deg) <= 30 || Controller1.ButtonB.pressing());
    stop(hold);
    stake.close();
    wait(500,msec);
    spin(-50);
    waitUntil(chainRot.position(deg) <= 6 || Controller1.ButtonB.pressing());
    chain.stop(coast);
    wait(200,msec);
    stake.open();
    wait(200,msec);
    spin(50);
    waitUntil(chainRot.position(deg) >= 20 || Controller1.ButtonB.pressing());

}

void ringBar::autoDeposit(){
    spin(100);
    waitUntil(chainRot.position(deg) >= 170 || Controller1.ButtonB.pressing());
    stake.close();
    wait(500,msec);
    stop(coast);
    waitUntil(stakeDie.objectDistance(mm) > 120 || Controller1.ButtonB.pressing());
    spin(-100);
    waitUntil(chainRot.position(deg) <= 25 || Controller1.ButtonB.pressing());
    stop(hold);

}

int chainState = 0;
int staketoggle = 0;

int ringBarControl(){
    while(true){

        if(Controller1.ButtonR1.pressing()){
            chain.autoStakeLift();
            waitUntil(!Controller1.ButtonR1.pressing());
        }
        else if(Controller1.ButtonR2.pressing()){
            chain.autoLower();
            waitUntil(!Controller1.ButtonR2.pressing());
        }

        else if(Controller1.ButtonL2.pressing()){
            chain.autoPickup();
            if(stakeDie.objectDistance(mm) < 30){
                chain.autoDeposit();
            }
            waitUntil(!Controller1.ButtonL2.pressing());
        }
        else{
            chain.stop(hold);
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
        //stake close button
        if(Controller1.ButtonLeft.pressing() && !staketoggle){
            stake.open();
            staketoggle = 1;
            waitUntil(!Controller1.ButtonLeft.pressing());
        }
        //stake open button
        else if(Controller1.ButtonLeft.pressing() && staketoggle){
            stake.close();
            staketoggle = 0;
            waitUntil(!Controller1.ButtonLeft.pressing());
        }
        }

       
        
        wait(10,msec);
    }
}            