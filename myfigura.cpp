#include "myfigura.h"
#include<QDebug>

myfigura::myfigura(myfigura&& mf){
    points1=std::move(mf.points1);
    rebra1=std::move(mf.rebra1);
    grani1=std::move(mf.grani1);
    points2=std::move(mf.points2);
    rebra2=std::move(mf.rebra2);
    grani2=std::move(mf.grani2);
    R1=mf.R1;
    R2=mf.R2;
    n=mf.n;
    h=mf.h;
}

//myfigura::myfigura(const myfigura& mf){
//    points1=mf.points1;
//    rebra1=mf.rebra1;
//    grani1=mf.grani1;
//}

myfigura&& myfigura::make_fig(int _R1, int _R2, int _n, int _h){
    return std::move(myfigura( _R1,  _R2,  _n,  _h));
}

void myfigura::aprok_change_slot(int a){
    qDebug()<<a;
//    *this=make_fig(R1, R2, a, h);
    mutex.lock();
    QtConcurrent::run(remake_this_shit, this, R1, R2, a, h);
    emit figChanged();
    mutex.unlock();
}

void myfigura::doPointEdit(QList<QSharedPointer<QVector3D>>& points, QList<QSharedPointer<QLine>>& rebra, QList<QSharedPointer<gran>>& grani)
{
    int aproksimation=points.size();
    rebra.clear();
    auto point_iterator1=points.cbegin();//vershina
    auto point_iterator2=point_iterator1;
    for(auto i=0; i<aproksimation; i++){
        rebra.push_back(QSharedPointer<QLine>(new QLine((*points.cbegin())->toPoint(), (*point_iterator1++)->toPoint())));
        if(point_iterator1==points.cend()){
            rebra.push_back(QSharedPointer<QLine>(new QLine((*--point_iterator1)->toPoint(), (*points.cbegin())->toPoint())));
            rebra.push_back(QSharedPointer<QLine>(new QLine((*point_iterator1)->toPoint(), (*++points.cbegin())->toPoint())));
            break;
        }
        rebra.push_back(QSharedPointer<QLine>(new QLine((*point_iterator1)->toPoint(), (*point_iterator2++)->toPoint())));
    }
    grani.clear();
    qDebug()<<"mhv";
    auto rebraIter=rebra.cbegin();
    for(int i=0; i<aproksimation; i++){
        QLine* linemas=new QLine[3];
        linemas[0]=*(*rebraIter++);
        linemas[1]=*(*rebraIter++);
        linemas[2]=*(*rebraIter);
        grani.push_back(QSharedPointer<gran>(new gran(linemas, 3)));
    }

    point_iterator1=points.cbegin();//vershina
    point_iterator1++;
    point_iterator2=++point_iterator1;
    QLine* osnovanie=new QLine[aproksimation];
    for(int i=0; i<aproksimation ; i++){
        osnovanie[i]=QLine((*point_iterator1++)->toPoint(), (*point_iterator2++)->toPoint());
        if(point_iterator2==points.cend()){
            osnovanie[i+1]=QLine((*++points.cbegin())->toPoint(), (*--point_iterator2)->toPoint());
            break;
        }
    }
    grani.push_back(QSharedPointer<gran>(new gran(osnovanie, n)));
}

void myfigura::remake_this_shit(myfigura* mfp, int R1, int R2, int a, int h){
    *mfp=myfigura(R1, R2, a, h);
}

void myfigura::operator *=(const QMatrix4x4& matr){
    for(auto& vec: points1){
        *vec=matr*(*vec);
    }
    for(auto& vec: points2){
        *vec=matr*(*vec);
    }
    doPointEdit(points1, rebra1, grani1);
    doPointEdit(points2, rebra2, grani2);
}

myfigura& myfigura::operator =(myfigura&& mf){
    points1=std::move(mf.points1);
    rebra1=std::move(mf.rebra1);
    grani1=std::move(mf.grani1);
    points2=std::move(mf.points2);
    rebra2=std::move(mf.rebra2);
    grani2=std::move(mf.grani2);
    R1=mf.R1;
    R2=mf.R2;
    n=mf.n;
    h=mf.h;
}


//myfigura::myfigura(const QList<QSharedPointer<QVector3D>>& points){

//    points1=points;
//    doPointEdit(points2, rebra2, grani2);
//    doPointEdit(points1, rebra1, grani1);
//}

myfigura::myfigura(int _R1, int _R2, int _n, int _h): R1(_R1), R2(_R2), n(_n), h(_h)
{

    points1.push_back(QSharedPointer<QVector3D>(new QVector3D(0,0,0)));//вершина конуса
    points2.push_back(QSharedPointer<QVector3D>(new QVector3D(0,0,0)));//вершина конуса

    float alf=2*3.14/n;

    for(int i=0; i<n; i++){//сюда тасуешь свои точки
        points1.push_back(QSharedPointer<QVector3D>(new QVector3D(h,R1*sin(alf*i),R1*cos(alf*i))));
    }
    for(int i=0; i<n; i++){//сюда тасуешь свои точки
        points2.push_back(QSharedPointer<QVector3D>(new QVector3D(h,R2*sin(alf*i),R2*cos(alf*i))));
    }

    doPointEdit(points1, rebra1, grani1);//тута они соединяются
    doPointEdit(points2, rebra2, grani2);
}
class gran;
const QList<QSharedPointer<QVector3D>>& myfigura::get_points1(){
    return points1;
}
const QList<QSharedPointer<QVector3D>>& myfigura::get_points2(){
    return points2;
}
const QList<QSharedPointer<QLine>>& myfigura::get_rebra1(){
    return rebra1;
}
const QList<QSharedPointer<QLine>>& myfigura::get_rebra2(){
    return rebra2;
}
myfigura::~myfigura(){
//    for(auto &d: points1){
//        delete d;
//    }
//    for(auto &d: rebra1){
//        delete d;
//    }
//    for(auto &d: grani1){
//        delete d;
//    }
}
