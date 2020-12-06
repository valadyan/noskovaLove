#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include <QPushButton>
#include <QSlider>
#include <QCheckBox>

#include <myfigura.h>
#include <utils.h>

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
signals:
    void update_signal();
public slots:
    void aprok_change_slot(int a);
    void update_slot(){update();}
    void useMatrix(QMatrix4x4 m);
    void animate();

private:
    int start_x_position;//for mouse
    int start_y_position;
//    QPoint* startPoint=nullptr;
    myfigura* my_fig;
    QMatrix4x4* eyeMatrix;//=MatrixManager::getRotateM(45,45,45);
    void showSeenLines(QPainter* painter);

    QSlider* slider;
    QCheckBox* chBox;
    QCheckBox* animationChBox;

    QTimer *animationTimer;

    Utils* utils;

    int R1,R2,h,aprox;
};

#endif // MAINWINDOW_H
