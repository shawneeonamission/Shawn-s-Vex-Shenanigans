//include vex.h and the header file you created
#include "vex.h"
#include "drive.h"
#include "odom.h"
#include "VexLink.h"
#include "AutonSelection.h"
#include "FrontVision.h"
#include <iostream>
#include "cmath"

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

double joystickCurveValue = 0;

double lForward;

double rForward;

double lTurn;

double rTurn;

int bot = 0;

bool control = true;

void drive::setJoystickCurve(double curveValue){
    joystickCurveValue = curveValue;
}

double drive::getJoystickCurve(){
  return joystickCurveValue;
}

//Function to stop the motors
void drive::stop(){
    RDrive.stop(brake);
    LDrive.stop(brake);

}


//Function to stop all the drive motors with a specified brake type
void drive::stop(brakeType type){
    RDrive.stop(type);
    LDrive.stop(type);
}

//Function to spin all the drive motors at the specified power percentage
void drive::spin(float pwr){
    RDrive.spin(directionType::fwd,pwr,pct);
    LDrive.spin(directionType::fwd,pwr,pct);
}

//Function to spin the left and right drive motors at the their specified power percentages
void drive::spin(float leftpower,float rightpower){
    RDrive.spin(directionType::fwd,rightpower,pct);
    LDrive.spin(directionType::fwd,leftpower,pct);
}
void drive::spin(float leftfront, float leftrear, float rightfront,float rightrear){
    RFDrive.spin(fwd,rightfront,pct);
    RRDrive.spin(fwd,rightrear,pct);
    LFDrive.spin(fwd,leftfront,pct);
    LRDrive.spin(fwd,leftrear,pct);
}

double drive::joystickCurve(double joystickValue){
    return exp(((abs(joystickValue) - 100) * joystickCurveValue) / 1000) * joystickValue;
}

//Function that uses a PID loop to move the robot either forward or backward at a specified maximum power
void drive::move(double dist, double maxPwr){

     //set and initalize variables
  float lastError = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  timer PIDTimer = timer();
  double currentDist = 0;
  double pwr = 0; 
  /**********adjust pI and dI to tune*********/
  float kP = 5;
  float kI = 0;
  float kD = 0;

  //set turn target
  int driveTarget = dist;

  LDrive.resetPosition();
  RDrive.resetPosition();

  while(true){

    currentDist = status == linkType::manager ?(((LDrive.position(rev) + RDrive.position(rev))/2) * (0.6)) * (3.25 * pi) : ((LDrive.position(rev) + RDrive.position(rev))/2) * (1.8 * pi);

    //calculate the P
    P = driveTarget - currentDist;
    std::cout << P << " :Move P" << std::endl;
    //calculate the I
    I += P * 10;

    //Calculate the D
    D = (P - lastError)/10;
    lastError = P;
    //calculate drive power
    float total = P*kP + I*kI + D*kD;

    //setting power value
    if(fabs(total) > maxPwr){
      pwr = maxPwr;
    }else if(fabs(total) < 4){
      pwr = 4;
    }else{
      pwr = fabs(total);
    }
    //check if turning left
    if(P < 0){
      pwr = -1*pwr;
    }
    //set motors to spin
    spin(pwr,pwr);  
    
    //check if we have reached our target
    if(fabs(P) > 0.5){
      PIDTimer.clear(); 
    }
    if(PIDTimer.time(msec) > 50)
    {
      break;
    }
    
    wait(10,msec);
  }

//stop the drive
stop(brake);

}

void drive::move(double dist){
  move(dist,100);
}

int driveTask(void* distpwr){
  double dis = *(double*)distpwr;
  //double pr = *(double*)pwr;
  base.move(dis);
  return 0;
}

void drive::move(double dist, double maxPwr, bool waitForCompletion){
  if(waitForCompletion){
    move(dist,maxPwr);
  }
  else{
    double distandpwr[] = {dist,maxPwr};
    task myTask(driveTask, &distandpwr);
  }
}

void drive::moveToRing(int rob, double maxPwr){

  
}

