#ifndef PLANE_H
#define PLANE_H

#include "Node.h"
#include <QList>
#include <cmath>

namespace Geometry {

  class Plane
  {
  public:
      QList<Node*> nodes;
      Plane(QList<Node*>& points);
      Plane& operator =(const Plane& p);
      QList<Node*> getNodes();
      QList<QLine> getLines();
      bool isSeen();
  };

}
#endif // PLANE_H
