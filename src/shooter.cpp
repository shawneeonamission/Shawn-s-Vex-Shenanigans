//include vex.h and the header file you created
#include "vex.h"
#include "shooter.h"
#include "FrontVision.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

//Catapult rotation sensor values-------------------------------------------------------------------------
int upAngle = 5;
int downAngle = 95;

//Function to stop the motors
void shooter::stop(){
    wShooter.stop(brake);

}

//Function to stop all the drive motors with a specified brake type
void shooter::stop(brakeType type){
    wShooter.stop(type);
}

void shooter::spin(float pwr){

    wShooter.spin(fwd,pwr,pct);
}

void shooter::fire(float speed){
    spin(100);
    waitUntil(cataRot.angle(deg) < upAngle);
    waitUntil(cataRot.angle(deg) > downAngle);
    stop(hold);
}

void shooter::pullBack(float speed){
    spin(100);
    waitUntil(cataRot.angle(deg) > downAngle);
    stop(hold);
}





//Task to run the drive and associated mechanisms
int Shoot(){
    while(true){
        
        if(Controller1.ButtonL2.pressing()){
            Shooter.fire(100);
            waitUntil(!Controller1.ButtonR2.pressing());
        }

        wait(10,msec);
    }
}