#include "formcenter.h"
#include "ui_formcenter.h"
#include <QDebug>
#include "datacenter.h"
FormCenter::FormCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCenter)
{
    ui->setupUi(this);
    ui->pushButton_exit->setStyleSheet("QPushButton{border-image: url(:/icon/exit.png);}"
                                       "QPushButton:hover{border-image: url(:/icon/exit_down.png);}"
                                       "QPushButton:pressed{border-image: url(:/icon/exit_down.png);}"
                                       "QPushButton:checked{border-image: url(:/icon/exit_down.png);}");
    ui->pushButton_return->setStyleSheet("QPushButton{border-image: url(:/icon/return.png);}"
                                         "QPushButton:hover{border-image: url(:/icon/return_down.png);}"
                                         "QPushButton:pressed{border-image: url(:/icon/return_down.png);}"
                                         "QPushButton:checked{border-image: url(:/icon/return_down.png);}");
    ui->pushButton_mini->setStyleSheet("QPushButton{border-image: url(:/icon/mini.png);}"
                                       "QPushButton:hover{border-image: url(:/icon/mini_down.png);}"
                                       "QPushButton:pressed{border-image: url(:/icon/mini_down.png);}"
                                       "QPushButton:checked{border-image: url(:/icon/mini_down.png);}");
    ui->pushButton_setting->setStyleSheet("QPushButton{border-image: url(:/icon/setting.png);}"
                                          "QPushButton:hover{border-image: url(:/icon/setting_down.png);}"
                                          "QPushButton:pressed{border-image: url(:/icon/setting_down.png);}"
                                          "QPushButton:checked{border-image: url(:/icon/setting_down.png);}");

    ui->stackedWidget->addWidget(&login);
    ui->stackedWidget->addWidget(&home);
    ui->stackedWidget->addWidget(&move);
    ui->stackedWidget->addWidget(&collect);
    ui->stackedWidget->addWidget(&colud);
    ui->stackedWidget->addWidget(&commutication);
    ui->stackedWidget->addWidget(&m_setting);

    connect(&home,SIGNAL(gotoForm(int)),this,SLOT(setCurIndex(int)));
    connect(&login,SIGNAL(gotoForm(int)),this,SLOT(setCurIndex(int)));
    setCurIndex(0);
    m_last_index = -1;
    checkTable();
}

FormCenter::~FormCenter()
{
    delete ui;
}

void FormCenter::on_pushButton_return_clicked()
{
    if(ui->stackedWidget->currentIndex()==6){
        if(m_last_index==0)
            setCurIndex(0);
        else if(m_last_index>=0&&m_last_index<ui->stackedWidget->count())
            setCurIndex(m_last_index);
    }else{
        setCurIndex(1);
    }
}

void FormCenter::setCurIndex(int index)
{
    if(index==-1) return;
    if(ui->pushButton_return->isHidden())
        ui->pushButton_return->show();
    if(ui->pushButton_setting->isHidden())
        ui->pushButton_setting->show();
    if(index==0){
        if(!ui->pushButton_return->isHidden())
            ui->pushButton_return->hide();
    }
    if(index==1){
        if(!ui->pushButton_return->isHidden())
            ui->pushButton_return->hide();
    }
    if(index==6){
        if(!ui->pushButton_setting->isHidden())
            ui->pushButton_setting->hide();
    }
    if(ui->stackedWidget->currentIndex() == index){
        return;
    }
    if(index<0||index>=ui->stackedWidget->count()){
        return ;
    }
    m_last_index = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(index);
}

void FormCenter::checkTable()
{
    bool save = false;

    TableCreat c= dataCenter::instance()->getTableCreat();

    if(!c.IsAccount){
        dataCenter::instance()->CreatAccountTable();
        c.IsAccount = true;
        dataCenter::instance()->setTableCreat(c);
    }

    if(!c.IsCollectData){
        dataCenter::instance()->CreatCollectDataTable();
        c.IsCollectData = true;
        save = true;
    }
    if(!c.IsCollectParm){
        dataCenter::instance()->CreatCollectParamTable();
        c.IsCollectParm = true;
        save = true;
    }
    if(save)
        dataCenter::instance()->setTableCreat(c);
}



void FormCenter::on_pushButton_setting_clicked()
{
    setCurIndex(6);
}

void FormCenter::on_pushButton_mini_clicked()
{
    emit miniWindow();
}

void FormCenter::on_pushButton_exit_clicked()
{
    emit systemExit();
}

