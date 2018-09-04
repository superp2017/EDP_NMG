#include "formcloudcontrol.h"
#include "ui_formcloudcontrol.h"
#include <QFileDialog>

FormCloudControl::FormCloudControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCloudControl)
{
    ui->setupUi(this);

    ui->label_cloud_title->setPixmap(QPixmap(":/icon/cloud_title.png"));

    ui->label_learn_title->setPixmap(QPixmap(":/icon/learn_title.png"));

    ui->label_control_title->setPixmap(QPixmap(":/icon/control_title.png"));

    ui->widget_left->setStyleSheet("#widget_left{border-image: url(:/icon/cloud_left_back.png);}");
    ui->widget_right->setStyleSheet("#widget_right{border-image: url(:/icon/cloud_right_back.png);}");

//    ui->widget_left->setStyleSheet("#widget_left{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");
//    ui->widget_right->setStyleSheet("#widget_right{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");




    ui->pushButton_ok->setStyleSheet("QPushButton{border-image: url(:/icon/cloud_ok.png);}"
                                     "QPushButton:hover{border-image: url(:/icon/cloud_ok_down.png);}"
                                     "QPushButton:pressed{border-image: url(:/icon/cloud_ok_down.png);}"
                                     "QPushButton:checked{border-image: url(:/icon/cloud_ok_down.png);}");
    ui->pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/cloud_cancel.png);}"
                                         "QPushButton:hover{border-image: url(:/icon/cloud_cancel_down.png);}"
                                         "QPushButton:pressed{border-image: url(:/icon/cloud_cancel_down.png);}"
                                         "QPushButton:checked{border-image: url(:/icon/cloud_cancel_down.png);}");


    m_light_Status.append(LightStatus{ui->pushButton_light_1,ui->label_status_1,true});
    m_light_Status.append(LightStatus{ui->pushButton_light_2,ui->label_status_2,true});
    m_light_Status.append(LightStatus{ui->pushButton_light_3,ui->label_status_3,false});
    m_light_Status.append(LightStatus{ui->pushButton_light_4,ui->label_status_4,true});
    m_light_Status.append(LightStatus{ui->pushButton_light_5,ui->label_status_5,true});
    m_light_Status.append(LightStatus{ui->pushButton_light_6,ui->label_status_6,false});
    m_light_Status.append(LightStatus{ui->pushButton_light_7,ui->label_status_7,true});
    m_light_Status.append(LightStatus{ui->pushButton_light_8,ui->label_status_8,false});

    for(LightStatus l:m_light_Status){
        setLightStatus(l.label,l.status);
        setButtonSheet(l.btn);
        connect(l.btn,SIGNAL(clicked(bool)),this,SLOT(onLightClicked()));
    }
}

FormCloudControl::~FormCloudControl()
{
    delete ui;
}

void FormCloudControl::showEvent(QShowEvent *event)
{
event->accept();
}

void FormCloudControl::on_pushButton_ok_clicked()
{

}

void FormCloudControl::on_pushButton_cancel_clicked()
{

}

void FormCloudControl::on_pushButton_select_down_clicked()
{
    QString dir =  QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     ".",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(!dir.trimmed().isEmpty())
        ui->lineEdit_down->setText(dir.trimmed());
}

void FormCloudControl::on_pushButton_select_up_clicked()
{
    QString dir =  QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     ".",QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(!dir.trimmed().isEmpty())
        ui->lineEdit_up->setText(dir.trimmed());
}


void FormCloudControl::setButtonSheet(QPushButton *btn)
{
    btn->setStyleSheet("QPushButton{border-image: url(:/icon/cloud_button.png);}"
                       "QPushButton:hover{border-image: url(:/icon/cloud_button_down.png);}"
                       "QPushButton:pressed{border-image: url(:/icon/cloud_button_down.png);}"
                       "QPushButton:checked{border-image: url(:/icon/cloud_button_down.png);}");
}

void FormCloudControl::setLightStatus(QLabel*l, bool isopen)
{
    if(l!=NULL){
        if(isopen)
            l->setPixmap(QPixmap(":/icon/linght_green.png"));
        else{
            l->setPixmap(QPixmap(":/icon/red.png"));
        }
    }
}



void FormCloudControl::setLight(int index)
{
    bool s = !m_light_Status.at(index).status;
    m_light_Status[index].status = s;
    setLightStatus(m_light_Status.at(index).label,s);
}


void FormCloudControl::onLightClicked()
{
    QPushButton*btn =  dynamic_cast<QPushButton*>(sender());
    for(int i=0;i<m_light_Status.size();++i){
        if(m_light_Status.at(i).btn==btn){
            setLight(i);
        }
    }
}

