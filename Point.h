#ifndef POINT_H
#define POINT_H

#include <QMatrix4x4>
#include <QVector3D>

namespace Geometry {

  class Point
  {
      QVector3D _point;
  public:
      Point()=default;
      Point(const QVector3D& p) {_point=p;}
      QVector3D getVec(){return _point;}
      Point& operator *=(const QMatrix4x4* m){
          _point=_point*(*m);
          return *this;
      }
  };

}
#endif // POINT_H