//Function that uses a PID loop to turn the robot to a specified angle at a specified maximum power
void drive::turn(double angle, double maxPwr){

     //set and initalize variables
  float lastError = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  timer PIDTimer = timer();
  double pwr = 0; 
  /**********adjust pI and dI to tune*********/
  float kP = 0.8;
  float kI = 0;
  float kD = 0;

  //set turn target
  int turnTarget = angle;

  while(true){

    //calculate the P
    P = turnTarget - Gyro.rotation(deg);
    std::cout << P << " :Turn P" << std::endl;
    //calculate the I
    I += P * 10;

    //Calculate the D
    D = (P - lastError)/10;
    lastError = P;
    //calculate drive power
    float total = P*kP + I*kI + D*kD;

    //setting power value
    if(fabs(total) > maxPwr){
      pwr = maxPwr;
    }else if(fabs(total) < 4){
      pwr = 4;
    }else{
      pwr = fabs(total);
    }
    //check if turning left
    if(P < 0){
      pwr = -1*pwr;
    }
    //set motors to spin
    spin(-pwr,pwr);  
    
    //check if we have reached our target
    if(fabs(P) > 1){
      PIDTimer.clear(); 
    }
    if(PIDTimer.time(msec) > 50)
    {
      break;
    }
    
    wait(10,msec);
  }

//stop the drive
stop(brake);

}

void drive::turn(double angle){
  turn(angle,100);
}

//Function that uses a PID loop to turn the robot to a specified angle at a specified maximum power
void drive::turn2(double angle, double maxPwr){
    LDrive.resetPosition();
  RDrive.resetPosition();
     //set and initalize variables
  float lastError = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  timer PIDTimer = timer();
  double pwr = 0; 
  /**********adjust pI and dI to tune*********/
  float kP = 0.5;
  float kI = 0;
  float kD = 0;

  //set turn target
  int turnTarget = angle;

  while(true){

    //calculate the P
    P = turnTarget - (RDrive.position(deg)*0.17);

    //calculate the I
    I += P * 10;

    //Calculate the D
    D = (P - lastError)/10;
    lastError = P;
    //calculate drive power
    float total = P*kP + I*kI + D*kD;

    //setting power value
    if(fabs(total) > maxPwr){
      pwr = maxPwr;
    }else if(fabs(total) < 4){
      pwr = 4;
    }else{
      pwr = fabs(total);
    }
    //check if turning left
    if(P < 0 ^ status == linkType::worker){
      pwr = -1*pwr;
    }
    //set motors to spin
    spin(-pwr,pwr);  
    
    //check if we have reached our target
    if(fabs(P) > 1){
      PIDTimer.clear(); 
    }
    if(PIDTimer.time(msec) > 50)
    {
      break;
    }
    
    wait(10,msec);
  }

//stop the drive
stop(brake);

}

//Function that uses a PID loop to turn the robot to a specified angle at a specified maximum power
void drive::turn3(double angle, double maxPwr){
    Gyro.resetRotation();
     //set and initalize variables
  float lastError = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  timer PIDTimer = timer();
  double pwr = 0; 
  /**********adjust pI and dI to tune*********/
  float kP = 0.5;
  float kI = 0;
  float kD = 0;

  //set turn target
  int turnTarget = angle;

  while(true){

    //calculate the P
    P = turnTarget - Gyro.rotation(deg);
    std::cout << P << " :Turn P" << std::endl;
    //calculate the I
    I += P * 10;

    //Calculate the D
    D = (P - lastError)/10;
    lastError = P;
    //calculate drive power
    float total = P*kP + I*kI + D*kD;

    //setting power value
    if(fabs(total) > maxPwr){
      pwr = maxPwr;
    }else if(fabs(total) < 4){
      pwr = 4;
    }else{
      pwr = fabs(total);
    }
    //check if turning left
    if(P < 0 ^ status == linkType::worker){
      pwr = -1*pwr;
    }
    //set motors to spin
    spin(-pwr,pwr);  
    
    //check if we have reached our target
    if(fabs(P) > 1){
      PIDTimer.clear(); 
    }
    if(PIDTimer.time(msec) > 50)
    {
      break;
    }
    
    wait(10,msec);
  }

//stop the drive
stop(brake);

}

