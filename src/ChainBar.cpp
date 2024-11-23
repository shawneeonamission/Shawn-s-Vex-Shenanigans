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
    waitUntil(chainRot.position(deg) > angle);
    stop(hold);
}
// New function to lift the chain bar using an instance
int liftTaskFunction(void* param) {
    double* myParam = static_cast<double*>(param);
    double angle = *myParam;
    // Call the lift function on the ringBar instance
    chain.lift(angle);
    return 0; // End of task
}
// Updated startLift function
void ringBar::startLift(double angle) {
    task liftTask(liftTaskFunction, &angle); // Start the task
}


int chainState = 0;


int chainBarControl(){
    chainRot.resetPosition();
    while(true){
        
            if(Controller1.ButtonR1.pressing() && status == linkType::manager){
                chain.lift(95);
                hang.open();
                waitUntil(!(Controller1.ButtonR1.pressing()));
                
            }
            else if(Controller1.ButtonR2.pressing() && status == linkType::manager){
                chain.spin(-50);
                hang.close();
                waitUntil(!(Controller1.ButtonR2.pressing()));
                chain.stop(coast);
                
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
        
        }

       
        
        wait(10,msec);
    }
    return 0;
}            