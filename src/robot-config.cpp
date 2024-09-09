#include "vex.h"
#include "rgbLED.h"

using namespace vex;
using namespace S;

brain Brain;
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);
motor RD1 = motor(PORT7,ratio6_1);
motor RD2 = motor(PORT8,ratio6_1);
motor RD3 = motor(PORT9,ratio6_1,true);
motor_group RDrive(RD1,RD2,RD3);
motor LD1 = motor(PORT1,ratio6_1,true);
motor LD2 = motor(PORT2,ratio6_1,true);
motor LD3 = motor(PORT3,ratio6_1);
motor_group LDrive(LD1,LD2,LD3);

distance stakeDie(PORT13);
distance goalDie(PORT12);

inertial Gyro = inertial(PORT19,left);
rotation leftTrackingWheel = rotation(PORT11);
rotation rightTrackingWheel = rotation(PORT12,true);
rotation perpendicularTrackingWheel = rotation(PORT10);

motor chainBar = motor(PORT5,ratio36_1,true);

motor lLift = motor(PORT11,ratio36_1);
motor rLift = motor(PORT20,ratio36_1,true);

motor_group goalLift = motor_group(lLift,rLift);

rotation chainRot(PORT7);

pneumatics stake(Brain.ThreeWirePort.A);


analog_in airPressure(Brain.ThreeWirePort.E);

RGB lSideRail(vex::triport(PORT22).F, 56 );
RGB rSideRail(vex::triport(PORT22).G, 56 );


