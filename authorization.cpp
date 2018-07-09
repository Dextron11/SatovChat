#include "authorization.h"
#include "ui_authorization.h"
Authorization::Authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);

}

Authorization::~Authorization()
{
    delete ui;
}

QString Authorization::getUserName(){
    return _user_name;
}
QString Authorization::getIpServer(){
    return _ip_server;
}

void Authorization::on_pushButton_Join_clicked()
{
   if((ui->lineEdit_User->text()).isEmpty()||(ui->lineEdit_Ip->text()).isEmpty()){
        ui->label_error->setText("The username or password is missing!");
    }
    else {
        _ip_server=ui->lineEdit_Ip->text();
        _user_name=ui->lineEdit_User->text();
        this->accept();
    }
}
