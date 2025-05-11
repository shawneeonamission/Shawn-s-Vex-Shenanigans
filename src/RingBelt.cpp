//include vex.h and the header file you created
#include "vex.h"
#include "RingBelt.h"
#include "GoalLift.h"
#include "ChainBar.h"
#include "AutonSelection.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

int load = 0;


void hooks::spin(float prct){
  ringBelt.spin(fwd,prct,pct);
}
void hooks::spinFor(double rotation, rotationUnits units, double pwr){
    ringBelt.resetPosition();
    spin(pwr);
    waitUntil(fabs(ringBelt.position(units)) > fabs(rotation));
    stop(brake);
}
void hooks::spinFor(double time, timeUnits units, double pwr){
    ringBelt.resetPosition();
    spin(pwr);
    wait(time,units);
    stop(brake);
}

void hooks::stop(){
    ringBelt.stop(brake);
}
void hooks::stop(brakeType type){
    ringBelt.stop(type);
}
void hooks::loadThingy(){
    if(chainRot.installed()){
        load = 1;
        while(intakeSens.value(range12bit) > 2500){
            /*if(ringBelt.velocity(rpm) < 5){
                belt.spin(-50);
                wait(500,msec);
                belt.spin(100);
                wait(200,msec);
            }*/
            wait(5,msec);
        }
        load = 2;
        wait(200,msec);
        waitUntil(intakeSens.value(range12bit) > 2500);
        load = 3;

        belt.spin(50);
        waitUntil(ringColor.isNearObject());
        load = 4;
        belt.spin(10);
        waitUntil(!ringColor.isNearObject());
        load = 5;
        belt.spin(-25);
        wait(1,sec);
        belt.spin(100);
        load = 0;
    }else{
        load = 1;
        chain.lower(15);
        load = 2;
        belt.spin(100);
        waitUntil(ringBelt.velocity(rpm) < 5 || Controller1.ButtonB.pressing());
        load = 3;
        ringBelt.resetPosition();
        belt.spin(-10);
        waitUntil(ringBelt.position(deg) < -27);
        load = 4;
        belt.stop();
        chain.lift(95);
        load = 0;
        chainState = 2;
    }
}

int beltState = 0;
timer beltTimer = timer();
int ringBeltControl(){
    ringColor.setLightPower(50,pct);
    ringColor.setLight(ledState::on);

    while(true){
        if(chainState == 0){
            ringBelt.setMaxTorque(50,pct);
        }else{
            ringBelt.setMaxTorque(100,pct);
        }
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
        
        if(beltState == 1 && ringBelt.velocity(rpm) < 5){
            belt.spin(-50);
            wait(500,msec);
            belt.spin(100);
            wait(200,msec);
        }
        //load thingy
        if(Controller1.ButtonLeft.pressing() && beltState == 1){
            belt.loadThingy();
        }
        if(ringColor.isNearObject()){
            std::cout << "Close: "<< ringColor.hue() << std::endl;
            waitUntil(ringColor.hue() > 60 || ringColor.hue() < 50);
        //color sorting
        if((ringColor.hue() < 25 || ringColor.hue() > 300) && rob == 2 && beltState == 1){
        std::cout << "Red: "<< ringColor.hue() << " , "<< rob << std::endl;
        belt.stop(coast);
        beltTimer.clear();
        wait(500,msec);
        belt.spin(100);
        wait(200,msec);

        }
        //color sorting
        if((ringColor.hue() > 200 && ringColor.hue() < 300) && rob == 1 && beltState == 1)
        {
        std::cout << "Blue: " << ringColor.hue() << " , "<< rob << std::endl;
        belt.stop(coast);
        beltTimer.clear();
        wait(500,msec);
        belt.spin(100);
        wait(200,msec);
        }
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