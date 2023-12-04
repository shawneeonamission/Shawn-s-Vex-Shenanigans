#include "vex.h"

using namespace vex;

brain Brain;
controller Controller1 = controller(primary);
controller Controller2 = controller(partner);

motor RD1 = motor(PORT1,ratio6_1);
motor RD2 = motor(PORT2,ratio6_1);
motor RD3 = motor(PORT3,ratio6_1);
motor RD4 = motor(PORT4,ratio6_1);
motor_group RDrive(RD1,RD2,RD3,RD4);
motor LD1 = motor(PORT5,ratio6_1);
motor LD2 = motor(PORT6,ratio6_1);
motor LD3 = motor(PORT7,ratio6_1);
motor LD4 = motor(PORT8,ratio6_1);
motor_group LDrive(LD1,LD2,LD3,LD4);

inertial Gyro = inertial(PORT9,left);
rotation parallelTrackingWheel = rotation(PORT10);
rotation perpendicularTrackingWheel = rotation(PORT11);

motor wIntake = motor(PORT12,ratio6_1);

motor lShooter = motor(PORT13,ratio18_1);
motor rShooter = motor(PORT14,ratio18_1,true);
motor_group wShooter = motor_group(lShooter,rShooter);

pneumatics intakeOut(Brain.ThreeWirePort.A);
pneumatics intakeTilt(Brain.ThreeWirePort.B);
pneumatics lWing(Brain.ThreeWirePort.C);
pneumatics rWing(Brain.ThreeWirePort.D);
