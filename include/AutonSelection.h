/* this is to prevent multiple definitions */
#ifndef __AUTONSELECTION_H__
#define __AUTONSELECTION_H__

//dummy code for example
#include <iostream>

extern int auton;

extern int autonSelect();

extern int odomCalculations();

extern int rob;

extern void GyroCalibrate();

extern int TestingMenu();

extern short BotCount;

extern int offset;

extern double startX;

extern double startY;

extern bool testing;

extern short driverCount;


//define a namespace
namespace S{

  //define a class
  class AutonSelector{
    
    //make sure that the function is public
    public:
      //declare functions to use within class

  };

}


//this finished the #ifndef condition
//put all code between these 
#endif