#include "myfigura.h"
#include<QDebug>

myfigura::myfigura(myfigura&& mf){
    R1=mf.R1;
    R2=mf.R2;
    aproksimation=mf.aproksimation;
    h=mf.h;
    pointList=std::move(mf.pointList);
    lineList=std::move(mf.lineList);
    planeList=std::move(mf.planeList);
    mf.pointList.clear();
    mf.lineList.clear();
    mf.planeList.clear();
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

void myfigura::doPointEdit()
{
    lineList.clear();
    planeList.clear();
    auto point_iterator1=pointList.cbegin();//vershina
    point_iterator1++;
    auto point_iterator2=point_iterator1;
    for(auto i=0; i<aproksimation-1; i++){
        lineList.push_back(MyLine3D(*pointList.cbegin(), (*point_iterator1++)));
        lineList.push_back(MyLine3D(*point_iterator1, *point_iterator2++));
    }
    lineList.push_back(MyLine3D(*point_iterator1, *pointList.cbegin()));
    lineList.push_back(MyLine3D(*point_iterator1, *++pointList.cbegin()));
     auto insideBegin=++point_iterator1;//begin of inside triengle
     point_iterator2=point_iterator1;
            for(auto i=0; i<aproksimation-1; i++){
                lineList.push_back(MyLine3D(*pointList.cbegin(), (*point_iterator1++)));
                lineList.push_back(MyLine3D(*point_iterator1, *point_iterator2++));
            }
            lineList.push_back(MyLine3D(*point_iterator1, *pointList.cbegin()));
            lineList.push_back(MyLine3D(*point_iterator1, *insideBegin));

    auto rebraIter=lineList.cbegin();
            MyLine3D* linemas= new MyLine3D[3];
            MyLine3D* osnovanie= new MyLine3D[aproksimation];
    for(int i=0; i<aproksimation-1; i++){
        linemas[0]=(*rebraIter++);
        *(osnovanie+i)=(*rebraIter);
        linemas[1]=(*rebraIter++);
        linemas[2]=(*rebraIter);
        planeList.push_back(MyPlane(3, linemas));
    }
    linemas[0]=(*rebraIter++);
    *(osnovanie+aproksimation-1)=(*rebraIter);
    linemas[1]=(*rebraIter);
    linemas[2]=*lineList.cbegin();
    planeList.push_back(MyPlane(3, linemas));
    planeList.push_back(MyPlane(aproksimation, osnovanie));
    auto insideBeg=++rebraIter;
    for(int i=0; i<aproksimation-1; i++){//inside planes
        linemas[2]=(*rebraIter++);
        *(osnovanie+aproksimation-1-i)=(*rebraIter);
        linemas[1]=(*rebraIter++);
        linemas[0]=(*rebraIter);
        planeList.push_back(MyPlane(3, linemas));
    }
    linemas[2]=(*rebraIter++);
    *(osnovanie)=(*rebraIter);
    linemas[1]=(*rebraIter);
    linemas[0]=*insideBeg;
    planeList.push_back(MyPlane(3, linemas));
    planeList.push_back(MyPlane(aproksimation, osnovanie));
}

void myfigura::remake_this_shit(myfigura* mfp, int R1, int R2, int a, int h){
    *mfp=std::move(myfigura(R1, R2, a, h));
}

void myfigura::operator *=(const QMatrix4x4& matr){
    for(auto& vec: pointList){
        vec=matr*vec;
    }
    doPointEdit();
}

myfigura& myfigura::operator =(myfigura&& mf){
    R1=mf.R1;
    R2=mf.R2;
    aproksimation=mf.aproksimation;
    h=mf.h;
    pointList=std::move(mf.pointList);
    lineList=std::move(mf.lineList);
    planeList=std::move(mf.planeList);
    mf.pointList.clear();
    mf.lineList.clear();
    mf.planeList.clear();
}


//myfigura::myfigura(const QList<QSharedPointer<QVector3D>>& points){

//    points1=points;
//    doPointEdit(points2, rebra2, grani2);
//    doPointEdit(points1, rebra1, grani1);
//}

myfigura::myfigura(int _R1, int _R2, int _n, int _h): R1(_R1), R2(_R2), aproksimation(_n), h(_h)
{

    pointList.push_back(QVector3D(0,0,0));//вершина конуса

    float alf=2*3.14/aproksimation;

    for(int i=0; i<aproksimation; i++){//сюда тасуешь свои точки
        pointList.push_back(QVector3D(h,R1*sin(alf*i),R1*cos(alf*i)));
    }
    for(int i=0; i<aproksimation; i++){//сюда тасуешь свои точки
        pointList.push_back(QVector3D(h,R2*sin(alf*i),R2*cos(alf*i)));
    }
    doPointEdit();
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
