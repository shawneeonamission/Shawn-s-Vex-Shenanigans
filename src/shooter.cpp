//include vex.h and the header file you created
#include "vex.h"
#include "shooter.h"
#include "AutonSelection.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

//Catapult rotation sensor values-------------------------------------------------------------------------
//int upAngle = 139;
//int downAngle = 223;
//int midAngle = 180;

int upAngle = 95;
int downAngle = 12;
int midAngle = 180;

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
    spin(speed);
    if(cataRot.angle(deg) < downAngle + 20){
    wShooter.spinFor(30,deg);
    waitUntil(cataRot.angle(deg) < upAngle);
    wait(200,msec);
    }
    
    double p = fabs(downAngle - cataRot.angle(deg));
    double lastP = p;
    double d = p - lastP;
    while(1){
        p = fabs(downAngle - cataRot.angle(deg));
        std::cout << cataRot.angle(deg) << std::endl;
        p *= .85;
        d = p - lastP;
        lastP = p;
        d *= 2;
    if(p > speed){p = speed;}
    spin(p + d);
    if(p < 2){break;}
    }
    stop(hold);
    
}

void shooter::pullBack(double angle,float speed){
    double p = fabs(angle - cataRot.angle(deg));
    double lastP = p;
    double d = p - lastP;
    while(1){
        p = angle - cataRot.angle(deg);

        p *= .7;
        d = p - lastP;
        lastP = p;
        d *= 2;
    if(p > speed){p = speed;}
    spin(p + d);
    if(p < 2){break;}
    }
    stop(hold);
}





//Task to run the drive and associated mechanisms
int Shoot(){
    while(true){
        
        if(Controller1.ButtonL2.pressing() && driverCount == 1){
            Shooter.fire(100);
            waitUntil(!Controller1.ButtonL2.pressing());
        }
        if(Controller1.ButtonR2.pressing() && driverCount == 3){
            Shooter.fire(100);
            waitUntil(!Controller1.ButtonR2.pressing());
        }
        if(Controller1.ButtonDown.pressing()){
            Shooter.pullBack(25,100);
            waitUntil(!Controller1.ButtonDown.pressing());
        }


        wait(10,msec);
    }
}