void drive::turnToRing(double maxPwr){
 //set and initalize variables
  float lastError = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  timer PIDTimer = timer();
  double pwr = 0; 
  /**********adjust pI and dI to tune*********/
  float kP = 0.1;
  float kI = 0;
  float kD = 0;

  //set turn target
  //int turnTarget = angle;

  while(true){
    AIVision1.takeSnapshot(aivision::ALL_OBJECTS);
    //calculate the P
    P = 160 - AIVision1.largestObject.centerX;
    std::cout << P << " :Turn P" << std::endl;
    //calculate the I
    I += P * 10;

    //Calculate the D
    D = (P - lastError)/10;
    lastError = P;
    //calculate drive power
    float total = P*kP + I*kI + D*kD;

    //setting power value
    if(fabs(total) > maxPwr){
      pwr = maxPwr;
    }else if(fabs(total) < 4){
      pwr = 4;
    }else{
      pwr = fabs(total);
    }
    //check if turning left
    if(P < 0){
      pwr = -1*pwr;
    }
    //set motors to spin
    spin(-pwr,pwr);  
    
    //check if we have reached our target
    if(fabs(P) > 10){
      PIDTimer.clear(); 
    }
    if(PIDTimer.time(msec) > 50)
    {
      break;
    }
    
    wait(10,msec);
  }
  stop(brake);
}


//Function to turn to face the coordinates specified at full speed
void drive::turnToPoint(double x, double y){

    //turn to the inverse tangent of the point specified
    float turnTarget = (atan2(y - finalPosY,x - finalPosY)*180/pi);

    //make any turn less than 180 degrees
    if(turnTarget - finalAngle >= 180)
    {
        turnTarget -= 360;
    }
    else if(turnTarget - finalAngle <= -180)
    {
        turnTarget += 360;
    } 

    //turn to the calculated angle
    turn(turnTarget,100);

    //stop the drive
    stop();
}

//Function to turn to face the coordinates specified with a specified maximum power
void drive::turnToPoint(double x, double y, double pwr){

    //turn to the inverse tangent of the point specified
    float turnTarget = (atan2(y - finalPosY,x - finalPosY)*180/pi);

    //make any turn less than 180 degrees
    if(turnTarget - finalAngle >= 180)
    {
        turnTarget -= 360;
    }
    else if(turnTarget - finalAngle <= -180)
    {
        turnTarget += 360;
    } 

    //turn to the calculated angle
    turn(turnTarget,pwr);

    //stop the drive
    stop();
}

//Function to have the robot move to the specified coordinates and end at the specified angle
void drive::moveToPoint(double x, double y, double angle){
    //
    if(fabs(finalAngle - angle) > 30){
        turnToPoint(x,y);
    }
    //**Implement Rest of move to point code here**
    double dist = sqrt(pow(finalPosX - x,2) + pow(finalPosY - y,2));
    move(dist,100);
    turn(angle);
}

//Function to have the robot move to the specified coordinates with a specified maximum power and end at the specified angle
void drive::moveToPoint(double x, double y, double angle, double maxPwr){
    if(fabs(finalAngle - angle) > 30){
        turnToPoint(x,y,maxPwr);
    }

    double dist = sqrt(pow(finalPosX - x,2) + pow(finalPosY - y,2));
      //set and initalize variables
  float lastError = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  timer PIDTimer = timer();
  double currentDist = 0;
  double pwr = 0; 
  /**********adjust pI and dI to tune*********/
  float kP = 5.5;
  float kI = 0;
  float kD = 0;

  //set turn target
  int driveTarget = dist;

  LDrive.resetPosition();
  RDrive.resetPosition();

  while(true){

    currentDist = sqrt(pow(x,2) + pow(y,2));;

    //calculate the P
    P = driveTarget - currentDist;

    //calculate the I
    I += P * 10;

    //Calculate the D
    D = (P - lastError)/10;
    lastError = P;
    //calculate drive power
    float total = P*kP + I*kI + D*kD;

    //setting power value
    if(fabs(total) > maxPwr){
      pwr = maxPwr;
    }else if(fabs(total) < 4){
      pwr = 4;
    }else{
      pwr = fabs(total);
    }
    //check if turning left
    if(P < 0){
      pwr = -1*pwr;
    }
    //set motors to spin
    spin(pwr,pwr);  
    
    //check if we have reached our target
    if(fabs(P) > 0.5){
      PIDTimer.clear(); 
    }
    if(PIDTimer.time(msec) > 50)
    {
      break;
    }
    
    wait(10,msec);
  }

//stop the drive
stop(brake);
}

