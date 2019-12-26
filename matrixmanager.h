#ifndef MATRIXMANAGER_H
#define MATRIXMANAGER_H

#include<QMatrix4x4>
#include <cmath>

#define PI 3.14159265

class MatrixManager
{
public:
    MatrixManager();
    static QMatrix4x4* getRotateMatrix(int dx, int dy, int dz){
        return new QMatrix4x4(QMatrix4x4(1,0,0,0,
                          0,cos(dx),sin(dx),0,
                          0,-sin(dx),cos(dx),0,
                          0,0,0,1)*QMatrix4x4(cos(dy),0,-sin(dy),0,
                                              0,1,0,0,
                                              sin(dy),0,cos(dy),0,
                                              0,0,0,1)*QMatrix4x4(cos(dz),sin(dz),0,0,
                                                                 -sin(dz),cos(dz),0,0,
                                                                 0,0,1,0,
                                                                 0,0,0,1));
    }
    static QMatrix4x4* getMoveMatrix(double dX, double dY, double dZ)
    {
        QMatrix4x4* T = getSimpleMatrix();
        T->operator ()(3, 0) = dX;
        T->operator ()(3, 1) = dY;
        T->operator ()(3, 2) = dZ;
        return T;
    }
    static QMatrix4x4* getScaleMatrix(double dX, double dY, double dZ)
    {
        QMatrix4x4* T = getSimpleMatrix();
        T->operator ()(0, 0) = dX;
        T->operator ()(1, 1) = dY;
        T->operator ()(2, 2) = dZ;
        return T;
    }
    static QMatrix4x4* getFrontViewMatrix()
    {
        QMatrix4x4* T = getSimpleMatrix();
        T->operator ()(2, 2) = 0;
        return T;
    }
    static QMatrix4x4* getLeftViewMatrix()
    {
        QMatrix4x4* T = getSimpleMatrix();
        T->operator ()(0, 0) = 0;
        return T;
    }
    static QMatrix4x4* getTopViewMatrix()
    {
        QMatrix4x4* T = getSimpleMatrix();
        T->operator ()(1, 1) = 0;
        return T;
    }
    static QMatrix4x4* getSimpleMatrix()
    {
        return new QMatrix4x4(1,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          0,0,0,1);
    }
    static QMatrix4x4* getAxonometricMatrix(double aX, double aY, double aZ)
    {
        return getRotateMatrix(aX, aY, aZ);
    }
    static QMatrix4x4* getObliqueMatrix(double L, double a)//cosoug
    {
        return new QMatrix4x4(1,0,0,0,
                          0,1,0,0,
                          L*cos(a),L*sin(a),0,0,
                          0,0,0,1);

    }
    static QMatrix4x4* getPerspectiveMatrix(double d, double pointsCount)
    {
        /*     M persp
         * ...          ...  ...          ...  ...          ...
         * | 1  0  0   0  |  | 1  0  0   0  |  | 1  0  0  1/d |
         * | 0  1  0   0  |  | 0  1  0  1/d |  | 0  1  0  1/d |
         * | 0  0  1  1/d |  | 0  0  1  1/d |  | 0  0  1  1/d |
         * | 0  0  0   0  |  | 0  0  0   0  |  | 0  0  0   0  |
         * '''          '''  '''          '''  '''          '''
         */
        QMatrix4x4* M = getSimpleMatrix();

        if (abs(d) < 0.0001) d = 0.00001;
        switch ((int)pointsCount)
        {
            case 1:
                M->operator ()(2, 3) = 1 / d;
                break;
            case 2:
                M->operator ()(2, 3) = 1 / d;
                M->operator ()(1, 3) = 1 / d;
                break;
            case 3:
                M->operator ()(2, 3) = 1 / d;
                M->operator ()(1, 3) = 1 / d;
                M->operator ()(0, 3) = 1 / d;
                break;
        }

        M->operator ()(3, 3) = 0;
        return M;
    }
    static QMatrix4x4* getViewTransformationMatrix(double r, double f, double t, bool isWCS)
            {
                /*
                 *  V = T * Rz * Rx * S // S - переход от левой к правой ск и обратно
                 *  input: ρ φ θ
                 * ...                                    ...
                 * | -sin(θ) -cos(φ)cos(θ) -sin(φ)cos(θ)  0 |
                 * |  cosθ   -cos(φ)sin(θ) -sin(φ)sin(θ)  0 |
                 * |    0        sin(φ)       -cos(φ)     0 |
                 * |    0          0             ρ        1 |
                 * '''                                    '''
                 */

                QMatrix4x4* T = getSimpleMatrix();
                T->operator ()(3, 0) = -r * sin(f) * cos(t);
                T->operator ()(3, 1) = -r * sin(f) * sin(t);
                T->operator ()(3, 2) = -r * cos(f);

                auto Rz = QMatrix4x4
                             (
                                 cos(PI/2 - t), sin(PI/2 - t), 0, 0,
                                 -sin(PI/2 - t), cos(PI/2 - t), 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1
                             );

                auto Rx = QMatrix4x4
                             (
                                 1, 0, 0, 0,
                                 0, cos(f - PI), sin(f - PI), 0,
                                 0, sin(f - PI), cos(f - PI), 0,
                                 0, 0, 0, 1
                             );
                QMatrix4x4* S = getSimpleMatrix(); // для преобразования правой в левую (мировой в видовую)
                S->operator ()(2, 2) = -1;

                QMatrix4x4* V = new QMatrix4x4(Rz*Rx*(*T));
                if (isWCS)
                    *V = (*V)* (*S);

                return V;
    }
};

#endif // MATRIXMANAGER_H
