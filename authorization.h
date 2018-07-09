#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>

namespace Ui {
class Authorization;
}

class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = 0);

    QString getUserName();

    QString getIpServer();

    ~Authorization();

private slots:
    void on_pushButton_Join_clicked();

private:
    Ui::Authorization *ui;

    QString _user_name;

    QString _ip_server;

};

#endif // AUTHORIZATION_H
