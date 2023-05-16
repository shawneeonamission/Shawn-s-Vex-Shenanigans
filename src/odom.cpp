//include vex.h and the header file you created
#include "vex.h"
#include "odom.h"
#include <iostream>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

double finalPosX;
double finalPosY;
double finalAngle;

double localPosX;
double localPosY;
double globalPosChangeX;
double globalPosChangeY;
double globalPosDisplacmentX;
double globalPosDisplacmentY;

double startX = 0;
double startY = 0;
double startAngle = 0;

double inertialCurrent;
double inertialPrevious;
double inertialChange;
double inertialCurrentRadians;
double inertialChangeRadians;

double parallelTrackingWheelDiameter = 2.775;
double parallelTrackingWheelCurrent;
double parallelTrackingWheelPrevious;
double parallelTrackingWheelChange;
double parallelTrackingWheelChangeInches;
double parallelTrackingWheelTotalInches;
double parallelDistanceToCenter = 3.625;

double perpendicularTrackingWheelDiameter = 2.775;
double perpendicularTrackingWheelCurrent;
double perpendicularTrackingWheelPrevious;
double perpendicularTrackingWheelChange;
double perpendicularTrackingWheelChangeInches;
double perpendicularTrackingWheelTotalInches;
double perpendicularDistanceToCenter = 5;

double localHypotnuseLength;
double localHypotnuseAngle;


bool odomEnable = true;

//Function to easily set the odometry starting position amd angle
void odom::setStartPos(double x, double y, double angle){
    startX = x;
    startY = y;
    startAngle = angle;

}


//Task to perform odometry calculations
int odomCalculations(){
    //Infinte loop
    while(true){
        //line to be able to start and stop the odometry at will
        waitUntil(odomEnable);

        //Update Sensor Variables
        inertialCurrent = Gyro.rotation(deg);
        inertialCurrentRadians = inertialCurrent * (pi / 180);
        parallelTrackingWheelCurrent = parallelTrackingWheel.position(deg);
        perpendicularTrackingWheelCurrent = perpendicularTrackingWheel.position(deg);

        //Calculate Change in sensor values
        inertialChange = inertialCurrent - inertialPrevious;
        parallelTrackingWheelChange = parallelTrackingWheelCurrent - parallelTrackingWheelPrevious;
        perpendicularTrackingWheelChange = perpendicularTrackingWheelCurrent - perpendicularTrackingWheelPrevious;

        //Convert Sensor values to units easier for calcualtions
        inertialChangeRadians = inertialChange * (pi / 180);
        parallelTrackingWheelChangeInches = (parallelTrackingWheelCurrent / 360) * (pi * parallelTrackingWheelDiameter);
        perpendicularTrackingWheelChangeInches = (perpendicularTrackingWheelCurrent / 360) * (pi * perpendicularTrackingWheelDiameter);

        //Calculate total displacement of the tracking wheels in inches
        parallelTrackingWheelTotalInches += parallelTrackingWheelChangeInches;
        perpendicularTrackingWheelTotalInches += perpendicularTrackingWheelChangeInches;

        // calculate the final angle of the robot
        finalAngle = inertialCurrent + startAngle;

        if(finalAngle > 180)
        {
            finalAngle -= 360;
        }
        else if(finalAngle < -180){
            finalAngle += 360;
        }




       
        //if the angle of the robot hasn't changed then the local x and y displacement is equal to the perpendicular and parallel tracking wheels respectivly
        if (inertialChange == 0) {

            // x axis is equal to perpendicular tracking wheel's delta in inches
            localPosX = perpendicularTrackingWheelChangeInches;
            // y axis is equal to the parallel tracking wheel's delta in inches
            localPosY = parallelTrackingWheelChangeInches;
        }
        else {

            // if the angle change is not equal to 0 for the cycle, calculate the
            // poition change in the local x direction
            localPosX = (2 * (perpendicularTrackingWheelChangeInches / inertialChangeRadians + perpendicularDistanceToCenter) * sin(inertialChangeRadians / 2));

            // if the angle change is not equal to 0 for the cycle, calculate the
            // posiiton change in the local y direction
            localPosY = ((2 * (parallelTrackingWheelChangeInches / inertialChangeRadians + parallelDistanceToCenter)) * sin(inertialChangeRadians / 2));
        }


        // calculate the hypotinuse of the local displacement
        localHypotnuseLength = sqrt((pow(localPosX,2)) + (pow(localPosY,2)));

        // calculate the angle of the hypotinuse of the local displacement
        localHypotnuseAngle = atan2(localPosX,localPosY);



        // calculate the x axis global displacement
        globalPosChangeX = localHypotnuseLength * sin(localHypotnuseAngle + inertialCurrentRadians);

        // calculate the y axis global displacement
        globalPosChangeY = localHypotnuseLength * cos(localHypotnuseAngle + inertialCurrentRadians);



        // find the total x axis global displacement
        globalPosDisplacmentX += globalPosChangeX;

        // find the total y axis global displacement
        globalPosDisplacmentY += globalPosChangeY;




        // add global x axis starting postion to the displacement to find final
        // position of the global x axis
        finalPosX = startX + globalPosDisplacmentX;

        // add global y axis starting postion to the displacement to find the final
        // position of the global y axis
        finalPosY = startY + globalPosDisplacmentY;

        // set pervious sensor values to the current (last cycles
        // current) values
        parallelTrackingWheelPrevious = parallelTrackingWheelCurrent;
        perpendicularTrackingWheelPrevious = perpendicularTrackingWheelCurrent;
        inertialPrevious = inertialCurrent;


        wait(10,msec);
    }
}

