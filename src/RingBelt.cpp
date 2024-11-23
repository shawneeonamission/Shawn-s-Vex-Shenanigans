//include vex.h and the header file you created
#include "vex.h"
#include "RingBelt.h"
#include "GoalLift.h"
#include "AutonSelection.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;


void hooks::spin(float prct){
  ringBelt.spin(fwd,prct,pct);
}

void hooks::stop(){
    chainBar.stop(brake);
}
void hooks::stop(brakeType type){
    chainBar.stop(type);
}

int beltState = 0;

int ringBeltControl(){
    while(true){
        
        if(Controller1.ButtonR1.pressing() && beltState != 1){
            belt.spin(100);
            beltState = 1;
            waitUntil(!(Controller1.ButtonR1.pressing()));
        }
        else if(Controller1.ButtonR2.pressing() && beltState != 2){
            belt.spin(-100);
            waitUntil(!(Controller1.ButtonR2.pressing()));
            if(beltState == 1){
                belt.spin(100);
            }
            else{
                belt.stop();
            }
        }
        else if(((Controller1.ButtonR1.pressing()  && driverCount == 1) || (Controller1.ButtonL1.pressing()  && driverCount == 2)) && beltState == 1){
            belt.stop();
            beltState = 0;
            waitUntil(!(Controller1.ButtonR1.pressing()) && !(Controller1.ButtonL1.pressing()));
        }
        //Shift Key
        while(Controller1.ButtonB.pressing()){
        if(Controller1.ButtonL1.pressing()){
            belt.spin(50);
            waitUntil(!Controller1.ButtonL1.pressing());
        }
        else if(Controller1.ButtonL2.pressing()){
            belt.spin(-50);
            waitUntil(!Controller1.ButtonL2.pressing());
        }
        else{
            belt.stop(hold);
        }
        }

       
        
        wait(10,msec);
    }
    return 0;
}            