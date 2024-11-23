#include "vex.h"
#include "rgbLED.h"

using namespace vex;
using namespace S;

brain Brain;
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor RD1 = motor(PORT18,ratio6_1);
motor RD2 = motor(PORT19,ratio6_1);
motor RD3 = motor(PORT20,ratio6_1,true);
motor RD4 = motor(PORT17,ratio6_1,true);
motor_group RDrive(RD1,RD2,RD3,RD4);
motor LD1 = motor(PORT11,ratio6_1,true);
motor LD2 = motor(PORT12,ratio6_1,true);
motor LD3 = motor(PORT13,ratio6_1);
motor LD4 = motor(PORT14,ratio6_1);
motor_group LDrive(LD1,LD2,LD3,LD4);

distance goalDie(PORT8);

inertial Gyro = inertial(PORT7,left);

rotation leftTrackingWheel = rotation(PORT5);
rotation rightTrackingWheel = rotation(PORT3,true);
rotation perpendicularTrackingWheel = rotation(PORT6);

motor chainBar = motor(PORT9,ratio36_1);

motor lRingBelt(PORT10,ratio18_1,true);
motor rRingBelt(PORT1,ratio18_1);

motor_group ringBelt(rRingBelt,lRingBelt);

motor lLift = motor(PORT15,ratio36_1);
motor rLift = motor(PORT16,ratio36_1,true);

motor_group goalLift = motor_group(lLift,rLift);

rotation chainRot(PORT4);

pneumatics shift(Brain.ThreeWirePort.A);
pneumatics paddle(Brain.ThreeWirePort.B);
pneumatics clamp(Brain.ThreeWirePort.C);

analog_in airPressure(Brain.ThreeWirePort.E);

RGB lSideRail(vex::triport(PORT22).F, 56 );
RGB rSideRail(vex::triport(PORT22).G, 56 );

aivision aiVision(PORT10);
linkType status = chainRot.installed()?linkType::manager : linkType::worker;
serial_link linkA(PORT3,"INTRT_In_Transit_Robotics",status);