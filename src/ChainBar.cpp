//include vex.h and the header file you created
#include "vex.h"
#include "ChainBar.h"
#include "GoalLift.h"
#include "AutonSelection.h"
#include <iostream>
#include <thread>

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
    if(chainRot.installed()){
    waitUntil(chainRot.position(deg) > angle || Controller1.ButtonB.pressing());
    }
    else{
        waitUntil(chainBar.position(deg) > angle * 5 || Controller1.ButtonB.pressing());
    }
    stop(hold);
}
void ringBar::goTo(double angle){
    if(chainRot.installed()){
    
    if(chainRot.position(deg) < angle){
        lift(angle);
    }else{
        lower(angle);
    }
    }
    else{
        waitUntil(chainBar.position(deg) > angle * 5 || Controller1.ButtonB.pressing());
        if(chainBar.position(deg) / 5.0 < angle){
            lift(angle);
        }else{
            lower(angle);
        }
    }
    stop(hold);
}

// New function to lift the chain bar using an instance
int liftTaskFunction(void* param) {
    double angle = *(double*)param;
    // Call the lift function on the ringBar instance
    chain.lift(angle);
    return 0; // End of task
}
// Updated startLift function
void ringBar::startLift(double angle) {
    task liftTask(liftTaskFunction, &angle); // Start the task
}

void ringBar::lower(double angle){
    spin(-100);
    if(chainRot.installed()){
    waitUntil(chainRot.position(deg) < angle || Controller1.ButtonB.pressing());
    }
    else{
        waitUntil(chainBar.position(deg) < angle * 5 || Controller1.ButtonB.pressing());
    }
    stop(hold);
}


int chainState = 0;


int chainBarControl(){
    chainRot.resetPosition();
    chainBar.resetPosition();
    if(!chainRot.installed()){
        chain.lift(45);
        chainState = 1;
    }
    while(true){

        if(status == linkType::manager){
            if(Controller1.ButtonR1.pressing()){
                chain.lift(95);
                intakeLift.open();
                waitUntil(!(Controller1.ButtonR1.pressing()));
                
            }
            else if(Controller1.ButtonR2.pressing()){
                chain.spin(-50);
                intakeLift.close();
                waitUntil(!(Controller1.ButtonR2.pressing()));
                chain.stop(coast);
                
            }
        }
        else if(status == linkType::worker){
            if(Controller1.ButtonR1.pressing() && chainState < 2){
                chain.lift(95);
                intakeLift.open();
                chainState = 2;
                waitUntil(!(Controller1.ButtonR1.pressing()));
                
            }
            else if(Controller1.ButtonR1.pressing() && chainState == 2){
                chain.lift(180);
                intakeLift.open();
                chainState = 3;
                waitUntil(!(Controller1.ButtonR1.pressing()));
                
            }
            else if(Controller1.ButtonR1.pressing() && chainState == 3){
                chain.lift(215);
                intakeLift.open();
                chainState = 4;
                waitUntil(!(Controller1.ButtonR1.pressing()));
                
            }
            if(Controller1.ButtonR2.pressing() && chainState > 1){
                chain.lower(45);
                intakeLift.close();
                chainState = 1;
                waitUntil(!(Controller1.ButtonR2.pressing()));
               
                
            }
            else if(Controller1.ButtonR2.pressing() && chainState == 1){
                chain.lower(15);
                chainState = 0;
                waitUntil(!(Controller1.ButtonR2.pressing()));
            }
        }
       
        
        //Shift Key
        while(Controller1.ButtonB.pressing()){
        if(Controller1.ButtonR1.pressing()){
            chain.spin(50);
            waitUntil(!Controller1.ButtonL1.pressing());
        }
        else if(Controller1.ButtonR2.pressing()){
            chain.spin(-50);
            waitUntil(!Controller1.ButtonL2.pressing());
        }
        else{
            chain.stop(hold);
        }
        
        }

       
        
        wait(10,msec);
    }
    return 0;
}            