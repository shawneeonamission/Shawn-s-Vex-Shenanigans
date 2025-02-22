#include "vex.h"
#include "rgbLED.h"

using namespace vex;
using namespace S;

brain Brain;


distance goalDie(PORT8);



rotation leftTrackingWheel = rotation(PORT5);
rotation perpendicularTrackingWheel = rotation(PORT6);

motor chainBar = motor(PORT9,ratio36_1);

motor lRingBelt(PORT16,ratio18_1);
motor rRingBelt(PORT15,ratio18_1,true);

motor_group ringBelt(rRingBelt,lRingBelt);

optical ringColor(PORT2);


rotation chainRot(PORT4);



pneumatics clamp(Brain.ThreeWirePort.A);
pneumatics doink(Brain.ThreeWirePort.B);
pneumatics hang(Brain.ThreeWirePort.C);
pneumatics intakeLift(Brain.ThreeWirePort.D);
analog_in airPressure(Brain.ThreeWirePort.E);
RGB lSideRail(vex::triport(PORT22).F, 56 );
RGB rSideRail(vex::triport(PORT22).G, 56 );
line intakeSens(Brain.ThreeWirePort.H);

linkType status = chainRot.installed()?linkType::manager : linkType::worker;
serial_link linkA(PORT3,"INTRT_In_Transit_Robotics",status);

inertial Gyro = inertial(PORT7,chainRot.installed()? left : right);

controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor RD1 = motor(PORT17,ratio6_1,chainRot.installed()? false : true);
motor RD2 = motor(PORT18,ratio6_1,true);
motor RD3 = motor(PORT19,ratio6_1);
motor RD4 = motor(PORT20,ratio6_1);
motor_group RFDrive(RD1,RD3);
motor_group RRDrive(RD2,RD4);
motor_group RDrive(RD1,RD2,RD3,RD4);
motor LD1 = motor(PORT11,ratio6_1,true);
motor LD2 = motor(PORT12,ratio6_1,true);
motor LD3 = motor(PORT13,ratio6_1);
motor LD4 = motor(PORT14,ratio6_1,chainRot.installed()? true : false);
motor_group LFDrive(LD1,LD3);
motor_group LRDrive(LD2,LD4);
motor_group LDrive(LD1,LD2,LD3,LD4);

// AI Classification Competition Element IDs
enum gameElements {
  mobileGoal,
  redRing,
  blueRing,
};

// AI Vision Color Descriptions
// AI Vision Code Descriptions
vex::aivision AIVision1(PORT1, aivision::ALL_AIOBJS);