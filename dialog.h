#ifndef DIALOG_H
#define DIALOG_H

#include "qserialport.h"
#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_FestoABar_valueChanged(int value);

    void on_FestoBBar_valueChanged(int value);

    void on_FestoCBar_valueChanged(int value);

    void on_cycle_valueChanged(int low_val, int high_val, int period);

    void updateFESTO(QString);

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;
};
#endif // DIALOG_H
