//include vex.h and the header file you created
#include "vex.h"
#include "shooter.h"
#include "FrontVision.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;


//Function to stop the motors
void shooter::stop(){
    RD1.stop(brake);
    RD2.stop(brake);
    RD3.stop(brake);
    RD4.stop(brake);
    LD1.stop(brake);
    LD2.stop(brake);
    LD3.stop(brake);
    LD4.stop(brake);

}


//Function to stop all the drive motors with a specified brake type
void shooter::stop(brakeType type){
    RD1.stop(brake);
    RD2.stop(brake);
    RD3.stop(brake);
    RD4.stop(brake);
    LD1.stop(brake);
    LD2.stop(brake);
    LD3.stop(brake);
    LD4.stop(brake);
}

//Function to spin all the drive motors at the specified power percentage
void shooter::spin(float pwr){
    RD1.spin(directionType::fwd,pwr,pct);
    RD2.spin(directionType::fwd,pwr,pct);
    RD3.spin(directionType::fwd,pwr,pct);
    RD4.spin(directionType::fwd,pwr,pct); 
    LD1.spin(directionType::fwd,pwr,pct);
    LD2.spin(directionType::fwd,pwr,pct);
    LD3.spin(directionType::fwd,pwr,pct);
    LD4.spin(directionType::fwd,pwr,pct); 
}






//Task to run the drive and associated mechanisms
int Shoot(){
    while(true){
        
        

        wait(10,msec);
    }
}