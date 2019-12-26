#ifndef MY3DTHINTH_H
#define MY3DTHINTH_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QLine>
#include <cmath>
#include <QList>
#include <QDebug>
#include <memory>


class Plane;

class MyPoint
{
    QVector3D _point;
public:
    MyPoint()=default;
    MyPoint(const QVector3D& p) {_point=p;}
    QVector3D getVec(){return _point;}
    MyPoint& operator *=(const QMatrix4x4* m){
        _point=_point*(*m);
        return *this;
    }
};

class Node
{
    typedef std::shared_ptr<MyPoint> PointPointer;
    PointPointer _point;
    QList<std::shared_ptr<Node>> _friends;
public:
    Node()=default;
    Node(MyPoint* point):_point(PointPointer(point)){}
    Node& operator =(const Node& n){
        _point=n._point;
        _friends=n._friends;
        return *this;
    }
    PointPointer getPoint(){return _point;}
    QList<QLine> getLines(){
        QList<QLine> lines;
        for(auto n: _friends){
            lines.push_back(QLine(_point->getVec().toPoint(), n->getPoint()->getVec().toPoint()));
        }
        return lines;
    }
    QList<MyPoint> getPoints(){
        QList<MyPoint> points;
        points.push_back(*_point);
        for(auto n: _friends){
            points.push_back(*(n->getPoint()));
        }
        return points;
    }
    void addFriend(Node* friend_){_friends.push_back(std::shared_ptr<Node>(friend_));}
};

class My3DThinth
{
public:
    My3DThinth();
    class Plane
    {
    public:
        QList<Node*> nodes;
        Plane(QList<Node*>& points):
            nodes(points)//(*points.front())
        {
//            for(auto p=++points.begin(); p!=points.end(); p++)
//                nodes.addFriend(*p);
        }
        Plane& operator =(const Plane& p){
            nodes=p.nodes;
            return *this;
        }
        QList<QLine> getLines(){
            QList<QLine> lines;
            auto iterN=nodes.begin();
            auto iter2=nodes.begin()++;
            auto preEnd=--nodes.end();
            while(iter2!=preEnd){
                lines.push_back(QLine((*iterN++)->getPoint()->getVec().toPoint(), (*iter2++)->getPoint()->getVec().toPoint()));
            }
            lines.push_back(QLine((*iter2)->getPoint()->getVec().toPoint(), (*nodes.begin())->getPoint()->getVec().toPoint()));
            return lines;
        }
        bool isSeen(){
//            auto pointsList=nodes.getPoints();
            auto p0=nodes[0]->getPoint()->getVec();
            auto p1=nodes[1]->getPoint()->getVec();
            auto p2=nodes[2]->getPoint()->getVec();
            double xa= p0.y()* p1.z() + p1.y()* p2.z() + p2.y()* p0.z() - p1.y()* p0.z() - p2.y()* p1.z() -p0.y()* p2.z();
            double ya= p0.z()* p1.x() + p1.z()* p2.x() + p2.z()* p0.x() - p1.z()* p0.x() - p2.z()* p1.x() -p0.z()* p2.x();
            double za= p0.x()* p1.y() + p1.x()* p2.y() + p2.x()* p0.y() - p1.x()* p0.y() - p2.x()* p1.y() -p0.x()* p2.y();
            double xb = 0;
            double yb = 0;
            double zb = 1;

            double axb = xa * xb + ya * yb + za * zb;
            double a = sqrt(xa * xa + ya * ya + za * za);
            double b = sqrt(xb * xb + yb * yb + zb * zb);
            double cos = axb / (a * b);
            double acos_ = acos(cos) * 180 / 3.14;
            if (acos_ < 90)
            {
                return true;
//              PointF[] p = new PointF[3];
//              p[0].X = (float)p0.X;
//              p[1].X = (float)p1.X;
//              p[2].X = (float)p2.X;
//              p[0].Y = (float)p0.Y;
//              p[1].Y = (float)p1.Y;
//              p[2].Y = (float)p2.Y;
//              g.FillPolygon(solidBrush, p);
            }
            return false;
        }
    };
    QList<std::shared_ptr<MyPoint>> getPoints(){
        return points;
    }
    QList<std::shared_ptr<Plane>> getPlanes(){
        return planes;
    }
    QList<std::shared_ptr<Node>> getNodes(){
        return nodes;
    }
protected:
    QList<std::shared_ptr<Plane>> planes;
    QList<std::shared_ptr<MyPoint>> points;
    QList<std::shared_ptr<Node>> nodes;
};

#endif // MY3DTHINTH_H
