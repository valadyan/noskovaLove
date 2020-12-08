#ifndef PLANE_H
#define PLANE_H

#include "Node.h"
#include <QList>
#include <cmath>

namespace Geometry {

  class Plane
  {
    QList<std::shared_ptr<Node>> nodes;
  public:
    Plane()=default;
    Plane(QList<std::shared_ptr<Node>>& points);
    Plane& operator =(const Plane& p);
    QList<std::shared_ptr<Node>> getNodes();
    QList<QLine> getLines();
    bool isSeen();
  };

}
#endif // PLANE_H
