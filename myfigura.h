#ifndef MYFIGURA_H
#define MYFIGURA_H

#include <QObject>

#include<my3dthinth.h>

class myfigura: public My3DThinth
{
public:
    myfigura(int _R1, int _R2, int _n, int _h);
    myfigura(myfigura&&);
    myfigura(const myfigura&);
    virtual ~myfigura();

    void operator *=(const QMatrix4x4*);
    myfigura& operator =(myfigura&&);
    myfigura& operator =(myfigura& mf);

private:
    void doPointEdit();
    int R1, aproksimation;
    int R2;
    int h;
};

#endif // MYFIGURA_H
