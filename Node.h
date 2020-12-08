#ifndef NODE_H
#define NODE_H

#include "Point.h"
#include <QLine>
#include <memory>

namespace Geometry {

  class Node
  {
      Point _point;
      QList<std::shared_ptr<Node>> _friends;
  public:
      Node()=default;
      Node(const Point& point);
      Node& operator =(const Node& n);
      Node& operator *=(const QMatrix4x4* m);
      Point getPoint();
      QList<QLine> getLines();
      QList<Point> getPoints();
      void addFriend(Node* friend_);
  };

}
#endif // NODE_H