//Function that uses a PID loop to move the robot either forward or backward at a specified maximum power
void drive::strafe(double dist, double maxPwr){

     //set and initalize variables
  float lastError = 0;
  float P = 0;
  float I = 0;
  float D = 0;

  timer PIDTimer = timer();
  double currentDist = 0;
  double pwr = 0; 
  /**********adjust pI and dI to tune*********/
  float kP = 5;
  float kI = 0;
  float kD = 0;

  //set turn target
  int driveTarget = dist;

  LDrive.resetPosition();
  RDrive.resetPosition();

  while(true){

    currentDist = ((LDrive.position(rev) + RDrive.position(rev))/2) * (1.58 * pi);

    //calculate the P
    P = driveTarget - currentDist;
    std::cout << P << " :Move P" << std::endl;
    //calculate the I
    I += P * 10;

    //Calculate the D
    D = (P - lastError)/10;
    lastError = P;
    //calculate drive power
    float total = P*kP + I*kI + D*kD;

    //setting power value
    if(fabs(total) > maxPwr){
      pwr = maxPwr;
    }else if(fabs(total) < 4){
      pwr = 4;
    }else{
      pwr = fabs(total);
    }
    //check if turning left
    if(P < 0){
      pwr = -1*pwr;
    }
    //set motors to spin
    spin(pwr,-pwr,pwr,-pwr);  
    
    //check if we have reached our target
    if(fabs(P) > 0.5){
      PIDTimer.clear(); 
    }
    if(PIDTimer.time(msec) > 50)
    {
      break;
    }
    
    wait(10,msec);
  }

//stop the drive
stop(brake);

}





//Task to run the drive and associated mechanisms
int Drive(){

    base.setJoystickCurve(10);
    

    while(true){
        

        
        lForward = base.joystickCurve(Controller1.Axis3.position());
        rForward = base.joystickCurve(Controller1.Axis2.position());
        lTurn = base.joystickCurve(Controller1.Axis4.position());
        rTurn = base.joystickCurve(Controller1.Axis1.position());
        
        if(status == linkType::worker){
          if(driverCount == 0){
              base.spin((lForward + lTurn + rTurn), (lForward + lTurn - rTurn),(lForward - lTurn + rTurn) ,(lForward - lTurn - rTurn) );
          }
          else if(driverCount == 1)
          {
            base.spin((lForward + lTurn), (lForward - lTurn),(rForward + lTurn) ,(rForward - lTurn) );
          }
          else if(driverCount == 2){
            base.spin((rForward + rTurn + lTurn), (rForward + rTurn - lTurn),(rForward - rTurn + lTurn) ,(rForward - rTurn - lTurn) );
          }
          else if(driverCount == 3){
            base.spin((lForward + rTurn + lTurn), (lForward + rTurn - lTurn),(lForward - rTurn + lTurn) ,(lForward - rTurn - lTurn) );
          }
          else if(driverCount == 4){
            base.spin((rForward + lTurn + rTurn), (rForward + lTurn - rTurn),(rForward - lTurn + rTurn) ,(rForward - lTurn - rTurn) );
          }
        }
        else{
          if(driverCount == 0)
          {
            base.spin(lForward + lTurn,lForward - lTurn);
          }
          else if(driverCount == 1)
          {
            base.spin(lForward,rForward);
          }
          else if(driverCount == 2){
              base.spin(rForward + rTurn,rForward - rTurn);
          }
          else if(driverCount == 3){
              base.spin(lForward + rTurn, lForward - rTurn);
          }
          else if(driverCount == 4){
              base.spin(rForward + lTurn, rForward - lTurn);
          }
        }
        }
      
       

        wait(10,msec);
    }
