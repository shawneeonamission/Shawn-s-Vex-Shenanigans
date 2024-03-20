#include "vex.h"
#include "rgbLED.h"

using namespace vex;
using namespace S;

brain Brain;
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

motor RD1 = motor(PORT8,ratio6_1,true);
motor RD2 = motor(PORT7,ratio6_1);
motor RD3 = motor(PORT6,ratio6_1);
motor RD4 = motor(PORT5,ratio6_1);
motor_group RDrive(RD1,RD2,RD3,RD4);
motor LD1 = motor(PORT1,ratio6_1,true);
motor LD2 = motor(PORT2,ratio6_1);
motor LD3 = motor(PORT3,ratio6_1,true);
motor LD4 = motor(PORT4,ratio6_1,true);
motor_group LDrive(LD1,LD2,LD3,LD4);

distance intakeDie(PORT13);

inertial Gyro = inertial(PORT17,left);
rotation parallelTrackingWheel = rotation(PORT9);
rotation perpendicularTrackingWheel = rotation(PORT10);

motor wIntake = motor(PORT12,ratio6_1);

motor lShooter = motor(PORT11,ratio36_1);
motor rShooter = motor(PORT19,ratio36_1,true);
rotation cataRot(PORT15);
motor_group wShooter = motor_group(lShooter,rShooter);

pneumatics intakeOut(Brain.ThreeWirePort.A);
pneumatics intakeTilt(Brain.ThreeWirePort.B);
pneumatics lWing(Brain.ThreeWirePort.D);
pneumatics rWing(Brain.ThreeWirePort.C);

analog_in airPressure(Brain.ThreeWirePort.E);

RGB sideRails(vex::triport(PORT22).F, 56 );
RGB underGlow(vex::triport(PORT22).G, 64 );
RGB underGlow2(vex::triport(PORT22).H, 64 );

//yay my keyboard still works yayyyyyyyyy!!!!!!!!!!!!!! woooooo hooooooooo yayyyyy!!!!! I'm quite surprised that im typing this well without keycapssds

