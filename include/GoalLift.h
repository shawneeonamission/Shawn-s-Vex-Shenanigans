/* this is to prevent multiple definitions */
#ifndef __GOALLIFT_H__
#define __GOALLIFT_H__

extern int FerrisWheel();

extern int downAngle;

extern bool cata;


//define a namespace
namespace S{

  //define a class
  class liftgoal{

    //make sure that the function is public
    public:
      //declare functions to use within class
        void stop();
      void stop(brakeType type);
      void spin(float pwr);
      void spin(float lPwr, float rPwr);
      double angle();
      void lift(float speed);
      void lower( float speed);
       };

}

extern S::liftgoal ferriswheel;
//this finished the #ifndef condition
//put all code between these 
#endif