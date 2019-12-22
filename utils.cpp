#include "utils.h"
#include "ui_utils.h"

Utils::Utils(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Utils)
{
    ui->setupUi(this);
}

Utils::~Utils()
{
    delete ui;
}
