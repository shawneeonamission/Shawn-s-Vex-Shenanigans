/* this is to prevent multiple definitions */
#ifndef __VEXLINK_H__
#define __VEXLINK_H__

extern linkType status;
extern int vexLink();

namespace S{

    class link{
        public:
            void send(double x, double y);
            void send(std::string message);
    };
}

#endif