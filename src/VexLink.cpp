//include vex.h and the header file you created
#include "vex.h"
#include "VexLink.h"
#include "odom.h"
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

serial_link linkA(PORT14,"CYCLN3_Cyclone_Robotics",status);
 





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


void rx_handler( uint8_t *buffer, int32_t length ) {
    if(buffer[0] == uint8_t('C')){
        targetX = double(buffer[1]) + (double(buffer[2])/100);
        targetY = double(buffer[3]) + (double(buffer[4])/100);
        Brain.Screen.printAt(10,110,true,"target value (%.2f.,%.2f)", targetX, targetY );
    }
    if(buffer[0] == uint8_t('S')){
        messageRecieved = true;
        for(int i = 0; i < length; i++){
            recievedMessage += buffer[i + 1];
        }
        
    }
}



int vexLink(){
    
    while(true){
        Brain.Screen.printAt( 10, 50, true, "Link: %s", linkA.isLinked() ? "ok" : "--" );
        if(linkA.isLinked()){
            if(status == linkType::manager){
                if(linkA.isReceiving()){
                    linkA.received(rx_handler);
                }
                if(messageToSend.length() > 0){
                    sendMessage = true;
                    Link.send(messageToSend);
                }
                else{
                    Link.send(finalPosX,finalPosY);
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
        wait(5,msec);
    }
}