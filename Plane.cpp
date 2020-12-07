#include "Plane.h"

using namespace Geometry;

Plane::Plane(QList<Node*>& points):
    nodes(points)//(*points.front())
{
//            for(auto p=++points.begin(); p!=points.end(); p++)
//                nodes.addFriend(*p);
}

Plane& Plane::operator =(const Plane& p)
{
    nodes=p.nodes;
    return *this;
}

QList<Node*> Plane::getNodes()
{
  return nodes;
}

QList<QLine> Plane::getLines()
{
    QList<QLine> lines;
    auto iterN=nodes.begin();
    auto iter2=iterN+1;
    auto preEnd=--nodes.end();
    while(iter2!=preEnd){
        lines.push_back(QLine((*iterN++)->getPoint()->getVec().toPoint(), (*iter2++)->getPoint()->getVec().toPoint()));
    }
    lines.push_back(QLine((*iter2)->getPoint()->getVec().toPoint(), (*nodes.begin())->getPoint()->getVec().toPoint()));
    return lines;
}

bool Plane::isSeen()
{
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
