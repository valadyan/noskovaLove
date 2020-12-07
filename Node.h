#ifndef NODE_H
#define NODE_H

#include "Point.h"
#include <QLine>
#include <memory>

namespace Geometry {

  class Node
  {
      typedef std::shared_ptr<Point> PointPointer;
      PointPointer _point;
      QList<std::shared_ptr<Node>> _friends;
  public:
      Node()=default;
      Node(Point* point);
      Node& operator =(const Node& n);
      PointPointer getPoint();
      QList<QLine> getLines();
      QList<Point> getPoints();
      void addFriend(Node* friend_);
  };

}
#endif // NODE_H
