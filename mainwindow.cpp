#include "mainwindow.h"

#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    utils= new Utils();
    utils->show();
    connect(utils, &Utils::sendMatrix, this, &MainWindow::useMatrix);
    connect(this, &MainWindow::destroyed, utils, &Utils::close);

    slider=new QSlider(this);
    slider->setFixedSize(30,100);
    slider->setRange(3,15);
    slider->setTickInterval(1);

    chBox= new QCheckBox(this);

    chBox->setGeometry(550,0,30,30);

    connect(chBox, &QCheckBox::clicked, this, &MainWindow::update_slot);

    setGeometry(600,100,600,600);
    R1=50; R2=150; aprox=7; h=120;
    my_fig=new myfigura(R1, R2, aprox, h);
//    (*my_fig)*=eyeMatrix;

    connect(slider, &QSlider::sliderMoved, this, &MainWindow::aprok_change_slot);
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
    int dx_, dy_;
    if(abs(start_x_position-mouseEvent->x())>100)dx_=100; else dx_=0;
            if(abs(start_y_position-mouseEvent->y())>100)dy_=100;else dy_=0;
    auto dx=2*3.14*(dx_);//в радианах
    auto dy=2*3.14*(dy_);

    if(mouseEvent->button() == Qt::LeftButton){//поворо по x y
          my_fig->operator *=(MatrixManager::getRotateMatrix(dx,dy,0));
          update();
    }
    if(mouseEvent->button() == Qt::RightButton){//po z
        my_fig->operator *=(MatrixManager::getRotateMatrix(0,0,dx));
        update();
    }
}

void MainWindow::aprok_change_slot(int a){
    qDebug()<<a;
    my_fig=new myfigura(R1, R2, a, h);
    update_slot();
}
//auto CalculateAngle=[](const QVector3D& vectorParams, const QVector3D& sideParams)
//{
//    double chisl = vectorParams.x() * sideParams.x() + vectorParams.y() * sideParams.y() + vectorParams.z() * sideParams.z();
//    double znam1 = sqrt(pow(vectorParams.x(), 2) + pow(vectorParams.y(), 2) + pow(vectorParams.z(), 2));
//    double znam2 = sqrt(pow(sideParams.x(), 2) + pow(sideParams.y(), 2) + pow(sideParams.z(), 2));

//    double otv = chisl / (znam1 * znam2);
//    return otv;

//};


void MainWindow::useMatrix(QMatrix4x4 m){
    qDebug()<<"was recived"<<m;
    my_fig->operator *=(new QMatrix4x4(m));
    update();
}

void MainWindow::showSeenLines(QPainter* painter){
    QPoint centerPoint(geometry().size().width()/2,geometry().size().height()/2);
    for(auto pl: my_fig->getPlanes()){
        if(pl->isSeen()){
            for(auto line: pl->getLines())
                painter->drawLine(line.translated(centerPoint));
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if(!my_fig) return;

    QPainter painter(this);

    QPoint centerPoint(geometry().size().width()/2,geometry().size().height()/2);

    painter.fillRect(0,0, geometry().width(), geometry().height(), QBrush(QColor(255,255,255)));

    if(chBox->isChecked()){
        showSeenLines(&painter);
        return;
    }

    for(auto pl: my_fig->getPlanes()){
      for(auto line: pl->getLines())
          painter.drawLine(line.translated(centerPoint));
    }
}

MainWindow::~MainWindow()
{
    delete my_fig;
}
