#include "vex.h"
#include "controllerScreen.h"
#include "RingBelt.h"
#include <iostream>
int warning = 0;
//display important values on the controller screen
int ControllerScreen()
{
  while(true)
  {
   double tankPressure = (airPressure.value(range12bit)/22) - (210/11);
    
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,0);
    if(load == 0){
    Controller1.Screen.print("Bat %d Air %.0f", Brain.Battery.capacity(pct),tankPressure);
    }
    else{
      Controller1.Screen.print("LOADING %d",load);
    }
    Controller1.Screen.setCursor(2,0);
    Controller1.Screen.print("Chain %3.0f Belt %3.0f", chainBar.temperature(fahrenheit), ringBelt.temperature(fahrenheit));
    Controller1.Screen.setCursor(3,0);
    Controller1.Screen.print("L %3.0f R %3.0f", LDrive.temperature(fahrenheit), RDrive.temperature(fahrenheit));
    wait(20,msec);
    if(tankPressure <= 70 && warning == 0){
      Controller1.rumble("-");
      warning = 1;
    }
    else if(tankPressure <= 50 && warning == 0){
      Controller1.rumble("-");
      warning = 1;
    }
  }
}
