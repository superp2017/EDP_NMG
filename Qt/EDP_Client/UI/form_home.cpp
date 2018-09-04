#include "form_home.h"
#include "ui_form_home.h"

Form_home::Form_home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_home)
{
    ui->setupUi(this);

    ui->pushButton_sport->setStyleSheet("QPushButton{border-image: url(:/icon/sport.png);}");
    ui->pushButton_data_collect->setStyleSheet("QPushButton{border-image: url(:/icon/datacollect.png);}");
    ui->pushButton_cloud->setStyleSheet("QPushButton{border-image: url(:/icon/cloud.png);}");
    ui->pushButton_communication->setStyleSheet("QPushButton{border-image: url(:/icon/communication.png);}");
    ui->label_home_title->setPixmap(QPixmap(":/icon/home_title.png"));
}

Form_home::~Form_home()
{
    delete ui;
}

void Form_home::on_pushButton_sport_clicked()
{
    emit gotoForm(2);
}

void Form_home::on_pushButton_data_collect_clicked()
{
    emit gotoForm(3);
}

void Form_home::on_pushButton_cloud_clicked()
{
    emit gotoForm(4);
}

void Form_home::on_pushButton_communication_clicked()
{
    emit gotoForm(5);
}

