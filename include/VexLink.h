/* this is to prevent multiple definitions */
#ifndef __VEXLINK_H__
#define __VEXLINK_H__

#include <string>

extern linkType status;
extern int vexLink();
extern double targetX;
extern double targetY;
extern bool messageRecieved;
extern bool sendMessage;
extern std::string messageToSend;
extern std::string recievedMessage;

namespace S{

    class link{
        public:
          
            void send(double x, double y);
            void send(std::string message);
    };
}
extern S::link Link;
#endif