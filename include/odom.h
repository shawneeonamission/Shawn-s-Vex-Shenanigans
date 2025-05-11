/* this is to prevent multiple definitions */
#ifndef __ODOM_H__
#define __ODOM_H__

extern double pi;
extern double finalPosX;
extern double finalPosY;
extern double finalAngle;
extern double leftTrackingWheelCurrent;
extern int odomCalculations();

namespace S{

    class odom{

        public:
        void setStartPos(double x, double y, double angle);
        double angleToPoint(double x, double y);

    };
}

//this finished the #ifndef condition
//put all code between these 
#endif