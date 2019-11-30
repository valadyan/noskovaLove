#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <myfigura.h>
//#include <QMatrix4x4>
#include <QMouseEvent>
#include <QFuture>
#include <QtConcurrent>

#include <QPushButton>
#include <QSlider>
#include <QCheckBox>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* );
    void mouseReleaseEvent(QMouseEvent* );
//    void mouseMoveEvent(QMouseEvent* );
//    void mouseDoubleClickEvent(QMouseEvent* );
//    void setMatrix(const QMatrix4x4&);

public slots:
    void update_slot(){update();}
    void showFront();
    void showLeft();
    void showTop();
//    void useMatrix();

private:
    int start_x_position;//for mouse
    int start_y_position;
//    QPoint* startPoint=nullptr;
    myfigura* my_fig;
//    QMatrix4x4* matrix;
    void showSeenLines(QPainter* painter);

    QSlider* slider;
    QPushButton* bFront;
    QPushButton* bTop;
    QPushButton* bLeft;
    QCheckBox* chBox;
};

#endif // MAINWINDOW_H
