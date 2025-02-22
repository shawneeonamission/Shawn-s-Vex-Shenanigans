/* this is to prevent multiple definitions */
#ifndef __INTAKE_H__
#define __INTAKE_H__

extern int intoggle;
extern int chainBarControl();
extern int inSped;
extern int outSped;
extern int chainState;

//define a namespace
namespace S{

  //define a class
  class ringBar{
    
    //make sure that the function is public
    public:
      //declare functions to use within class
      void spin(float prct);
      void stop();
      void stop(brakeType type);
      void lift(double angle);
      void startLift(double angle);
      void lower(double angle);
  };

}



extern S::ringBar chain;

//this finished the #ifndef condition
//put all code between these 
#endif