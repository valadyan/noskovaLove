#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <myfigura.h>
//#include <QMatrix4x4>
#include <QMouseEvent>
#include <QFuture>
#include <QtConcurrent>

#include <QSlider>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent* event);
//    void mouseMoveEvent(QMouseEvent* );
    void mousePressEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );
//    void mouseDoubleClickEvent(QMouseEvent* );
public slots:
    void update_slot(){update();}
private:
    QSlider* slider;
    int start_x_position;
    int start_y_position;
//    QPoint* startPoint=nullptr;
    myfigura* my_fig;
    QMatrix4x4* matrix;
};

#endif // MAINWINDOW_H
