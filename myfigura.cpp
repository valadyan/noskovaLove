#include "myfigura.h"
#include<QDebug>

using namespace Geometry;

myfigura::myfigura(myfigura&& mf){
    R1=mf.R1;
    R2=mf.R2;
    aproksimation=mf.aproksimation;
    h=mf.h;
    planes=std::move(mf.planes);
    nodes=std::move(mf.nodes);
    mf.planes.clear();
    mf.nodes.clear();
}

myfigura::myfigura(const myfigura& mf){
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
    for(auto& n: nodes){
        n->operator *=(matr);
    }
}

myfigura& myfigura::operator =(myfigura&& mf){
    R1=mf.R1;
    R2=mf.R2;
    aproksimation=mf.aproksimation;
    h=mf.h;
    nodes=std::move(mf.nodes);
    planes=std::move(mf.planes);
    mf.planes.clear();
    mf.nodes.clear();
    return *this;
}
myfigura& myfigura::operator =(myfigura& mf){
    R1=mf.R1;
    R2=mf.R2;
    aproksimation=mf.aproksimation;
    h=mf.h;
    nodes=std::move(mf.nodes);
    planes=std::move(mf.planes);
    mf.planes.clear();
    mf.nodes.clear();
    return *this;
}

auto makePlane = [] (std::shared_ptr<Node> p1, std::shared_ptr<Node> p2, std::shared_ptr<Node> p3)
{
    QList<std::shared_ptr<Node>> nodes;
    nodes.push_back(p1);
    nodes.push_back(p2);
    nodes.push_back(p3);
    std::shared_ptr<Plane> plane(new Plane(nodes));
    return plane;
};

myfigura::myfigura(int _R1, int _R2, int _n, int _h): R1(_R1), R2(_R2), aproksimation(_n), h(_h)
{
    Point p(QVector3D(0,0,0));
    std::shared_ptr<Node> topNode(new Node(p));
    nodes.push_back(topNode);

    float alf=2*3.14/aproksimation;

    QList<std::shared_ptr<Node>> coneBaseList;

    Point baseP(QVector3D(h,R2*sin(alf*0),R2*cos(alf*0)));
    std::shared_ptr<Node> baseNode(new Node(baseP));
    nodes.push_back(std::shared_ptr<Node>(baseNode));
    coneBaseList.append(baseNode);
    std::shared_ptr<Node> firstBaseNode = baseNode;

    for(int i=1; i<aproksimation; i++){//conebase
        Point p(QVector3D(h,R2*sin(alf*i),R2*cos(alf*i)));
        std::shared_ptr<Node> nextBaseNode(new Node(p));
        nodes.push_back(nextBaseNode);
        planes.push_back(std::shared_ptr<Plane>(makePlane(topNode, baseNode, nextBaseNode)));
        coneBaseList.push_front(nextBaseNode);//reverse sequence for isSeen() method
        baseNode = nextBaseNode;
    }

    planes.push_back(std::shared_ptr<Plane>(makePlane(topNode, baseNode, firstBaseNode)));

    planes.push_back(std::shared_ptr<Plane>(new Plane(coneBaseList)));

//    doPointEdit();
}

myfigura::~myfigura(){
}
