#include "Node.h"

using namespace Geometry;

Node::Node(Point* point):_point(PointPointer(point)){}

Node& Node::operator =(const Node& n){
    _point=n._point;
    _friends=n._friends;
    return *this;
}

Node::PointPointer Node::getPoint()
{
    return _point;
}

QList<QLine> Node::getLines()
{
    QList<QLine> lines;
    for(auto n: _friends){
        lines.push_back(QLine(_point->getVec().toPoint(), n->getPoint()->getVec().toPoint()));
    }
    return lines;
}

QList<Point> Node::getPoints()
{
    QList<Point> points;
    points.push_back(*_point);
    for(auto n: _friends){
        points.push_back(*(n->getPoint()));
    }
    return points;
}

void Node::addFriend(Node* friend_)
{
    _friends.push_back(std::shared_ptr<Node>(friend_));
}
