#include "register.h"
#include "ui_register.h"

Register::Register(QString x_IP, uint16_t x_port, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register),con_IP(x_IP),con_port(x_port)
{
    ui->setupUi(this);
    cl = new chatClient(REGISTER,this);

    ui->password->setEchoMode(QLineEdit::Password);
    ui->password_confirm->setEchoMode(QLineEdit::Password);

    connect(cl,SIGNAL(regwindow_issuccess(const QString&)),this,SLOT(display_issuccess(const QString&)));
    connect(ui->Return,SIGNAL(clicked()),this,SLOT(close()));

    setWindowTitle("Register");
}

Register::~Register()
{
    delete ui;
    if(cl != nullptr){
        delete cl;
    }
}

void Register::on_Confirm_clicked()
{
    //这里判断的时候真的是有点傻。如果在判断失误之后能继续输入就好了
    if( ui->user_name->text().isEmpty() )
    {
        QMessageBox::warning(this, tr("Warning"), tr("User name cannot be empty"));
        return;
    }else if(ui->password->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Password cannot be empty"));
        return;
    }else if(ui->password->text().isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Please confirm your password"));
        return;
    }
    //name
    //TODO:warning of the form of the name,the same name.
    QString user_name = ui->user_name->text();
    //password
    QString passw_hash = QCryptographicHash::hash( ui->password->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    QString passwcon_hash = QCryptographicHash::hash( ui->password_confirm->text().toUtf8(),
                                                      QCryptographicHash::Sha3_256 );
    if(passw_hash != passwcon_hash){
        QMessageBox::warning(this, tr("Warning"), tr("Entered passwords differ"));
        return;
    }
    //Encode
    QString tosend = "RG" + user_name +" "+ passwcon_hash;
    //connect
    cl->connectToServer(con_IP, con_port);
    cl->sendMessage(tosend);
    return;
}

void Register::display_issuccess(const QString& s){
    if(s == "Success"){
        QMessageBox::about(this,"Message from server","You have successfully registered! ");
        cl->disconnect();
        emit ui->Return->clicked();
    }
}
