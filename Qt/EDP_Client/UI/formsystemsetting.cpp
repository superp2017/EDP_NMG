#include "formsystemsetting.h"
#include "ui_formsystemsetting.h"
#include "datacenter.h"
#include <QMessageBox>
#include <QToolTip>
#include "global.h"

FormSystemSetting::FormSystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSystemSetting)
{
    ui->setupUi(this);
    ui->lineEdit_db_name->setText(dataCenter::instance()->getDBConfig().server_DB);
    ui->lineEdit_ip->setText(dataCenter::instance()->getDBConfig().server_ip);
    ui->lineEdit_passwd->setText(dataCenter::instance()->getDBConfig().server_passwd);
    ui->lineEdit_port->setText(dataCenter::instance()->getDBConfig().server_port);
    ui->lineEdit_username->setText(dataCenter::instance()->getDBConfig().server_username);
    ui->label__title->setPixmap(QPixmap(":/icon/db_title.png"));

    ui->pushButton_close->setStyleSheet("QPushButton{border-image: url(:/icon/close_connect.png);}"
                                         "QPushButton:hover{border-image: url(:/icon/close_connect_down.png);}"
                                         "QPushButton:pressed{border-image: url(:/icon/close_connect_down.png);}"
                                         "QPushButton:checked{border-image: url(:/icon/close_connect_down.png);}");
    ui->pushButton_connect->setStyleSheet("QPushButton{border-image: url(:/icon/re_connect.png);}"
                                          "QPushButton:hover{border-image: url(:/icon/re_connect_down.png);}"
                                          "QPushButton:pressed{border-image: url(:/icon/re_connect_down.png);}"
                                          "QPushButton:checked{border-image: url(:/icon/re_connect_down.png);}");
    ui->pushButton_mod->setStyleSheet("QPushButton{border-image: url(:/icon/modify_config.png);}"
                                      "QPushButton:hover{border-image: url(:/icon/modify_config_down.png);}"
                                      "QPushButton:pressed{border-image: url(:/icon/modify_config_down.png);}"
                                      "QPushButton:checked{border-image: url(:/icon/modify_config_down.png);}");

    ui->widget->setStyleSheet("#widget{border-image: url(:/icon/move_left_back.png);}");
//    ui->widget->setStyleSheet("#widget{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");

}

FormSystemSetting::~FormSystemSetting()
{
    delete ui;
}


void FormSystemSetting::on_pushButton_mod_clicked()
{
    QString db= ui->lineEdit_db_name->text().trimmed();
    QString ip= ui->lineEdit_ip->text().trimmed();
    QString psswd= ui->lineEdit_passwd->text().trimmed();
    QString port= ui->lineEdit_port->text().trimmed();
    QString username= ui->lineEdit_username->text().trimmed();

    if(ip.isEmpty()){
        QToolTip::showText(ui->lineEdit_ip->mapToGlobal(QPoint(100, 0)), "数据库ip不能为空！");
        return;
    }
    if(port.isEmpty()){
        QToolTip::showText(ui->lineEdit_port->mapToGlobal(QPoint(100, 0)), "数据库端口不能为空！");
        return;
    }
    if(username.isEmpty()){
        QToolTip::showText(ui->lineEdit_username->mapToGlobal(QPoint(100, 0)), "用户名不能为空！");
        return;
    }
    if(psswd.isEmpty()){
        QToolTip::showText(ui->lineEdit_passwd->mapToGlobal(QPoint(100, 0)), "登录密码不能为空！");
        return;
    }
    if(db.isEmpty()){
        QToolTip::showText(ui->lineEdit_db_name->mapToGlobal(QPoint(100, 0)), "数据库名称不能为空！");
        return;
    }
    DB_Config config;
    config.server_DB        = db;
    config.server_username  = username;
    config.server_passwd    = psswd;
    config.server_ip        = ip;
    config.server_port      =  port ;

    dataCenter::instance()->setDBConfig(config);

}

void FormSystemSetting::on_pushButton_connect_clicked()
{
    on_pushButton_mod_clicked();
    if(dataCenter::instance()->OpenSQL()){
        QMessageBox::information(this,"提示","连接成功!");
    }else{
        QMessageBox::information(this,"提示","连接失败!");
    }
}


void FormSystemSetting::on_pushButton_close_clicked()
{
        dataCenter::instance()->CloseSQL();
}
