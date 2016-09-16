#ifndef SERVO6DOF_H
#define SERVO6DOF_H


class Servo6dof
{
public:
    Servo6dof();

    int getLegOne() const;
    void setLegOne(int value);

    int getLegTwo() const;
    void setLegTwo(int value);

    int getLegFour() const;
    void setLegFour(int value);

    int getLegFive() const;
    void setLegFive(int value);

    int getLegSix() const;
    void setLegSix(int value);

private:
    int legOne;
    int legTwo;
    int legFour;
    int legFive;
    int legSix;
    int caculate(int x,int y,int z, int roll, int pitch
};

#endif // SERVO6DOF_H
