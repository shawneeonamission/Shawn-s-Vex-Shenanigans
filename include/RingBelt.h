/* this is to prevent multiple definitions */
#ifndef __RINGBELT_H__
#define __RINGBELT_H__

extern int intoggle;
extern int ringBeltControl();
extern int inSped;
extern int outSped;

//define a namespace
namespace S{

  //define a class
  class hooks{
    
    //make sure that the function is public
    public:
      //declare functions to use within class
      void spin(float prct);
      void stop();
      void stop(brakeType type);
      void lift(double angle);
  };

}



extern S::hooks belt;

//this finished the #ifndef condition
//put all code between these 
#endif