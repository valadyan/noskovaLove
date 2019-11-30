#ifndef MYFIGURA_H
#define MYFIGURA_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>
#include <QLine>
#include <QSharedPointer>
#include <cmath>
#include <QList>
#include <QtConcurrent>
#include <QMutex>

#include<my3dthinth.h>


class myfigura: public QObject, public My3DThinth
{
    Q_OBJECT
public:
    myfigura(int _R1, int _R2, int _n, int _h);
//    myfigura(const QList<std::shared_ptr<QVector3D>>& points);
    myfigura(myfigura&&);
//    myfigura(const myfigura&);
    virtual ~myfigura();
//    void setR1(int r);
//    void setR2(int r);
//    void setH2(int h);
//    void setN1(int n);
//    void setH(int h);

    static void remake_this_shit(myfigura* mfp, int R1, int R2, int a, int h);
    void operator *=(const QMatrix4x4&);
    myfigura& operator =(myfigura&&);

public slots:
    void aprok_change_slot(int);
//    void R1_change_slot(int);
//    void R2_change_slot(int);
//    void H1_change_slot(int);
//    void H2_change_slot(int);
signals:
    void figChanged();
private:
    QMutex mutex;
    void doPointEdit();
    myfigura&& make_fig(int _R1, int _R2, int _n, int _h);
    int R1, aproksimation;
    int R2;
    int h;
};

#endif // MYFIGURA_H
