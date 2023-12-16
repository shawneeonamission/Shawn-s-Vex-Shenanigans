//include vex.h and the header file you created
#include "vex.h"
#include "intake.h"
#include "AutonSelection.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

int intoggle = 0;

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
            intake.in(75);
            waitUntil(!Controller1.ButtonR1.pressing());
        }
        else if((Controller1.ButtonR2.pressing()  && driverCount != 3) || (Controller1.ButtonB.pressing()  && driverCount == 3) && intoggle != 2){
            int previntoggle = intoggle;
            intake.out(100);
            waitUntil(!(Controller1.ButtonR2.pressing()) && !(Controller1.ButtonB.pressing()));
            if(previntoggle == 1){
                intake.in(75);
            }
            else{
                intake.stop();
            }
        }
        else if(Controller1.ButtonR1.pressing() && intoggle == 1){
            intake.stop();
            waitUntil(!Controller1.ButtonR1.pressing());
        }
        if(((Controller1.ButtonLeft.pressing()  && driverCount != 3) || (Controller1.ButtonL2.pressing()  && driverCount == 3)) && !outToggle){
            intakeOut.open();
            outToggle = 1;
            waitUntil(!(Controller1.ButtonLeft.pressing()) && !(Controller1.ButtonL2.pressing()));
        }
        else if(((Controller1.ButtonLeft.pressing()  && driverCount != 3) || (Controller1.ButtonL2.pressing()  && driverCount == 3)) && outToggle){
            intakeOut.close();
            outToggle = 0;
            waitUntil(!(Controller1.ButtonLeft.pressing()) && !(Controller1.ButtonL2.pressing()));
        }
        if(((Controller1.ButtonUp.pressing()  && driverCount != 3) || (Controller1.ButtonL1.pressing()  && driverCount == 3)) && !upToggle){
            intakeTilt.open();
            upToggle = 1;
            waitUntil(!(Controller1.ButtonUp.pressing()) && !(Controller1.ButtonL1.pressing()));
        }
        else if(((Controller1.ButtonUp.pressing()  && driverCount != 3) || (Controller1.ButtonL1.pressing()  && driverCount == 3)) && upToggle){
            intakeTilt.close();
            upToggle = 0;
            waitUntil(!(Controller1.ButtonUp.pressing()) && !(Controller1.ButtonL1.pressing()));
        }
        wait(10,msec);
    }
}