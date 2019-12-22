#ifndef UTILS_H
#define UTILS_H

#include <QWidget>

namespace Ui {
class Utils;
}

class Utils : public QWidget
{
    Q_OBJECT

public:
    explicit Utils(QWidget *parent = 0);
    ~Utils();

private:
    Ui::Utils *ui;
};

#endif // UTILS_H
