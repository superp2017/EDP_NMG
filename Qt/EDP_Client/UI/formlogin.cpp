#include "formlogin.h"
#include "ui_formlogin.h"
#include <QDebug>
#include "datacenter.h"
#include <QMessageBox>
#include <QToolTip>
FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
{
    ui->setupUi(this);

    ui->n_useNameLine->setPlaceholderText("用户名");
    ui->n_usePwdLine->setPlaceholderText("密码");
    ui->n_usePwdLine->setEchoMode(QLineEdit::Password);

    ui->pushButton->setStyleSheet("QPushButton{border-image: url(:/icon/login_before.png);}"
                                  "QPushButton:hover{border-image: url(:/icon/login_after.png);}"
                                  "QPushButton:pressed{border-image: url(:/icon/login_after.png);}"
                                  "QPushButton:checked{border-image: url(:/icon/login_after.png);}");

    ui->label_title->setPixmap(QPixmap(":/icon/login_title.png"));

    ui->widget->setStyleSheet("#widget{border-image: url(:/icon/login_frame.png);}");
//    ui->widget->setStyleSheet("#widget{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");

}

FormLogin::~FormLogin()
{
    delete ui;
}


void FormLogin::on_pushButton_clicked()
{

//    QString useName = ui->n_useNameLine->text();
//    QString usePwd = ui->n_usePwdLine->text();
//    if(useName == "") {
//        QToolTip::showText(ui->n_useNameLine->mapToGlobal(QPoint(100, 0)), "用户名输入有误");
//        return;
//    }
//    if(usePwd == ""){
//        QToolTip::showText(ui->n_usePwdLine->mapToGlobal(QPoint(100, 0)), "密码输入有误");
//        return;
//    }

//    if(!dataCenter::instance()->OpenSQL()){
//        QMessageBox::warning(this,"提示","数据库连接失败!");
//        return ;
//    }

//    int index=dataCenter::instance()->Login(useName,usePwd);
//    if(index==-1){
//        return ;
//    }
//    if (index==1){
//        QToolTip::showText(ui->n_useNameLine->mapToGlobal(QPoint(100, 0)), "获取账户信息失败");
//        return;
//    }
//    if (index==2){
//        QToolTip::showText(ui->n_usePwdLine->mapToGlobal(QPoint(100, 0)), "密码验证失败");
//        return;
//    }
    emit   gotoForm(1);
}
