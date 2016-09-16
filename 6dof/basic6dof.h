#ifndef BASIC6DOF_H
#define BASIC6DOF_H


class basic6Dof
{
public:
    basic6Dof();

    int getLegOne() const;
    void setLegOne(int value);

    int getLegTwo() const;
    void setLegTwo(int value);

    int getLegThree() const;
    void setLegThree(int value);

    int getLegFour() const;
    void setLegFour(int value);

    int getLegFive() const;
    void setLegFive(int value);

    int getLegSix() const;
    void setLegSix(int value);


private:
    int legOne;
    int legTwo;
    int legThree;
    int legFour;
    int legFive;
    int legSix;

};

#endif // BASIC6DOF_H
