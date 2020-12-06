#include "myfigura.h"
#include<QDebug>

myfigura::myfigura(myfigura&& mf){
    R1=mf.R1;
    R2=mf.R2;
    aproksimation=mf.aproksimation;
    h=mf.h;
    points=std::move(mf.points);
    planes=std::move(mf.planes);
    nodes=std::move(mf.nodes);
    mf.points.clear();
    mf.planes.clear();
    mf.nodes.clear();
}

myfigura::myfigura(const myfigura& mf){
    points=std::move(mf.points);
    planes=std::move(mf.planes);
    nodes=std::move(mf.nodes);
}

void refOn(Node* it, Node* onIt){
    it->addFriend(onIt);
}
void myfigura::doPointEdit()
{
//    planes.clear();

//    QList<Node*> osnovanie;
//    QList<Node*> osnovanieInside;

//    auto point_iterator1=nodes.cbegin();//vershina
//    point_iterator1++;
//    auto point_iterator2=point_iterator1;
//    osnovanie.push_back(point_iterator1->get());
//    for(auto i=0; i<aproksimation-1; i++){
//        refOn((point_iterator1++)->get(), nodes.cbegin()->get());
//        makePlane(point_iterator1->get(), point_iterator2->get());
//        refOn((point_iterator2++)->get(), point_iterator1->get());
//        osnovanie.push_back(point_iterator1->get());
//    }
//    refOn(point_iterator1->get(), nodes.cbegin()->get());
//    refOn(point_iterator1->get(), (++nodes.cbegin())->get());
//    makePlane(point_iterator1->get(), (++nodes.cbegin())->get());
//    auto insideBegin=++point_iterator1;//begin of inside triengle
//    point_iterator2=point_iterator1;
//    osnovanieInside.push_back(insideBegin->get());
//    for(auto i=0; i<aproksimation-1; i++){
//        refOn((point_iterator1++)->get(), nodes.cbegin()->get());
//        makePlane(point_iterator2->get(), point_iterator1->get());
//        refOn((point_iterator2++)->get(), point_iterator1->get());
//        osnovanieInside.push_back(point_iterator1->get());
//    }
//    refOn(point_iterator1->get(), nodes.cbegin()->get());
//    refOn(point_iterator1->get(), insideBegin->get());
//    makePlane(insideBegin->get(), point_iterator1->get());

//    planes.push_back(std::shared_ptr<Plane>(new Plane(osnovanie)));
//    planes.push_back(std::shared_ptr<Plane>(new Plane(osnovanieInside)));
}

void myfigura::operator *=(const QMatrix4x4* matr){
    for(auto& p: points){
        p->operator *=(matr);
    }
}

myfigura& myfigura::operator =(myfigura&& mf){
    R1=mf.R1;
    R2=mf.R2;
    aproksimation=mf.aproksimation;
    h=mf.h;
    points=std::move(mf.points);
    nodes=std::move(mf.nodes);
    planes=std::move(mf.planes);
    mf.points.clear();
    mf.planes.clear();
    mf.nodes.clear();
    return *this;
}
myfigura& myfigura::operator =(myfigura& mf){
    R1=mf.R1;
    R2=mf.R2;
    aproksimation=mf.aproksimation;
    h=mf.h;
    points=std::move(mf.points);
    nodes=std::move(mf.nodes);
    planes=std::move(mf.planes);
    mf.points.clear();
    mf.planes.clear();
    mf.nodes.clear();
    return *this;
}

auto makePlane = [] (Node* p1, Node* p2, Node* p3) ->My3DThinth::Plane*{
    QList<Node*> nodes;
    nodes.push_back(p1);
    nodes.push_back(p2);
    nodes.push_back(p3);
    My3DThinth::Plane* plane = new My3DThinth::Plane(nodes);
    return plane;
};

myfigura::myfigura(int _R1, int _R2, int _n, int _h): R1(_R1), R2(_R2), aproksimation(_n), h(_h)
{
    MyPoint* p=new MyPoint(QVector3D(0,0,0));
    points.push_back(std::shared_ptr<MyPoint>(p));//вершина конуса
    nodes.push_back(std::shared_ptr<Node>(new Node(p)));

    Node* topNode =new Node(p);

    float alf=2*3.14/aproksimation;

    MyPoint* baseP = new MyPoint(QVector3D(h,R2*sin(alf*0),R2*cos(alf*0)));//cone base node
    Node* baseNode = new Node(p);
    points.push_back(std::shared_ptr<MyPoint>(baseP));
    nodes.push_back(std::shared_ptr<Node>(baseNode));

    for(int i=1; i<aproksimation; i++){
        MyPoint* p = new MyPoint(QVector3D(h,R2*sin(alf*i),R2*cos(alf*i)));
        Node* nextBaseNode = new Node(p);
        points.push_back(std::shared_ptr<MyPoint>(p));
        nodes.push_back(std::shared_ptr<Node>(new Node(p)));
        planes.push_back(std::shared_ptr<Plane>(makePlane(baseNode, nextBaseNode, topNode)));
        baseNode = nextBaseNode;
    }
//    for(int i=0; i<aproksimation; i++){//сюда тасуешь свои точки
//        MyPoint* p=new MyPoint(QVector3D(h,R2*sin(alf*i),R2*cos(alf*i)));
//        points.push_back(std::shared_ptr<MyPoint>(p));
//        nodes.push_back(std::shared_ptr<Node>(new Node(p)));
//    }
//    doPointEdit();
}

myfigura::~myfigura(){
}
