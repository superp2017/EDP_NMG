#include "formcommunicationsystem.h"
#include "ui_formcommunicationsystem.h"
#include <QtSerialPort/QSerialPort>
#include <QIntValidator>
#include "datacenter.h"
#include <QToolTip>
#include <QMessageBox>

FormCommunicationSystem::FormCommunicationSystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCommunicationSystem)
{
    ui->setupUi(this);

    ui->label_title->setPixmap(QPixmap(":/icon/communication_title.png"));
    ui->label_netport_title->setPixmap(QPixmap(":/icon/port_title.png"));

     ui->widget->setStyleSheet("#widget{border-image: url(:/icon/cloud_left_back.png);}");


//    ui->widget->setStyleSheet("#widget{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");


    ui->pushButton_bus_ok->setStyleSheet("QPushButton{border-image: url(:/icon/communication_confirm.png);}"
                                         "QPushButton:hover{border-image: url(:/icon/communication_confirm_down.png);}"
                                         "QPushButton:pressed{border-image: url(:/icon/communication_confirm_down.png);}"
                                         "QPushButton:checked{border-image: url(:/icon/communication_confirm_down.png);}");

    ui->pushButton_dev_ok->setStyleSheet("QPushButton{border-image: url(:/icon/communication_confirm.png);}"
                                         "QPushButton:hover{border-image: url(:/icon/communication_confirm_down.png);}"
                                         "QPushButton:pressed{border-image: url(:/icon/communication_confirm_down.png);}"
                                         "QPushButton:checked{border-image: url(:/icon/communication_confirm_down.png);}");


    QIntValidator *port = new QIntValidator(0,20000,this);
    ui->lineEdit_prot->setValidator(port);
    QRegExp rx("((2[0-4]//d|25[0-5]|[01]?//d//d?)//.){3}(2[0-4]//d|25[0-5]|[01]?//d//d?)");
    QRegExpValidator *validator = new QRegExpValidator(rx, this);
    ui->lineEdit_ip->setValidator(validator);

    initCOM();
    initConfig();
}


void FormCommunicationSystem::initCOM()
{
    ui->comboBox_data->addItem("5位",5);
    ui->comboBox_data->addItem("6位",6);
    ui->comboBox_data->addItem("7位",7);
    ui->comboBox_data->addItem("8位",8);
    ui->comboBox_Baud_rate->addItem("1200",1200);
    ui->comboBox_Baud_rate->addItem("2400",2400);
    ui->comboBox_Baud_rate->addItem("4800",4800);
    ui->comboBox_Baud_rate->addItem("9600",9600);
    ui->comboBox_Baud_rate->addItem("19200",19200);
    ui->comboBox_Baud_rate->addItem("38400",38400);
    ui->comboBox_Baud_rate->addItem("57600",57600);
    ui->comboBox_Baud_rate->addItem("115200",115200);
    ui->comboBox_stop->addItem("1位",1);
    ui->comboBox_stop->addItem("1.5位",3);
    ui->comboBox_stop->addItem("2位",2);
    ui->comboBox_check->addItem("无校验",0);
    ui->comboBox_check->addItem("偶校验",2);
    ui->comboBox_check->addItem("奇校验",3);
    ui->comboBox_com->addItem("COM0");
    ui->comboBox_com->addItem("COM1");
    ui->comboBox_com->addItem("COM2");
    ui->comboBox_com->addItem("COM3");
    ui->comboBox_com->addItem("COM4");
    ui->comboBox_com->addItem("COM5");
    ui->comboBox_com->addItem("COM6");
    ui->comboBox_com->addItem("COM7");
    ui->comboBox_com->addItem("COM8");
    ui->comboBox_com->addItem("COM9");
}

void FormCommunicationSystem::initConfig()
{
    config = dataCenter::instance()->getCommunitConfig();
    ui->lineEdit_ip->setText(config.dev.IP);
    ui->lineEdit_prot->setText(config.dev.Port);
    ui->comboBox_com->setCurrentText(config.serial.com);
    ui->comboBox_check->setCurrentText(config.serial.check);
    ui->comboBox_Baud_rate->setCurrentText(config.serial.rate);
    ui->comboBox_data->setCurrentText(config.serial.bits);
    ui->comboBox_stop->setCurrentText(config.serial.stop);
}


FormCommunicationSystem::~FormCommunicationSystem()
{
    delete ui;
}



void FormCommunicationSystem::on_pushButton_dev_ok_clicked()
{
    QString ip = ui->lineEdit_ip->text().trimmed();
    QString port = ui->lineEdit_prot->text().trimmed();
    if(ip.isEmpty()){
        QToolTip::showText(ui->lineEdit_ip->mapToGlobal(QPoint(100, 0)), "IP填写不正确！");
        return;
    }
    if(port.isEmpty()){
        QToolTip::showText(ui->lineEdit_prot->mapToGlobal(QPoint(100, 0)), "端口填写不正确");
        return;
    }
    config.dev.IP = ip;
    config.dev.Port = port;
    dataCenter::instance()->setCommunitConfig(config);
    QMessageBox::information(this,"提示","更新成功");
}

void FormCommunicationSystem::on_pushButton_bus_ok_clicked()
{
    config.serial.com  =ui->comboBox_com->currentText();
    config.serial.bits = ui->comboBox_data->currentText();
    config.serial.stop = ui->comboBox_stop->currentText();
    config.serial.rate = ui->comboBox_Baud_rate->currentText();
    config.serial.check = ui->comboBox_check->currentText();
    dataCenter::instance()->setCommunitConfig(config);
    QMessageBox::information(this,"提示","更新成功");
}


