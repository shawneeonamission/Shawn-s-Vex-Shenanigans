//include vex.h and the header file you created
#include "vex.h"
#include "odom.h"
#include <iostream>

//declare the namespace you created
using namespace O;
//also include namespace vex
using namespace vex;

double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;
double finalPosX = 0;
double finalPosY = 0;
double finalAngle = 0;

int odomCalculations(){
    while(true){

        finalAngle = Gyro.rotation(deg);

        wait(10,msec);
    }
}

