/* this is to prevent multiple definitions */
#ifndef __INTAKE_H__
#define __INTAKE_H__

extern int intoggle;

//define a namespace
namespace S{

  //define a class
  class feeder{
    
    //make sure that the function is public
    public:
      //declare functions to use within class
      void in(float revs);
      void out(float revs);
      void stop();
  };

}



extern S::feeder intake;

//this finished the #ifndef condition
//put all code between these 
#endif