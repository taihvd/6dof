#ifndef SERVO6DOF_H
#define SERVO6DOF_H
#include "basic6dof.h"

class Servo6Dof :public basic6Dof
{
public:
    Servo6Dof();
    bool caculate(int x, int y, int z, int roll, int pitch, int yaw);
};

#endif // SERVO6DOF_H
