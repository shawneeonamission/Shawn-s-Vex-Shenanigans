//include vex.h and the header file you created
#include "vex.h"
#include "VexLink.h"
#include "odom.h"
#include "drive.h"
#include <iostream>
#include <string>

//declare the namespace you created
using namespace S;
//also include namespace vex
using namespace vex;

double targetX;
double targetY;
bool messageRecieved;
bool sendMessage;
std::string messageToSend = "";
std::string recievedMessage = "";


 





//Function that sends coordinates to the other robot
void link::send(double x, double y){
    int wholeX = int(x);
      int deciX = int((x - wholeX)*100);
      int wholeY = int(y);
      int deciY = int((y - wholeY)*100);

      uint8_t data[] = {uint8_t('C'), uint8_t(wholeX), uint8_t(deciX),uint8_t(wholeY),uint8_t(deciY)};
     
    linkA.send(data,sizeof(data));
}

//Function that sends a string to the other robot
void link::send(std::string message){
    uint8_t data[message.length() + 1];
    data[0] = uint8_t('S');
    for(int i = 1; i < message.length() + 1; i++){
        data[i] = uint8_t(message[i-1]);
    }
    linkA.send(data,sizeof(data));
}

void link::send(double lForward, double rForward, double lTurn, double rTurn){
    uint8_t data[] = {uint8_t('D'), uint8_t(lForward+100), uint8_t(rForward+100),uint8_t(lTurn+100),uint8_t(rTurn+100)};
    linkA.send(data,sizeof(data));
}


void rx_handler( uint8_t *buffer, int32_t length ) {
    if(buffer[0] == uint8_t('C')){
        control = true;
        targetX = double(buffer[1]) + (double(buffer[2])/100);
        targetY = double(buffer[3]) + (double(buffer[4])/100);
        Brain.Screen.printAt(20,210,true,"target value (%.2f.,%.2f)", targetX, targetY );
    }
    if(buffer[0] == uint8_t('S')){
        control = true;
        messageRecieved = true;
        for(int i = 0; i < length; i++){
            recievedMessage += buffer[i + 1];
        }
        
    }
    if(buffer[0] == uint8_t('D')){
        bot = 1;
        control = false;
        lForward = int(buffer[1])-100;
        rForward = int(buffer[2])-100;
        lTurn = int(buffer[3])-100;
        rTurn = int(buffer[4])-100;
        Brain.Screen.printAt(20,210,true,"Active Robot %.2lf, %.2lf, %.2lf, %.2lf", lForward, rForward,lTurn,  rTurn);
    }
}



int vexLink(){
    
    while(true){
        Brain.Screen.clearScreen();
        Brain.Screen.printAt( 20, 190, true, "%d Link: %s", status, linkA.isLinked() ? "ok" : "--" );
        if(linkA.isLinked()){
            if(status == linkType::manager){
                if(linkA.isReceiving()){
                    linkA.received(rx_handler);
                }
                if(messageToSend.length() > 0){
                    sendMessage = true;
                    Link.send(messageToSend);
                }
                if(control == false){
                    Brain.Screen.printAt(20,210,true,"Sending COntrols %.2lf, %.2lf, %.2lf, %.2lf", lForward, rForward,lTurn,  rTurn);
                    Link.send(lForward,rForward,lTurn,rTurn);
                }
                else{
                    Link.send(targetX,targetY);
                }
            }
            else if(status == linkType::worker){
                if(messageToSend.length() > 0){
                    sendMessage = true;
                    Link.send(messageToSend);
                }
                linkA.received(rx_handler);
            }
        }
        else{
            control = true;
        }
        wait(10,msec);

    }
}