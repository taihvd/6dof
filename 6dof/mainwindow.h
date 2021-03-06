#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void updateArduino(QString command);

    void on_textEdit_4_textChanged();

    void on_textEdit_5_textChanged();

    void on_textEdit_6_textChanged();

    void on_textEdit_7_textChanged();

    void on_textEdit_8_textChanged();

    void on_textEdit_9_textChanged();

    void on_textEdit_textChanged();

    void on_textEdit_2_textChanged();

    void on_textEdit_3_textChanged();

    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_5_valueChanged(int value);

    void on_horizontalSlider_6_valueChanged(int value);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void GiveStringforArduino();

    void on_horizontalSlider_9_valueChanged(int value);

    void on_horizontalSlider_8_valueChanged(int value);

    void on_horizontalSlider_7_valueChanged(int value);

    void RPYfusion();

    void on_horizontalSlider_10_valueChanged(int value);

    void on_horizontalSlider_11_valueChanged(int value);

    void on_horizontalSlider_12_valueChanged(int value);

    void on_pbChangeData_clicked();

    void Caculate();

    void getSetting();

    void on_btnSaveSetting_clicked();

    void on_teX_textChanged();

    void on_teY_textChanged();

    void on_teZ_textChanged();

    int fixToRightInput(int value);

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 68;
    QString arduino_port_name;
    bool arduino_is_available;

};

#endif // MAINWINDOW_H
