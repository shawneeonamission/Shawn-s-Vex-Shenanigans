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
double finalAngleRadians;

double localPosX;
double localPosY;
double localPosChangeX;
double localPosChangeY;
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

double leftTrackingWheelDiameter = 3.25;
double leftTrackingWheelCurrent;
double leftTrackingWheelPrevious;
double leftTrackingWheelChange;
double leftTrackingWheelChangeInches;
double leftTrackingWheelTotalInches;
double leftDistanceToCenter = 5.5;

double rightTrackingWheelDiameter = 2.775;
double rightTrackingWheelCurrent;
double rightTrackingWheelPrevious;
double rightTrackingWheelChange;
double rightTrackingWheelChangeInches;
double rightTrackingWheelTotalInches;
double rightDistanceToCenter = 5.5;

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

int phase = 2;

//Function to easily set the odometry starting position amd angle
void odom::setStartPos(double x, double y, double angle){
    startX = x;
    startY = y;
    startAngle = angle;

}
double odom::angleToPoint(double x, double y){
    return atan2(y - finalPosY,x - finalPosY)*180/pi;
}


//Task to perform odometry calculations
int odomCalculations(){
    //Infinte loop
    leftTrackingWheel.resetPosition();
    rightTrackingWheel.resetPosition();
    perpendicularTrackingWheel.resetPosition();
    while(true){
        //line to be able to start and stop the odometry at will
        waitUntil(odomEnable);
        if(phase == 0){
            //Set Previous

            inertialPrevious = inertialCurrent;
            leftTrackingWheelPrevious = leftTrackingWheelCurrent;
            rightTrackingWheelPrevious = rightTrackingWheelCurrent;

            //Set Current 
            inertialCurrent = Gyro.rotation(deg);
            leftTrackingWheelCurrent = (LDrive.position(rev)*3/5.0)* leftDistanceToCenter * pi;
            rightTrackingWheelCurrent = (RDrive.position(rev)*3/5.0)* rightDistanceToCenter * pi;



            //Difference

            inertialChange = inertialCurrent - inertialPrevious;
            leftTrackingWheelChange = leftTrackingWheelCurrent - leftTrackingWheelPrevious;
            rightTrackingWheelChange = rightTrackingWheelCurrent - rightTrackingWheelPrevious;




            //Final Angle
            finalAngle += inertialChange;

            

            if(finalAngle > 180)
            {
                finalAngle -= 360;
            }
            else if(finalAngle < -180)
            {
                finalAngle += 360;
            }
            if(inertialChange == 0){
                inertialChange += 0.0000000000001;

            }

            //Cycle Global Change
            globalPosChangeX = ((((leftTrackingWheelChange + rightTrackingWheelChange)/2) * sin(finalAngle * (pi/180))));

            globalPosChangeY = ((((leftTrackingWheelChange + rightTrackingWheelChange)/2) * cos(finalAngle * (pi/180))));
            //Final Position Change
            finalPosX += globalPosChangeX;

            finalPosY += globalPosChangeY;
            //Final Position
            finalPosX += startX;

            finalPosY += startY;
        }
        
        if(phase == 2){
            // update the parallel tracking wheel current degrees to the current value
            // of the parallel tracking wheel rotation sensor in degrees
            leftTrackingWheelCurrent = leftTrackingWheel.position(rotationUnits::deg);

            // update the perpendicular tracking wheel current degrees to the current
            // value of the perpendicular tracking wheel rotation sensor in degrees
           perpendicularTrackingWheelCurrent = perpendicularTrackingWheel.position(rotationUnits::deg);

            // update the inertial sensor value to the current value of the rotation sensor
            inertialCurrent = Gyro.heading(degrees);

            // calculate the diffrence in current and previous for the parallel tracking wheel
            leftTrackingWheelChange = leftTrackingWheelCurrent - leftTrackingWheelPrevious;

            // calculate the diffrence in current and previous for the perpendicular tracking wheel

            perpendicularTrackingWheelChange = perpendicularTrackingWheelCurrent - perpendicularTrackingWheelPrevious;

            // calculate the delta of the chassis inertial sensor heading
            inertialChange = inertialCurrent - inertialPrevious;

            // calculate the parallel inches traveled for the cycle
            leftTrackingWheelChangeInches = (leftTrackingWheelChange / 360) * leftTrackingWheelDiameter * M_PI;

            // calculate the perpendicular inches traveled for the cycle

            perpendicularTrackingWheelChangeInches = (perpendicularTrackingWheelChange / 360) * perpendicularTrackingWheelDiameter * M_PI;

            // calculate the total inches traveled by the parallel wheel
            leftTrackingWheelTotalInches += leftTrackingWheelChangeInches;

            // calculate the total inches traveled by the perpendicular wheel
            perpendicularTrackingWheelTotalInches += perpendicularTrackingWheelChangeInches;

            // calculate the final angle of the robot
            finalAngle = Gyro.heading(degrees) + startAngle;

            // If the chassis inertial sensor value is greater than 180, subtract 360 from it
            if (finalAngle >= 180) {
                finalAngle -= 360;
            }

            // if the chassis inertial sensor value is less than -180, add 360 to it
            else if (finalAngle <= -180) {
                finalAngle += 360;

            }

            // calculate the current radian diffrence of the chassis inertial sensor
            inertialChangeRadians = inertialChange * M_PI / 180;

            // calculate the currend radian final degree of the chassis inertial sensor

            finalAngleRadians = finalAngle * M_PI / 180;

            // if the delta of chassis inertial sensor is 0, then the local x axis displacemnt is equal to the perpendicular wheel's delta and the local y
            //axis displacement is equal to the parallel wheel's delta

            if (inertialChange == 0) {
            // x axis is equal to perpendicular tracking wheel's delta in inches
            localPosChangeX = perpendicularTrackingWheelChangeInches;

            // y axis is equal to the parallel tracking wheel's delta in inches
            localPosChangeY = leftTrackingWheelChange;
            }

            // if the delta of the chassis inertial sensor is not 0, then the local x
            // axis and y axis will be calculatd using both the parallel and
            // perpendicualr tracking wheel as well as the chassis inertial sensor.
            else {
            // if the angle change is not equal to 0 for the cycle, calculate the
            // poition change in the local x direction
            localPosChangeX = (2 * (perpendicularTrackingWheelChangeInches / inertialChangeRadians + perpendicularDistanceToCenter) * sin(inertialChangeRadians / 2));

            // if the angle change is not equal to 0 for the cycle, calculate the
            // posiiton change in the local y direction
            localPosChangeY = ((2 * (leftTrackingWheelChangeInches / inertialChangeRadians + leftDistanceToCenter)) * sin(inertialChangeRadians / 2));
            }

            // calculate the hypotinuse of the local displacement
            localHypotnuseLength = sqrt(pow(localPosChangeX,2) + pow(localPosChangeY,2));

            // calculate the angle of the hypotinuse of the local displacement
            localHypotnuseAngle = atan2(localPosChangeX,localPosChangeY);

            // calculate the x axis global displacement

            globalPosChangeX = localHypotnuseLength * sin(localHypotnuseAngle + finalAngleRadians);

            // calculate the y axis global displacement
            globalPosChangeY = localHypotnuseLength * cos(localHypotnuseAngle + finalAngleRadians);

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

            // set pervious odom tracking wheel values to the current (last cycles
            // current) values
            leftTrackingWheelPrevious = leftTrackingWheelCurrent;
            perpendicularTrackingWheelPrevious = perpendicularTrackingWheelCurrent;

            // set the previous inertial sensor value to the current (last cycles
            // current) value
            inertialPrevious = inertialCurrent;
        }
        if(phase == 3){

                    //Update Sensor Variables
        inertialCurrent = Gyro.rotation(deg);
        inertialCurrentRadians = inertialCurrent * (pi / 180);
        rightTrackingWheelCurrent = rightTrackingWheel.position(deg);
        perpendicularTrackingWheelCurrent = perpendicularTrackingWheel.position(deg);

        //Calculate Change in sensor values
        inertialChange = inertialCurrent - inertialPrevious;
        rightTrackingWheelChange = rightTrackingWheelCurrent - rightTrackingWheelPrevious;
        perpendicularTrackingWheelChange = perpendicularTrackingWheelCurrent - perpendicularTrackingWheelPrevious;

        //Convert Sensor values to units easier for calcualtions
        inertialChangeRadians = inertialChange * (pi / 180);
        rightTrackingWheelChangeInches = (rightTrackingWheelCurrent / 360) * (pi * rightTrackingWheelDiameter);
        perpendicularTrackingWheelChangeInches = (perpendicularTrackingWheelCurrent / 360) * (pi * perpendicularTrackingWheelDiameter);

        //Calculate total displacement of the tracking wheels in inches
        rightTrackingWheelTotalInches += rightTrackingWheelChangeInches;
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
            localPosY = rightTrackingWheelChangeInches;
        }
        else {

            // if the angle change is not equal to 0 for the cycle, calculate the
            // poition change in the local x direction
            localPosX = (2 * (perpendicularTrackingWheelChangeInches / inertialChangeRadians + perpendicularDistanceToCenter) * sin(inertialChangeRadians / 2));

            // if the angle change is not equal to 0 for the cycle, calculate the
            // posiiton change in the local y direction
            localPosY = ((2 * (rightTrackingWheelChangeInches / inertialChangeRadians + rightDistanceToCenter)) * sin(inertialChangeRadians / 2));
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
        rightTrackingWheelPrevious = rightTrackingWheelCurrent;
        perpendicularTrackingWheelPrevious = perpendicularTrackingWheelCurrent;
        inertialPrevious = inertialCurrent;
        }
        Brain.Screen.clearScreen();
        Brain.Screen.printAt(20,20,"Pos (%.2lf,%.2lf)", finalPosX,finalPosY);
        Brain.Screen.printAt(20,40,"Left: %.2lf", leftTrackingWheelCurrent);
        Brain.Screen.printAt(20,60,"Right: %.2lf", rightTrackingWheelCurrent);
        Brain.Screen.printAt(20,80,"Perp: %.2lf", perpendicularTrackingWheelCurrent);
        Brain.Screen.printAt(20,100,"Gyro: %.2lf", inertialCurrent);

        wait(10,msec);
    }
}


