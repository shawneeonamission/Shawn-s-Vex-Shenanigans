/* this is to prevent multiple definitions */
#ifndef __DRIVE_H__
#define __DRIVE_H__

extern int Drive();

//define a namespace
namespace S{

  //define a class
  class drive{

    //make sure that the function is public
    public:
      //declare functions to use within class
      void setJoystickCurve(double curveValue);
      double getJoystickCurve();
      void stop();
      void stop(brakeType type);
      void spin(float pwr);
      void spin(float leftpower, float rightpower);
      double joystickCurve(double joystickValue);
      void move(double dist, double maxPwr);
      void turn(double angle, double maxPwr);
      void turnToPoint(double x, double y);
      void turnToPoint(double x, double y, double pwr);
      void moveToPoint(double x, double y, double angle);
      void moveToPoint(double x, double y, double angle, double pwr);
      
       };

}

extern S::drive base;
//this finished the #ifndef condition
//put all code between these 
#endif