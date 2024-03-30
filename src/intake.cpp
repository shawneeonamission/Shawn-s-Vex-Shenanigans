//include vex.h and the header file you created
#include "vex.h"
#include "intake.h"
#include "shooter.h"
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

        if(((Controller1.ButtonR1.pressing()  && driverCount == 1) || (Controller1.ButtonL1.pressing()  && driverCount == 2)) && intoggle != 1){
            intake.in(85);
            waitUntil(!(Controller1.ButtonR1.pressing()) && !(Controller1.ButtonL1.pressing()));
        }
        else if((Controller1.ButtonR2.pressing()  && driverCount == 1) || (Controller1.ButtonL2.pressing()  && driverCount == 2) && intoggle != 2){
            int previntoggle = intoggle;
            intake.out(100);
            waitUntil(!(Controller1.ButtonR2.pressing()) && !(Controller1.ButtonL2.pressing()));
            if(previntoggle == 1){
                intake.in(85);
            }
            else{
                intake.stop();
            }
        }
        else if(((Controller1.ButtonR1.pressing()  && driverCount == 1) || (Controller1.ButtonL1.pressing()  && driverCount == 2)) && intoggle == 1){
            intake.stop();
            waitUntil(!(Controller1.ButtonR1.pressing()) && !(Controller1.ButtonL1.pressing()));
        }
        if(((Controller1.ButtonLeft.pressing()  && driverCount == 1) || (Controller1.ButtonB.pressing()  && driverCount == 2)) && !outToggle){
            intakeOut.open();
            outToggle = 1;
            waitUntil(!(Controller1.ButtonLeft.pressing()) && !(Controller1.ButtonB.pressing()));
        }
        else if(((Controller1.ButtonLeft.pressing()  && driverCount == 1) || (Controller1.ButtonB.pressing()  && driverCount == 2)) && outToggle){
            intakeOut.close();
            outToggle = 0;
            waitUntil(!(Controller1.ButtonLeft.pressing()) && !(Controller1.ButtonB.pressing()));
        }
        if(((Controller1.ButtonUp.pressing()  && driverCount == 1) || (Controller1.ButtonR2.pressing()  && driverCount == 2)) && !upToggle){
            intakeTilt.open();
            upToggle = 1;
            waitUntil(!(Controller1.ButtonUp.pressing()) && !(Controller1.ButtonR2.pressing()));
        }
        else if(((Controller1.ButtonUp.pressing()  && driverCount == 1) || (Controller1.ButtonR2.pressing()  && driverCount == 2)) && upToggle){
            intakeTilt.close();
            upToggle = 0;
            waitUntil(!(Controller1.ButtonUp.pressing()) && !(Controller1.ButtonR2.pressing()));
        }
        if(Controller1.ButtonRight.pressing()){
            intakeTilt.open();
            upToggle = 1;
            if(outToggle == 0){
                intakeOut.open();
                outToggle = 1;
            }
            intake.in(90);
            wait(400,msec);
            if(Shooter.angle() < downAngle){
                Shooter.fire(100);
            }
            wait(400,msec);
            while(Controller1.ButtonRight.pressing()){
                intakeTilt.close();
                wait(400,msec);
                intakeTilt.open();
                wait(800,msec);
                while(intakeDie.objectDistance(mm) > 100 && Controller1.ButtonRight.pressing()){
                    intakeTilt.close();
                    wait(400,msec);
                    intakeTilt.open();
                    wait(1200,msec);
                }
                wait(200,msec);
                Shooter.fire(80);

            }
        }
        wait(10,msec);
    }
}