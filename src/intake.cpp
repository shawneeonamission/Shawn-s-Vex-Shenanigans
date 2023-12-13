//include vex.h and the header file you created
#include "vex.h"
#include "intake.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

void feeder::in(float prct){
  intoggle = 1;
  wIntake.spin(fwd,prct,pct);
}
void feeder::out(float prct){
  intoggle = 2;
  wIntake.spin(reverse,prct,pct);
}
void feeder::stop(){
    intoggle = 0;
    wIntake.stop();
}

int upToggle = 0;
int outToggle = 0;

int intakeControl(){
    while(true){

        if(Controller1.ButtonR1.pressing() && intoggle != 1){
            intake.in(100);
            waitUntil(!Controller1.ButtonR1.pressing());
        }
        else if(Controller1.ButtonR2.pressing() && intoggle != 2){
            int previntoggle = intoggle;
            intake.out(100);
            waitUntil(!Controller1.ButtonR2.pressing());
            if(intoggle == 1){
                intake.in(200);
            }
            else{
                intake.stop();
            }
        }
        if(Controller1.ButtonLeft.pressing() && !outToggle){
            intakeOut.open();
            outToggle = 1;
            waitUntil(!Controller1.ButtonLeft.pressing());
        }
        else if(Controller1.ButtonLeft.pressing() && outToggle){
            intakeOut.close();
            outToggle = 0;
            waitUntil(!Controller1.ButtonLeft.pressing());
        }
        if(Controller1.ButtonUp.pressing() && !upToggle){
            intakeTilt.open();
            upToggle = 1;
            waitUntil(!Controller1.ButtonUp.pressing());
        }
        else if(Controller1.ButtonUp.pressing() && upToggle){
            intakeTilt.close();
            upToggle = 0;
            waitUntil(!Controller1.ButtonUp.pressing());
        }
        wait(10,msec);
    }
}