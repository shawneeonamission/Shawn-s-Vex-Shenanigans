#include "rgbLED.h"
using namespace vex;
using namespace S;

extern brain Brain;
extern controller Controller1;
extern controller Controller2;

extern motor_group RDrive;
extern motor_group LDrive;

extern inertial Gyro;
extern rotation leftTrackingWheel;
extern rotation rightTrackingWheel;
extern rotation perpendicularTrackingWheel;

extern motor chainBar;

extern distance stakeDie;
extern distance goalDie;

extern motor lLift;
extern motor rLift;
extern motor_group goalLift;

extern rotation chainRot;

extern pneumatics stake;

extern analog_in airPressure;

extern RGB lSideRail;
extern RGB rSideRail;



void vexcodeInit(void);
