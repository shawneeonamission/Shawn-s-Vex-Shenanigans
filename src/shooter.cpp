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
int upAngle = 139;
int downAngle = 220;
int midAngle = 180;

//int upAngle = 95;
//int downAngle = 12;
//int midAngle = 180;

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

double shooter::angle(){
    return cataRot.angle(deg);
}


void shooter::fire(float speed){
    spin(speed);
    if(angle() < downAngle + 20){
    wShooter.spinFor(30,deg);
  
    wait(200,msec);
    }

    double p = downAngle - cataRot.angle(deg);
    double lastP = p;
    double d = p - lastP;
    double kp = 1.7;
    double kd = 4;
    while(1){
        p = downAngle - cataRot.angle(deg);
        std::cout << p << std::endl;
        d = p - lastP;
        lastP = p;
    if(p > speed){p = speed;}
    spin(p*kp + d*kd);
    if(p < 3){
        std::cout << "break" << std::endl;
        break;
        }
    wait(10,msec);
    }
    stop(hold);
    
}

void shooter::pullBack(double angle,float speed){
    double p = angle - cataRot.angle(deg);
    double lastP = p;
    double d = p - lastP;
    while(1){
        p = angle - cataRot.angle(deg);

        p *= .7;
        d = p - lastP;
        lastP = p;
        d *= 2;
    if(fabs(p) > speed){p = speed;}
    if(p < 0){speed *= -1;}
    spin(p + d);
    if(fabs(p < 2)){break;}
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
        if(Controller1.ButtonR1.pressing() && driverCount == 2){
            Shooter.fire(100);
            waitUntil(!Controller1.ButtonR2.pressing());
        }
      


        wait(10,msec);
    }
}