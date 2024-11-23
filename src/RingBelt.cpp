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
    ringBelt.stop(brake);
}
void hooks::stop(brakeType type){
    ringBelt.stop(type);
}

int beltState = 0;

int ringBeltControl(){
    ringColor.setLightPower(50,pct);
    ringColor.setLight(ledState::on);

    while(true){
        if(status == linkType::manager){
            if(Controller1.ButtonL1.pressing() && beltState == 0){
                belt.spin(100);
                beltState = 1;
                waitUntil(!(Controller1.ButtonL1.pressing()));
            }
            else if(Controller1.ButtonL2.pressing()){
                belt.spin(-50);
                waitUntil(!(Controller1.ButtonL2.pressing()));
                belt.stop();
                beltState = 0;
            }
            else if(Controller1.ButtonL1.pressing() && beltState == 1){
                belt.stop();
                beltState = 0;
                waitUntil(!(Controller1.ButtonL1.pressing()));
            }
        }
        else{
            if(Controller1.ButtonL1.pressing() && beltState == 0){
                belt.spin(10);
                beltState = 1;
                waitUntil(!(Controller1.ButtonL1.pressing()));
            }
            else if(Controller1.ButtonL2.pressing()){
                belt.spin(-50);
                waitUntil(!(Controller1.ButtonL2.pressing()));
                belt.stop();
                beltState = 0;
            }
            else if(Controller1.ButtonL1.pressing() && beltState == 1){
                belt.spin(100);
                
                waitUntil(!(Controller1.ButtonL1.pressing()));
                belt.spin(10);
            }
        }
        if(beltState == 1 && ringBelt.velocity(rpm) < 5){
            belt.spin(-50);
            wait(500,msec);
            belt.spin(status == linkType::manager ? 100 : 10);
            wait(200,msec);
        }
        //load thingy
        if(Controller1.ButtonLeft.pressing() && beltState == 1){
            
            belt.spin(50);
            while(!ringColor.isNearObject()){
                if(beltState == 1 && ringBelt.velocity(rpm) < 5){
                    belt.spin(-50);
                    wait(500,msec);
                    belt.spin(50);
                }   
                wait(5,msec);
            }
            belt.spin(10);
            waitUntil(!ringColor.isNearObject());
            belt.spin(-25);
            wait(1,sec);
            belt.spin(100);
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