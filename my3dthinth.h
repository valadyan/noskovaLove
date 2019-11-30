#ifndef MY3DTHINTH_H
#define MY3DTHINTH_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QLine>
#include <QSharedPointer>
#include <cmath>
#include <QList>

struct MyLine3D{
    MyLine3D()=default;
    MyLine3D(const QVector3D& a, const QVector3D& b){
        start=a;
        end=b;
    }
    QLine getLine(){return QLine(start.toPoint(), end.toPoint());}
    QVector3D start;
    QVector3D end;
    ~MyLine3D()=default;
};

class My3DThinth
{
public:
    My3DThinth();
    class MyPlane
    {
    public:
        QList<MyLine3D> lineList;
        MyPlane(int _num_of_lines, MyLine3D* p){
            for(auto i=0; i<_num_of_lines; i++){
                lineList.push_back(p[i]);
            }
        }
        MyPlane operator =(const MyPlane& g){
            lineList=g.lineList;
            return *this;
        }
        MyPlane(MyPlane&& g){
            lineList=g.lineList;
            g.lineList.clear();
        }
        MyPlane(const MyPlane& g){
            lineList=g.lineList;
        }
        QVector3D getCenterMass() {
        double x = 0;
        double y = 0;
        double z = 0;
        for(auto i: lineList)
        {
            x += i.start.x() / lineList.size();
            y += i.start.y() / lineList.size();
            z += i.start.z() / lineList.size();
        }
        return QVector3D(x,y,z);
    }
    };
    QList<QVector3D>& getPoints(){return pointList;}
    QList<MyLine3D>& getLines(){return lineList;}
    QList<MyPlane>& getPlanes(){return planeList;}
protected:
    QList<QVector3D> pointList;
    QList<MyLine3D> lineList;
    QList<MyPlane> planeList;
};

#endif // MY3DTHINTH_H
