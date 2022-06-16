#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QtWidgets>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

//    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
//    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
//        qDebug() << "Has vendor ID: "<< serialPortInfo.hasVendorIdentifier();
//        if(serialPortInfo.hasVendorIdentifier()){
//            QDebug() << "Vendor ID: "<< serialPortInfo.vendorIdentifier();
//        }
//        qDebug() << "Has Product ID: "<< serialPortInfo.hasProductIdentifier();
//        if(serialPortInfo.hasProductIdentifier()){
//            QDebug() << "Product ID: "<< serialPortInfo.ProductIdentifier();
//        }
//    }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
            if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                arduino_port_name = serialPortInfo.portName();
                arduino_is_available = true;
                qDebug() <<"Arduino /dev/ttyACM0 is connected."<<endl;
            }
        }
    }

    if(arduino_is_available){
        // open and configure the port
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }
    else{
        // give error message
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino!");
    }
}

Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}


void Dialog::on_FestoABar_valueChanged(int value)
{
    ui->a_value_label->setText(QString(
        "<span style=\" font-size:16pt; font-weight:700;\">%1</span>").arg(value));
    //convert pressure 0~2000 to arduino digitalWrite() 0~255
    int onboard_value = floor((value * 0.1125) + 30);
    Dialog::updateFESTO(QString("a%1").arg(onboard_value)); //format from arduino
    qDebug() << "Regulating pressure "<<value<<"/2000 mbar..."
             <<"Setpoint is "<<onboard_value<<"/255..."<<endl;
}

void Dialog::on_FestoBBar_valueChanged(int value)
{
    //
}

void Dialog::on_FestoCBar_valueChanged(int value)
{
    //
}

void Dialog::on_cycle_valueChanged(int low_val, int high_val, int period)
{
    //from low_val to high_val: run

}

void Dialog::updateFESTO(QString command){
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
    }
    else{
        qDebug() << "Couldn't write this serial!";
    }
}
