#ifndef UTILS_H
#define UTILS_H

#include <QWidget>
#include <matrixmanager.h>

namespace Ui {
class Utils;
}

class Utils : public QWidget
{
    Q_OBJECT

public:
    explicit Utils(QWidget *parent = 0);
    ~Utils();
signals:
    void sendMatrix(QMatrix4x4 m);
public slots:
    void checkRotate();
    void checkMove();
    void checkScale();
    void checkAxa();
    void checkKosa();
    void checkPerspeck();
    void checkView();

private:
    QMatrix4x4* matr;
    Ui::Utils *ui;
};

#endif // UTILS_H
