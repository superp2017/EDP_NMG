#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QWidget>
#include <QShowEvent>
#pragma execution_character_set("utf-8")

namespace Ui {
class FormLogin;
}
#pragma execution_character_set("utf-8")
class FormLogin : public QWidget
{
    Q_OBJECT

public:
    explicit FormLogin(QWidget *parent = 0);
    ~FormLogin();

signals:
    void gotoForm(int index);
private slots:
    void on_pushButton_clicked();
private:
    bool do_login(QString acc,QString pwd);
    Ui::FormLogin *ui;
};

#endif // FORMLOGIN_H
