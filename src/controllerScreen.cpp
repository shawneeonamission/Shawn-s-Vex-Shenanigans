#include "vex.h"
#include "controllerScreen.h"
#include <iostream>

//display important values on the controller screen
int ControllerScreen()
{
  while(true)
  {
   double tankPressure = (airPressure.value(range12bit)/22) - (210/11);
    
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,0);
    Controller1.Screen.print("Cata %3.0f Air %.0f", wShooter.temperature(fahrenheit),tankPressure);
    Controller1.Screen.setCursor(2,0);
    Controller1.Screen.print("in %3.0f ", wIntake.temperature(fahrenheit));
    Controller1.Screen.setCursor(3,0);
    Controller1.Screen.print("L %3.0f R %3.0f", LDrive.temperature(fahrenheit), RDrive.temperature(fahrenheit));
    wait(200,msec);
  }
}
