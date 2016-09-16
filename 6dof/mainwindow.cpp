
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtDebug>
#include <QtWidgets>
#include <QString>
#include <servo6dof.h>
#include <basic6dof.h>

//basic6Dof *bs6D;
Servo6Dof sv6D;

const int middleServo=97;

const QString resetNum=" 9 ";
const QString Type1="Servo";
const QString Type2="Motor";
const QString Type3="Gear Motor";

int leg1=middleServo,leg2=middleServo,leg3=middleServo,leg4=middleServo,leg5=middleServo,leg6=middleServo;
float pi=3.1415926,theta_r,theta_p,theta_s[6],RD,PD,L1,L2,z_home,servo_min,servo_max,servo_mult;
//float theta_a[6]={middleServo/180*pi,middleServo/180*pi,middleServo/180*pi,middleServo/180*pi,middleServo/180*pi,middleServo/180*pi};
float p[2][6]={{pi/6,pi/6,-pi/2,-pi/2,pi/6,pi/6},{pi/6,pi/6,-pi/2,-pi/2,pi/6,pi/6}};
float re[2][6]={{pi/6,pi/6,-pi/2,-pi/2,pi/6,pi/6},{pi/6,pi/6,-pi/2,-pi/2,pi/6,pi/6}};
float q[3][6],r[3][6],dl[3][6],dl2[6];
float sway,surge,heave,roll,pitch,yaw;
float L[6],M[6],N[6],alfa[6];

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

    MainWindow::on_comboBox_currentIndexChanged(ui->comboBox->currentText());
    MainWindow::getSetting();
    MainWindow::Caculate();
}
void MainWindow::getSetting()
{
    theta_r = ui->teTR->toPlainText().toFloat()/180*pi;
    theta_p = ui->teTP->toPlainText().toFloat()/180*pi;

    theta_s[0] = ui->TeA1Angle->toPlainText().toFloat()/180*pi;
    theta_s[1] = ui->TeA2Angle->toPlainText().toFloat()/180*pi;
    theta_s[2] = ui->TeA3Angle->toPlainText().toFloat()/180*pi;
    theta_s[3] = ui->TeA4Angle->toPlainText().toFloat()/180*pi;
    theta_s[4] = ui->TeA5Angle->toPlainText().toFloat()/180*pi;
    theta_s[5] = ui->TeA6Angle->toPlainText().toFloat()/180*pi;

    z_home=ui->teZHome->toPlainText().toFloat();
    RD=ui->teRD->toPlainText().toFloat();
    PD=ui->tePD->toPlainText().toFloat();
    L1=ui->teL1->toPlainText().toFloat();
    L2=ui->teL2->toPlainText().toFloat();

    p[0][0]=PD*cos(pi/6+theta_p);
    p[0][1]=PD*cos(pi/6-theta_p);
    p[0][2]=PD*cos(-pi/2+theta_p);
    p[0][3]=-PD*cos(-pi/2+theta_p);
    p[0][4]=-PD*cos(pi/6-theta_p);
    p[0][5]=-PD*cos(pi/6+theta_p);

    p[1][0]=PD*sin(pi/6+theta_p);
    p[1][1]=PD*sin(pi/6-theta_p);
    p[1][2]=PD*sin(-pi/2+theta_p);
    p[1][3]=PD*sin(-pi/2+theta_p);
    p[1][4]=PD*sin(pi/6-theta_p);
    p[1][5]=PD*sin(pi/6+theta_p);

    re[0][0]=RD*cos(pi/6+theta_r);
    re[0][1]=RD*cos(pi/6-theta_r);
    re[0][2]=RD*cos(-pi/2+theta_r);
    re[0][3]=-RD*cos(-pi/2+theta_r);
    re[0][4]=-RD*cos(pi/6-theta_r);
    re[0][5]=-RD*cos(pi/6+theta_r);

    re[1][0]=RD*sin(pi/6+theta_r);
    re[1][1]=RD*sin(pi/6-theta_r);
    re[1][2]=RD*sin(-pi/2+theta_r);
    re[1][3]=RD*sin(-pi/2+theta_r);
    re[1][4]=RD*sin(pi/6-theta_r);
    re[1][5]=RD*sin(pi/6+theta_r);
}

