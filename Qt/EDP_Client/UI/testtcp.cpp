#include "testtcp.h"
#include "ui_testtcp.h"
#include <QDebug>
TestTCP::TestTCP(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestTCP)
{
    ui->setupUi(this);
    connect(&control,SIGNAL(cmd(QString )),this,SLOT(cmd(QString)));
}

TestTCP::~TestTCP()
{
    delete ui;
}

void TestTCP::on_pushButton_clicked()
{
    bool ok = control.initConnect(ui->lineEdit_port->text().toShort());

    ui->textEdit->append(QString("端口%1监听%2！").arg(ui->lineEdit_port->text().toShort()).arg(ok?"成功":"失败"));
}

void TestTCP::on_pushButton_stop_connect_clicked()
{
    ui->textEdit->append("停止监听！");
    control.closeListen();
}

void TestTCP::Feedback(int value, bool speed)
{
    if(speed){
        ui->lineEdit_feed_speed->setText(QString("%1").arg(value));
    }else{
        ui->lineEdit_feed_va->setText(QString("%1").arg(value));
    }
}

void TestTCP::ADFeedback(short data1, short data2, int data3)
{
    ui->lineEdit_ad_Data1->setText(QString("%1").arg(data1));
    ui->lineEdit_ad_data2->setText(QString("%1").arg(data2));
    ui->lineEdit_ad_data3->setText(QString("%1").arg(data3));
}


void TestTCP::on_pushButton_start_clicked()
{
    control.TurnOnOff(ui->lineEdit_addr->text().toShort(),true);
}

void TestTCP::on_pushButton_stop_clicked()
{
    control.TurnOnOff(ui->lineEdit_addr->text().toShort(),false);
}

void TestTCP::on_pushButton_set_pos_clicked()
{
    control.SetParam(ui->lineEdit_addr->text().toShort(),ui->lineEdit_value->text().toInt(),false);
}

void TestTCP::on_pushButton_set_speed_clicked()
{
    control.SetParam(ui->lineEdit_addr->text().toShort(),ui->lineEdit_value->text().toInt(),true);
}


void TestTCP::on_pushButton_query_speed_clicked()
{
    control.QueryParam(ui->lineEdit_addr->text().toShort(),true);
}

void TestTCP::cmd(QString c)
{
    ui->textEdit->append(c);
}


void TestTCP::on_pushButton_query_va_clicked()
{
    control.QueryParam(ui->lineEdit_addr->text().toShort(),false);
}


void TestTCP::on_pushButton_start_Ad_clicked()
{
    control.TurnOnOffAD(true);
}

void TestTCP::on_pushButton_stop_ad_clicked()
{
    control.TurnOnOffAD(false);
}


