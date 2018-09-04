#include "dialognewcollectdata.h"
#include "ui_dialognewcollectdata.h"
#include <QDateTime>
#include <QToolTip>
#include <QMessageBox>
#include "datacenter.h"

DialogNewCollectData::DialogNewCollectData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewCollectData)
{
    ui->setupUi(this);
    setStyleSheet("#DialogNewCollectData{border-image: url(icon/cloud_right_back.png);}");

//    setStyleSheet("#DialogNewCollectData{border: 10px solid #1C6493; border-radius: 10px;background-color:#9004111A}");


    ui->pushButton_cancel->setStyleSheet("QPushButton{border-image: url(:/icon/cancel.png);}"
                                         "QPushButton:hover{border-image: url(:/icon/cancel_down.png);}"
                                         "QPushButton:pressed{border-image: url(:/icon/cancel_down.png);}"
                                         "QPushButton:checked{border-image: url(:/icon/cancel_down.png);}");
    setWindowFlags(Qt::Window|\
                   Qt::FramelessWindowHint |\
                   Qt::WindowSystemMenuHint|\
                   Qt::WindowMinimizeButtonHint|\
                   Qt::WindowMaximizeButtonHint);
    m_model = NEW_Model;
    for(CollectParam p: dataCenter::instance()->all_param()){
        ui->comboBox_pname->addItem(p.P_name);
    }
    connect(ui->comboBox_pname,SIGNAL(currentIndexChanged(QString)),this,SLOT(collectParamChange()));
}

DialogNewCollectData::~DialogNewCollectData()
{
    delete ui;
}

void DialogNewCollectData::setmodel(DialogShowModel model)
{
    m_model = model;
    if(m_model==NEW_Model){
        ui->lineEdit_dname->setText("");
        ui->lineEdit_dvalue->setText("");
        ui->lineEdit_dunit->setText("");
        ui->comboBox_pname->setCurrentIndex(-1);
        ui->lineEdit_dtime->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        curData.D_name="";
        curData.D_time="";
        curData.D_unit="";
        curData.D_value=0;
        ui->lineEdit_dtime->setEnabled(false);
        ui->pushButton_add->setStyleSheet("QPushButton{border-image: url(:/icon/increase.png);}"
                                          "QPushButton:hover{border-image: url(:/icon/increase_down.png);}"
                                          "QPushButton:pressed{border-image: url(:/icon/increase_down.png);}"
                                          "QPushButton:checked{border-image: url(:/icon/increase_down.png);}");
    }
    if(m_model==Del_Model){
        ui->lineEdit_dname->setEnabled(false);
        ui->lineEdit_dvalue->setEnabled(false);
        ui->lineEdit_dunit->setEnabled(false);
        ui->comboBox_pname->setEnabled(false);
        ui->lineEdit_dtime->setEnabled(false);
        ui->pushButton_add->setStyleSheet("QPushButton{border-image: url(:/icon/delete.png);}"
                                          "QPushButton:hover{border-image: url(:/icon/delete_down.png);}"
                                          "QPushButton:pressed{border-image: url(:/icon/delete_down.png);}"
                                          "QPushButton:checked{border-image: url(:/icon/delete_down.png);}");
    }
    if(m_model==Modify_Model){
        ui->lineEdit_dname->setEnabled(false);
        ui->lineEdit_dtime->setEnabled(false);
        ui->lineEdit_dunit->setEnabled(false);
        ui->comboBox_pname->setEnabled(false);
        ui->pushButton_add->setStyleSheet("QPushButton{border-image: url(:/icon/modify.png);}"
                                          "QPushButton:hover{border-image: url(:/icon/modify_down.png);}"
                                          "QPushButton:pressed{border-image: url(:/icon/modify_down.png);}"
                                          "QPushButton:checked{border-image: url(:/icon/modify_down.png);}");
    }
}

void DialogNewCollectData::on_pushButton_add_clicked()
{
    if(m_model==NEW_Model||m_model==Modify_Model){
        curData.D_name = ui->lineEdit_dname->text().trimmed();
        curData.D_value = ui->lineEdit_dvalue->text().trimmed().toDouble()*100;
        curData.D_unit = ui->lineEdit_dunit->text().trimmed();
        curData.P_name = ui->comboBox_pname->currentText();
        curData.D_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        if(curData.P_name.isEmpty()){
            QToolTip::showText(ui->comboBox_pname->mapToGlobal(QPoint(100, 0)), "类型不能为空!");
            return;
        }
        if(curData.D_name.isEmpty()){
            QToolTip::showText(ui->lineEdit_dname->mapToGlobal(QPoint(100, 0)), "名称不能为空!");
            return;
        }
        if( ui->lineEdit_dvalue->text().trimmed().isEmpty()){
            QToolTip::showText(ui->lineEdit_dvalue->mapToGlobal(QPoint(100, 0)), "数值不能为空!");
            return;
        }
        if(m_model==NEW_Model){
            if(dataCenter::instance()->AddCollectData(curData)){
                done(123);
            }else{
                QMessageBox::warning(this,"提示","创建失败！");
                return;
            }
        }else{
            if(dataCenter::instance()->ModCollectData(curData)){
                done(123);
            }else{
                QMessageBox::warning(this,"提示","修改失败！");
                return;
            }
        }

    }
    if(m_model==Del_Model){
        if(dataCenter::instance()->DelCollectData(curData.P_name,curData.D_name)){
            done(123);
        }else{
            QMessageBox::warning(this,"提示","删除失败");
            done(-1);
            return;
        }
    }
}

void DialogNewCollectData::on_pushButton_cancel_clicked()
{
    done(-1);
}

void DialogNewCollectData::collectParamChange()
{
    for(CollectParam p: dataCenter::instance()->all_param()){
        if(p.P_name==ui->comboBox_pname->currentText()){
            ui->lineEdit_dunit->setText(p.P_unit);
        }
    }
}



CollectData DialogNewCollectData::getCurData() const
{
    return curData;
}

void DialogNewCollectData::setCurData(const CollectData &value)
{
    curData = value;
    ui->lineEdit_dname->setText(curData.D_name);
    ui->lineEdit_dvalue->setText(QString("%1").arg(curData.D_value/100));
    ui->lineEdit_dunit->setText(curData.D_unit);
    ui->lineEdit_dtime->setText(curData.D_time);
    ui->comboBox_pname->setCurrentText(curData.P_name);
}
