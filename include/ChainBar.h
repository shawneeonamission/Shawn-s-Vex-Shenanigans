/* this is to prevent multiple definitions */
#ifndef __INTAKE_H__
#define __INTAKE_H__

extern int intoggle;
extern int ringBarControl();
extern int inSped;
extern int outSped;

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
      void autoStakeLift();
      void autoLower();
      void autoPickup();
      void autoDeposit();
  };

}



extern S::ringBar chain;

//this finished the #ifndef condition
//put all code between these 
#endif