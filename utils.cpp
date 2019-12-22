#include "utils.h"
#include "ui_utils.h"

Utils::Utils(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Utils)
{
    ui->setupUi(this);

}



void Utils::checkRotate(){
    matr=MatrixManager::getRotateMatrix(
                ui->spinPovorotX->value(),
                ui->spinPovorotY->value(),
                ui->spinPovorotZ->value());
    qDebug()<<"to send"<<(*matr);
    emit sendMatrix(*matr);
}
void Utils::checkMove(){
    matr=MatrixManager::getMoveMatrix(
                ui->spinMoveX->value(),
                -1*ui->spinMoveY->value(),
                ui->spinMoveZ->value());
    qDebug()<<"to send"<<(*matr);
    emit sendMatrix(*matr);
}
void Utils::checkScale(){
    matr=MatrixManager::getScaleMatrix(
                ui->spinScaleX->value(),
                ui->spinScaleY->value(),
                ui->spinScaleZ->value());
    qDebug()<<"to send"<<(*matr);
    emit sendMatrix(*matr);
}
void Utils::checkAxa(){
    matr=MatrixManager::getAxonometricMatrix(
                ui->spinAxaX->value(),
                ui->spinAxaY->value(),
                ui->spinAxaZ->value());
    qDebug()<<"to send"<<(*matr);
    emit sendMatrix(*matr);
}
void Utils::checkKosa(){
    matr=MatrixManager::getObliqueMatrix(
                ui->spinKL->value(),
                ui->spinKA->value());
    qDebug()<<"to send"<<(*matr);
    emit sendMatrix(*matr);
}
void Utils::checkPerspeck(){
            matr=MatrixManager::getPerspectiveMatrix(
                        ui->doubleSpinBoxD->value(),
                        ui->spinPPCount->value());
            qDebug()<<"to send"<<(*matr);
            emit sendMatrix(*matr);
}
void Utils::checkView(){
            matr=MatrixManager::getViewTransformationMatrix(
                        ui->spinViewR->value(),
                        ui->spinViewF->value(),
                        ui->spinViewT->value(),
                        ui->radioButtonView->isChecked());
            qDebug()<<"to send"<<(*matr);
            emit sendMatrix(*matr);
}
Utils::~Utils()
{
    delete ui;
}
