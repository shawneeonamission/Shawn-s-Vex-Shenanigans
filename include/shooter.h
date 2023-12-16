/* this is to prevent multiple definitions */
#ifndef __SHOOTER_H__
#define __SHOOTER_H__

extern int Shoot();


//define a namespace
namespace S{

  //define a class
  class shooter{

    //make sure that the function is public
    public:
      //declare functions to use within class
        void stop();
      void stop(brakeType type);
      void spin(float pwr);
      void fire(float speed);
      void pullBack(double angle, float speed);
       };

}

extern S::shooter Shooter;
//this finished the #ifndef condition
//put all code between these 
#endif