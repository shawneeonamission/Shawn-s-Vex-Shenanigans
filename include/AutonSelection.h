/* this is to prevent multiple definitions */
#ifndef __AUTONSELECTION_H__
#define __AUTONSELECTION_H__

//dummy code for example
#include <iostream>

extern int auton;

extern int autonSelect();

extern int odom_refresh();

extern int rob;

extern void GyroCalibrate();

extern int TestingMenu();

extern short augmentCount;

extern int offset;

extern double Start_X;

extern double Start_Y;

extern int testing;


//define a namespace
namespace N{

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