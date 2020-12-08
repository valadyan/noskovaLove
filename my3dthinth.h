#ifndef MY3DTHINTH_H
#define MY3DTHINTH_H

#include "Point.h"
#include "Node.h"
#include "Plane.h"
#include <QDebug>


namespace Geometry {

  class My3DThinth
  {
  public:
      My3DThinth();
      QList<std::shared_ptr<Plane>> getPlanes(){
          return planes;
      }
      QList<std::shared_ptr<Node>> getNodes(){
          return nodes;
      }
  protected:
      QList<std::shared_ptr<Plane>> planes;
      QList<std::shared_ptr<Node>> nodes;
  };

}

#endif // MY3DTHINTH_H