void MainWindow::Caculate()
{
    roll=ui->textEdit->toPlainText().toFloat()/180*pi;
    pitch=ui->textEdit_2->toPlainText().toFloat()/180*pi;
    yaw=ui->textEdit_3->toPlainText().toFloat()/180*pi;

    sway=ui->teX->toPlainText().toFloat();
    surge=ui->teY->toPlainText().toFloat();
    heave=ui->teZ->toPlainText().toFloat();

    for ( int i = 0; i < 6 ; i++) {
        q[0][i] =p[0][i];
        q[1][i] =p[1][i];
        q[2][i] =0;
        //q[2][i]=-L1*sin(roll);

        r[0][i] = re[0][i]*cos(roll)*cos(yaw) + re[1][i]*(sin(pitch)*sin(roll)*cos(roll)-
        cos(pitch)*sin(yaw)) + sway;
        //care for that sin(roll)*cos(roll) it may sin(roll)*cos(yaw).

        r[1][i] = re[0][i]*cos(roll)*sin(yaw) + re[1][i]*(cos(pitch)*cos(yaw) +
        sin(pitch)*sin(roll)*sin(yaw)) + surge;

        r[2][i]= -re[0][i]*sin(roll) + re[1][i]*sin(pitch)*cos(roll) + z_home + heave;

        dl[0][i] = q[0][i] - r[0][i];
        dl[1][i] = q[1][i] - r[1][i];
        dl[2][i] = q[2][i] - r[2][i];
        dl2[i] = sqrt(dl[0][i]*dl[0][i] + dl[1][i]*dl[1][i] + dl[2][i]*dl[2][i]);

        L[i] = dl2[i]*dl2[i] - (L2*L2 - L1*L1);
        M[i] = 2*L1*(r[2][i]-q[2][i]);
        N[i] = 2*L1*( cos(theta_s[i]) * (r[0][i] - p[0][i]) + sin(theta_s[i]) * (r[1][i] - p[1][i]) );

        alfa[i] = asin(L[i] / sqrt( N[i]*N[i] + M[i]*M[i] )) - atan(N[i]/M[i]);
        alfa[i] = alfa[i]*180/pi;
    }
    /*
    ui->TeA1Angle->setText(QString::number(alfa[1]));
    ui->TeA2Angle->setText(QString::number(alfa[2]));
    ui->TeA3Angle->setText(QString::number(alfa[3]));
    ui->TeA4Angle->setText(QString::number(alfa[4]));
    ui->TeA5Angle->setText(QString::number(alfa[5]));
    ui->TeA6Angle->setText(QString::number(alfa[0]));*/
    MainWindow::on_horizontalSlider_valueChanged(90+alfa[0]);
    MainWindow::on_horizontalSlider_2_valueChanged(90+alfa[1]);
    MainWindow::on_horizontalSlider_3_valueChanged(90+alfa[2]);
    MainWindow::on_horizontalSlider_4_valueChanged(90+alfa[3]);
    MainWindow::on_horizontalSlider_5_valueChanged(90+alfa[4]);
    MainWindow::on_horizontalSlider_6_valueChanged(90+alfa[5]);
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


void MainWindow::on_pushButton_clicked()// Reset Button.
{
    if ( ui->comboBox->currentText() == Type1 ) {
        MainWindow::on_horizontalSlider_valueChanged(90);
        MainWindow::on_horizontalSlider_2_valueChanged(90);
        MainWindow::on_horizontalSlider_3_valueChanged(90);
        MainWindow::on_horizontalSlider_4_valueChanged(90);
        MainWindow::on_horizontalSlider_5_valueChanged(90);
        MainWindow::on_horizontalSlider_6_valueChanged(90);
        MainWindow::on_horizontalSlider_7_valueChanged(0);
        MainWindow::on_horizontalSlider_8_valueChanged(0);
        MainWindow::on_horizontalSlider_9_valueChanged(0);
        MainWindow::on_horizontalSlider_10_valueChanged(0);
        MainWindow::on_horizontalSlider_11_valueChanged(0);
        MainWindow::on_horizontalSlider_12_valueChanged(0);
    }
}

void MainWindow::GiveStringforArduino()
{
    QString str;
    if ( ui->comboBox->currentText() == Type1 ) {
        str ="0 "+QString::number(leg1)+" "+QString::number(leg2)+" "+QString::number(leg3)+" "+QString::number(leg4)+" ";
        str +=QString::number(leg5)+" "+QString::number(leg6)+" ";
    }
    MainWindow::updateArduino(str);
}
int MainWindow::fixToRightInput(int value)
{
    if (value > 165) {
        value = 165;
    }
    if (value < 15) {
        value =15;
    }
    return value;
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    value=MainWindow::fixToRightInput(value);
    ui->textEdit_4->setText(QString::number(value));
    leg1=value;
    QString str;
    str="1 "+QString::number(leg1)+" ";
    MainWindow::updateArduino(str);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    value=MainWindow::fixToRightInput(value);
    ui->textEdit_5->setText(QString::number(value));
    leg2=value;
    QString str;
    str="2 "+QString::number(leg2)+" ";
    MainWindow::updateArduino(str);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    value=MainWindow::fixToRightInput(value);
    ui->textEdit_6->setText(QString::number(value));
    leg3=value;
    QString str;
    str="3 "+QString::number(leg3)+" ";
    MainWindow::updateArduino(str);
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    value=MainWindow::fixToRightInput(value);
    ui->textEdit_7->setText(QString::number(value));
    leg4=value;
    QString str;
    str="4 "+QString::number(leg4)+" ";
    MainWindow::updateArduino(str);
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    value=MainWindow::fixToRightInput(value);
    ui->textEdit_8->setText(QString::number(value));
    leg5=value;
    QString str;
    str="5 "+QString::number(leg5)+" ";
    MainWindow::updateArduino(str);
}

void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    value=MainWindow::fixToRightInput(value);
    ui->textEdit_9->setText(QString::number(value));
    leg6=value;
    QString str;
    str="6 "+QString::number(leg6)+" ";
    MainWindow::updateArduino(str);
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if ( arg1 == Type1 ) {
    /*    sv6D.setLegOne(ui->horizontalSlider->value());
        sv6D.setLegTwo(ui->horizontalSlider_2->value());
        sv6D.setLegThree(ui->horizontalSlider_3->value());
        sv6D.setLegFour(ui->horizontalSlider_4->value());
        sv6D.setLegFive(ui->horizontalSlider_5->value());
        sv6D.setLegSix(ui->horizontalSlider_6->value());*/
    } //else
    //MainWindow::on_pushButton_clicked();
}
void MainWindow::RPYfusion()
{
    MainWindow::Caculate();
    //MainWindow::GiveStringforArduino();
}

