
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtDebug>
#include <QtWidgets>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;


    qDebug() << " Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()) {
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()) {
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }

   foreach(const QSerialPortInfo &serialPortInfo,QSerialPortInfo::availablePorts()) {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
            if (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id) {
                if (serialPortInfo.productIdentifier() == arduino_uno_product_id) {
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;
                }
            }
        }
    }

    if (arduino_is_available) {
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud115200);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        //arduino->open(QIODevice::ReadWrite);

    } else {
        QMessageBox::warning(this," Port error", "Couldn't find the Arduino");
    }
    QString t;

    ui->textEdit_3->setText(t.setNum(ui->horizontalSlider->value()));
}
void MainWindow::updateArduino(QString command)
{
    if (arduino->isWritable()) {
        arduino->write(command.toStdString().c_str());
    } else {
        qDebug() << "Couldn't write to serial";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_textEdit_4_textChanged()
{
    int position;
    position=ui->textEdit_4->toPlainText().toInt();
    ui->horizontalSlider->setSliderPosition(position);
}

void MainWindow::on_textEdit_5_textChanged()
{
    int position;
    position=ui->textEdit_5->toPlainText().toInt();
    ui->horizontalSlider_2->setSliderPosition(position);
}

void MainWindow::on_textEdit_6_textChanged()
{
    int position;
    position=ui->textEdit_6->toPlainText().toInt();
    ui->horizontalSlider_3->setSliderPosition(position);
}

void MainWindow::on_textEdit_7_textChanged()
{
    int position;
    position=ui->textEdit_7->toPlainText().toInt();
    ui->horizontalSlider_4->setSliderPosition(position);
}

void MainWindow::on_textEdit_8_textChanged()
{
    int position;
    position=ui->textEdit_8->toPlainText().toInt();
    ui->horizontalSlider_5->setSliderPosition(position);
}

void MainWindow::on_textEdit_9_textChanged()
{
    int position;
    position=ui->textEdit_9->toPlainText().toInt();
    ui->horizontalSlider_6->setSliderPosition(position);
}

void MainWindow::on_horizontalSlider_9_sliderMoved(int position)
{
    QString str;
    str.setNum(position);
    ui->textEdit->setText(str);
}

void MainWindow::on_horizontalSlider_8_sliderMoved(int position)
{
    QString str;
    str.setNum(position);
    ui->textEdit_2->setText(str);
}

void MainWindow::on_horizontalSlider_7_sliderMoved(int position)
{
    QString str;
    str.setNum(position);
    ui->textEdit_3->setText(str);
}

void MainWindow::on_textEdit_textChanged()
{
    int position;
    position=ui->textEdit->toPlainText().toInt();
    ui->horizontalSlider_9->setSliderPosition(position);
}

void MainWindow::on_textEdit_2_textChanged()
{
    int position;
    position=ui->textEdit_2->toPlainText().toInt();
    ui->horizontalSlider_8->setSliderPosition(position);
}

void MainWindow::on_textEdit_3_textChanged()
{
    int position;
    position=ui->textEdit_3->toPlainText().toInt();
    ui->horizontalSlider_7->setSliderPosition(position);
}

void MainWindow::on_horizontalSlider_rangeChanged(int min, int max)
{

}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit_4->setText("90");
    ui->textEdit_5->setText("90");
    ui->textEdit_6->setText("90");
    ui->textEdit_7->setText("90");
    ui->textEdit_8->setText("90");
    ui->textEdit_9->setText("90");
    ui->horizontalSlider->setValue(90);
    ui->horizontalSlider_2->setValue(90);
    ui->horizontalSlider_3->setValue(90);
    ui->horizontalSlider_4->setValue(90);
    ui->horizontalSlider_5->setValue(90);
    ui->horizontalSlider_6->setValue(90);
    MainWindow::updateArduino(" 9 ");
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QString str;
    str.setNum(value);
    ui->textEdit_4->setText(str);
    MainWindow::updateArduino("1 "+str+" ");
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    QString str;
    str.setNum(value);
    ui->textEdit_5->setText(str);
    MainWindow::updateArduino("2 "+str+" ");
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    QString str;
    str.setNum(value);
    ui->textEdit_6->setText(str);
    MainWindow::updateArduino("3 "+str+" ");
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    QString str;
    str.setNum(value);
    ui->textEdit_7->setText(str);
    MainWindow::updateArduino("4 "+str+" ");
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    QString str;
    str.setNum(value);
    ui->textEdit_8->setText(str);
    MainWindow::updateArduino("5 "+str+" ");
}

void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    QString str;
    str.setNum(value);
    ui->textEdit_9->setText(str);
    MainWindow::updateArduino("6 "+str+" ");
}
