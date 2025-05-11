#include "rgbLED.h"
using namespace vex;
using namespace S;

extern brain Brain;
extern controller Controller1;
extern controller Controller2;

extern motor_group RFDrive;
extern motor_group RRDrive;
extern motor_group RDrive;
extern motor_group LFDrive;
extern motor_group LRDrive;
extern motor_group LDrive;

extern inertial Gyro;
extern rotation leftTrackingWheel;
extern rotation rightTrackingWheel;
extern rotation perpendicularTrackingWheel;

extern pneumatics intakeLift;
extern analog_in airPressure;

extern RGB lSideRail;
extern RGB rSideRail;

extern linkType status;
extern serial_link linkA;

extern aivision AIVision1;



void vexcodeInit(void);