void MainWindow::on_horizontalSlider_9_valueChanged(int value)
{
    ui->textEdit->setText(QString::number(value));

    if ( ui->comboBox->currentText() == Type1) {
        MainWindow::RPYfusion();
    }
}

void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{

    ui->textEdit_2->setText(QString::number(value));

    if ( ui->comboBox->currentText() == Type1) {
        MainWindow::RPYfusion();
    }
}

void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{

    ui->textEdit_3->setText(QString::number(value));

    if ( ui->comboBox->currentText() == Type1) {
        MainWindow::RPYfusion();
    }
}

void MainWindow::on_horizontalSlider_10_valueChanged(int value)
{
    ui->teX->setText(QString::number(value));

    if ( ui->comboBox->currentText() == Type1) {
        MainWindow::RPYfusion();
    }
}

void MainWindow::on_horizontalSlider_11_valueChanged(int value)
{
    ui->teY->setText(QString::number(value));
    if ( ui->comboBox->currentText() == Type1) {
        MainWindow::RPYfusion();
    }
}

void MainWindow::on_horizontalSlider_12_valueChanged(int value)
{
    ui->teZ->setText(QString::number(value));
    if ( ui->comboBox->currentText() == Type1) {
        MainWindow::RPYfusion();
    }
}

void MainWindow::on_pbChangeData_clicked()
{

}

void MainWindow::on_btnSaveSetting_clicked()
{
    MainWindow::getSetting();
}

void MainWindow::on_teX_textChanged()
{
    int position;
    position=ui->teX->toPlainText().toInt();
    ui->horizontalSlider_10->setSliderPosition(position);
}

void MainWindow::on_teY_textChanged()
{
    int position;
    position=ui->teY->toPlainText().toInt();
    ui->horizontalSlider_11->setSliderPosition(position);
}

void MainWindow::on_teZ_textChanged()
{
    int position;
    position=ui->teZ->toPlainText().toInt();
    ui->horizontalSlider_12->setSliderPosition(position);
}
