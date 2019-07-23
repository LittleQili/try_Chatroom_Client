#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
#include "client.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QString x_IP,uint16_t x_port,QWidget *parent = 0);
    ~Register();

private slots:
    void on_Confirm_clicked();
    void display_issuccess(const QString&);
private:
    Ui::Register *ui;
    chatClient *cl;
    QString con_IP;
    uint16_t con_port;
};

#endif // REGISTER_H
