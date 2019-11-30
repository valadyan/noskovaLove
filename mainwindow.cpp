#include "mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{

    slider=new QSlider(this);
    slider->setFixedSize(30,100);
    slider->setRange(3,15);
    slider->setTickInterval(1);

    bLeft=new QPushButton("leftView",this);
    bTop=new QPushButton("topView",this);
    bFront=new QPushButton("frontView",this);
    chBox= new QCheckBox(this);

    bLeft->setGeometry(20,0,100,30);
    bTop->setGeometry(200,0,100,30);
    bFront->setGeometry(400,0,100,30);
    chBox->setGeometry(550,0,30,30);

    connect(bLeft, &QPushButton::clicked, this, &MainWindow::showLeft);
    connect(bTop, &QPushButton::clicked, this, &MainWindow::showTop);
    connect(bFront, &QPushButton::clicked, this, &MainWindow::showFront);
    connect(chBox, &QCheckBox::clicked, this, &MainWindow::update_slot);

    setGeometry(100,100,600,600);
    my_fig=new myfigura(50,150,7,120);
    connect(slider, &QSlider::sliderMoved, my_fig, &myfigura::aprok_change_slot);
    connect(my_fig, &myfigura::figChanged, this, &MainWindow::update_slot);
}

void MainWindow::mousePressEvent(QMouseEvent* mouseEvent){
    start_x_position=mouseEvent->x();
    start_y_position=mouseEvent->y();
}

//void MainWindow::mouseDoubleClickEvent(QMouseEvent* mouseEvent){
//    qDebug("двойной клик");
//    startPoint=new QPoint(mouseEvent->pos());
//}

void MainWindow::mouseReleaseEvent(QMouseEvent* mouseEvent){
//    QMatrix4x4 moveMatrix;
//    int a=startPoint->x()-mouseEvent->x();
//    int b=startPoint->y()-mouseEvent->y();
//    if(startPoint){
//        moveMatrix=QMatrix4x4(1,0,0,0,
//                              0,1,0,0,
//                              0,0,1,0,
//                              a,b,0,1);
//        (*my_fig)*=moveMatrix;
//        delete startPoint;
//        update();
//        return;
//    }
    auto dx=2*3.14*(start_x_position-mouseEvent->x());//в радианах
    auto dy=2*3.14*(start_y_position-mouseEvent->y());
//    QMatrix4x4 matrixX;
//    QMatrix4x4 matrixY;
    if(mouseEvent->button() == Qt::LeftButton){//поворо по x y
//          matrixX=QMatrix4x4(1,0,0,0,
//                             0,cos(dx),sin(dx),0,
//                             0,-sin(dx),cos(dx),0,
//                             0,0,0,1);
//          matrixY=QMatrix4x4(cos(dy),0,-sin(dy),0,
//                             0,1,0,0,
//                             sin(dy),0,cos(dy),0,
//                             0,0,0,1);
          (*my_fig)*=QMatrix4x4(1,0,0,0,
                                0,cos(dx),sin(dx),0,
                                0,-sin(dx),cos(dx),0,
                                0,0,0,1)*QMatrix4x4(cos(dy),0,-sin(dy),0,
                                                    0,1,0,0,
                                                    sin(dy),0,cos(dy),0,
                                                    0,0,0,1);
          update();
    }
    QMatrix4x4 matrixZ;
    if(mouseEvent->button() == Qt::RightButton){//po z
        matrixZ=QMatrix4x4(cos(dx),sin(dx),0,0,
                           -sin(dx),cos(dx),0,0,
                           0,0,1,0,
                           0,0,0,1);
        (*my_fig)*=matrixZ;
        update();
    }
}

void MainWindow::showTop(){
    (*my_fig)*=QMatrix4x4(1,0,0,0,
                          0,1,0,0,
                          0,0,0,0,
                          0,0,0,1);
    update();
}
void MainWindow::showLeft(){
    (*my_fig)*=QMatrix4x4(0,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          0,0,0,1);
    update();
}
void MainWindow::showFront(){
    (*my_fig)*=QMatrix4x4(1,0,0,0,
                          0,0,0,0,
                          0,0,1,0,
                          0,0,0,1);
    update();
}



void MainWindow::showSeenLines(QPainter* painter){

}

void MainWindow::paintEvent(QPaintEvent *)
{
    qDebug("событие  отрисовки дошло");

    if(!my_fig) return;

    QPainter painter(this);

    QPoint centerPoint(geometry().size().width()/2,geometry().size().height()/2);

    painter.fillRect(0,0, geometry().width(), geometry().height(), QBrush(QColor(0,110,200)));

    if(chBox->isDown()){
        showSeenLines(&painter);
        return;
    }

    for(auto& pvec: my_fig->getPoints()){
        painter.drawEllipse(pvec.toPoint()+centerPoint, 5,5);
    }
    for(auto& pline: my_fig->getLines()){
        painter.drawLine(pline.getLine().translated(centerPoint));
    }
}

MainWindow::~MainWindow()
{
    delete my_fig;
}
