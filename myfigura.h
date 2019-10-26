#ifndef MYFIGURA_H
#define MYFIGURA_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>
#include <QLine>
#include <QSharedPointer>
#include <cmath>
#include <QList>
#include <QtConcurrent>
#include <QMutex>

class myfigura: public QObject
{
    Q_OBJECT
public:
    myfigura(int _R1, int _R2, int _n, int _h);
//    myfigura(const QList<std::shared_ptr<QVector3D>>& points);
    myfigura(myfigura&&);
//    myfigura(const myfigura&);
    virtual ~myfigura();
    void setR1(int r);
    void setR2(int r);
    void setH2(int h);
    void setN1(int n);
    void setH(int h);
    class gran
    {
    public:
        QLine* mas;
        int num_of_lines;
        gran(QLine* p, int _num_of_lines){
            num_of_lines=_num_of_lines;
            mas=new QLine[num_of_lines];
            for(auto i=0; i<num_of_lines; i++){
                mas[i]=p[i];
            }
        }
        gran operator =(const gran& g){
            num_of_lines=g.num_of_lines;
            mas=new QLine[num_of_lines];
            for(auto i=0; i<num_of_lines; i++){
                mas[i]=g.mas[i];
            }
            return *this;
        }
        gran(gran&& g){
            mas=g.mas;
            g.mas=nullptr;
            num_of_lines=g.num_of_lines;
        }
        gran(const gran& g){
            num_of_lines=g.num_of_lines;
            mas=new QLine[num_of_lines];
            for(auto i=0; i<num_of_lines; i++){
                mas[i]=g.mas[i];
            }
        }
        ~gran(){delete mas;}
        //gran(int num_of_points, QLine* p) {mas=new QLine[num_of_points]; vcxv}
    };
    const QList<QSharedPointer<QVector3D>>& get_points1();
    const QList<QSharedPointer<QVector3D>>& get_points2();
    const QList<QSharedPointer<QLine>>& get_rebra1();
    const QList<QSharedPointer<QLine>>& get_rebra2();
    const QList<QSharedPointer<gran>>& get_grani1(){
        return grani1;
    }
    const QList<QSharedPointer<gran>>& get_grani2(){
        return grani2;
    }
    static void remake_this_shit(myfigura* mfp, int R1, int R2, int a, int h);
    void operator *=(const QMatrix4x4&);
    myfigura& operator =(myfigura&&);

public slots:
    void aprok_change_slot(int);
//    void R1_change_slot(int);
//    void R2_change_slot(int);
//    void H1_change_slot(int);
//    void H2_change_slot(int);
signals:
    void figChanged();
private:
    QMutex mutex;
    QList<QSharedPointer<QVector3D>> points1;
    QList<QSharedPointer<QLine>> rebra1;
    QList<QSharedPointer<QVector3D>> points2;
    QList<QSharedPointer<QLine>> rebra2;
    QList<QSharedPointer<gran>> grani1;
    QList<QSharedPointer<gran>> grani2;
    void doPointEdit(QList<QSharedPointer<QVector3D>>& points, QList<QSharedPointer<QLine>>& rebra, QList<QSharedPointer<gran>>& grani);
    myfigura&& make_fig(int _R1, int _R2, int _n, int _h);
    int R1, n;
    int R2;
    int h;
};

#endif // MYFIGURA_H
