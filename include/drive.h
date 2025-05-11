/* this is to prevent multiple definitions */
#ifndef __DRIVE_H__
#define __DRIVE_H__

extern int Drive();

extern double lForward;

extern double rForward;

extern double lTurn;

extern double rTurn;

extern int bot;

extern bool control;
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
      void spin(float leftfront, float leftrear, float rightfront,float rightrear);
      double joystickCurve(double joystickValue);
      void move(double dist);
      void move(double dist, double maxPwr);
      void move(double dist, double maxPwr, bool waitForCompletion);
      void moveToRing(int rob, double maxPwr);
      void turn(double angle);
      void turn(double angle, double maxPwr);
      void turn2(double angle, double maxPwr);
      void turn3(double angle, double maxPwr);
      void turnToRing(double maxPwr);
      void turnToPoint(double x, double y);
      void turnToPoint(double x, double y, double pwr);
      void moveToPoint(double x, double y, double angle);
      void moveToPoint(double x, double y, double angle, double pwr);
      void strafe(double dist, double maxPwr);
      void strafeSkills(double dist, double maxPwr);
      
       };

}

extern S::drive base;
//this finished the #ifndef condition
//put all code between these 
#endif